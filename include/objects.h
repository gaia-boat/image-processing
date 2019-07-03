#ifndef OBJECTS_H
#define OBJECTS_H

#include "base.h"

using namespace cv;
using namespace std;

void get_rotated_recs(vector<RotatedRect> &minRect, vector<vector<Point>> &contours);
void get_contours(Mat &image, vector<vector<Point>> &contours, vector<Vec4i> hierarchy);
double pixel_to_cm(double pixel);
long check_for_obstacle(vector<vector<Point>> &contours, vector<RotatedRect> &minRect);

#endif
