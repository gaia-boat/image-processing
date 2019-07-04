#ifndef DRAWING_H
#define DRAWING_H

#include "base.h"

using namespace cv;
using namespace std;

void draw_objects(Mat &dest_image, vector<vector<Point>> &contours, 
                  vector<RotatedRect> &minRect, size_t i);

#endif
