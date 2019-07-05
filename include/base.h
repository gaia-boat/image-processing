#ifndef BASE_H
#define BASE_H

#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <cstdlib> 

#define IMAGE_HEIGHT 560
#define IMAGE_WIDTH 720
#define MAX_PIXEL_VAL 255

#define HEIGHT_THRESHOLD 50
#define WIDTH_THRESHOLD 50

#define CANNY_THRESHOLD_1 150.0 
#define CANNY_THRESHOLD_2 200.0 

#define BLUR_SIZE 17
#define EROSION_SIZE 3
#define DILATION_SIZE 3

// This must be a float
#define CM_PER_PIXEL 5.0


#endif
