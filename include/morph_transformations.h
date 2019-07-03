#ifndef MORPH_TRANSFORMATIONS_H
#define MORPH_TRANSFORMATIONS_H

#include "base.h"

using namespace cv;

void blur(Mat &image);
void canny(Mat &image);
void dilation(Mat &image);
void erosion(Mat &image);

#endif
