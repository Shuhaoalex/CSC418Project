import cv2 as cv
import numpy as np
file = "1080p.ppm"
image = cv.imread(file, 1)
print(image.shape)
result = np.empty((image.shape[0]/3, image.shape[1]/3, 3))
for i in range(1, image.shape[0], 3):
    for j in range(1, image.shape[1], 3):
        result[i//3, j//3, :] = image[i,j,:]
result1 = cv.resize(result, None, fx=3, fy=3, interpolation=cv.INTER_LINEAR)

def kernal_location(i,j,max_i,max_j):
    i_l = max(i-1,0)
    i_r = min(max_i - 1, i+1)
    j_l = max(j-1, 0)
    j_r = min(max_j - 1, j+1)
    result = np.array(((i_l, j_l), (i_l, j), (i_l, j_r),\
                       (i, j_l),                (i,j_r),\
                       (i_r, j_l), (i_r, j), (i_r, j_r)))
    return result
location_to_be_replaced = set()
for i in range(1, result.shape[0], 2):
    for j in range(1, result.shape[1], 2):
        for (a,b) in kernal_location(i,j,image.shape[0]/3, image.shape[1]/3):
            cos_dist = result[a,b].dot(result[i,j])/(np.linalg.norm(result[a,b]) * np.linalg.norm(result[i,j]))
            abs_dist = np.linalg.norm(result[a,b] - result[i,j])
            if (cos_dist < 0.8 or abs_dist > 10):
                location_to_be_replaced.add((i,j))
                location_to_be_replaced.add((a,b))
copy = result1.copy()
replaced_pixels = set()
for (i,j) in location_to_be_replaced:
    for (a,b) in kernal_location(i*3 + 1, j*3 + 1, image.shape[0], image.shape[1]):
        result1[a,b] = image[a,b]
        replaced_pixels.add((a,b))
cv.imwrite("result1.ppm", result1)