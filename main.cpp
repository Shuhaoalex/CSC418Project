#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "read_json.h"
#include "write_ppm.h"
#include "viewing_ray.h"
#include "raycolor.h"
#include <Eigen/Core>
#include <vector>
#include <iostream>
#include <memory>
#include <limits>
#include <functional>
#include <pthread.h>
#include "pthread_args.h"
#define NUM_THREAD 8

volatile int available_threads = NUM_THREAD;
int buffer[NUM_THREAD];
volatile int buffer_head = 0;
volatile int buffer_tail = 0;
volatile int buffer_n = 0;
pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;

void * tracer(void * arg) {
  struct thread_arg * args = (thread_arg *) arg;
  int width = (args->shared).screen_w;
  int height = (args->shared).screen_h;
  int n_threads = (args->shared).num_threads;
  int i = args->thread_id;
  for (int j = 0; j < width; j++) {
    // Set background color
      Eigen::Vector3d rgb(0,0,0);

      // Compute viewing ray
      Ray ray;
      viewing_ray((args->shared).camera,i,j,width,height,ray);
      
      // Shoot ray and collect color
      raycolor(ray,1.0,(args->shared).objects,(args->shared).lights,0,rgb);

      // Write double precision color into image
      auto clamp = [](double s){ return std::max(std::min(s,1.0),0.0);};
      (args->shared).rgb_image[0+3*(j+width*i)] = 255.0*clamp(rgb(0));
      (args->shared).rgb_image[1+3*(j+width*i)] = 255.0*clamp(rgb(1));
      (args->shared).rgb_image[2+3*(j+width*i)] = 255.0*clamp(rgb(2));
  }
  pthread_mutex_lock(&running_mutex);
  available_threads++;
  buffer[buffer_tail] = i;
  buffer_tail = (buffer_tail + 1)%NUM_THREAD;
  buffer_n++;
  pthread_mutex_unlock(&running_mutex);
}

int main(int argc, char * argv[])
{
  Camera camera;
  std::vector< std::shared_ptr<Object> > objects;
  std::vector< std::shared_ptr<Light> > lights;
  // Read a camera and scene description from given .json file
  read_json(
    argc<=1?"../data/sphere-and-plane.json":argv[1],
    camera,
    objects,
    lights);
  int height = 1080;
  int width = 1920;
  std::vector<unsigned char> rgb_image(3*width*height);
  shared_arg shared(height, width, camera, objects, lights, rgb_image, NUM_THREAD);
  pthread_t threads[height];
  // For each row
  for (int i = 0; i < height; i++) {
    thread_arg* arg = new thread_arg(shared, i);
    pthread_mutex_lock(&running_mutex);
    available_threads--;
    pthread_mutex_unlock(&running_mutex);
    
    pthread_create(&threads[i], NULL, tracer, arg);

    if (i != height - 1) {
      while (available_threads == 0){;}
    }
  
    while (buffer_n != 0) {
      pthread_join(threads[buffer[buffer_head]], NULL);
      buffer_head = (buffer_head + 1)%NUM_THREAD;
      pthread_mutex_lock(&running_mutex);
      buffer_n--;
      pthread_mutex_unlock(&running_mutex);
    }
  }

  while (available_threads != NUM_THREAD) {
    while (buffer_n == 0){;}
    while (buffer_n != 0) {
      pthread_join(threads[buffer[buffer_head]], NULL);
      buffer_head = (buffer_head + 1)%NUM_THREAD;
      pthread_mutex_lock(&running_mutex);
      buffer_n--;
      pthread_mutex_unlock(&running_mutex);
    }
  }
  write_ppm("rgb.ppm",rgb_image,width,height,3);
}
