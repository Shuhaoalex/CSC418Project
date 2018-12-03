#include "Object.h"
#include "Light.h"
#include "Camera.h"
#include <memory>
#include <vector>
struct shared_arg {
    int screen_h;
    int screen_w;
    Camera & camera;
    std::vector< std::shared_ptr<Object>> & objects;
    std::vector< std::shared_ptr<Light>> & lights;
    std::vector<unsigned char> & rgb_image;
    int num_threads;
    shared_arg(int h,
               int w,
               Camera & cam,
               std::vector< std::shared_ptr<Object>> & objs,
               std::vector< std::shared_ptr<Light>> & lits,
               std::vector<unsigned char> & image,
               int n_threads):
                    screen_h(h),
                    screen_w(w),
                    camera(cam),
                    objects(objs),
                    lights(lits),
                    rgb_image(image),
                    num_threads(n_threads) {}
};

struct thread_arg {
    shared_arg & shared;
    int thread_id;
    thread_arg(shared_arg & sh, int id):shared(sh),thread_id(id){}
};