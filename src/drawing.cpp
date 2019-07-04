#include "drawing.h"

void draw_objects(Mat &dest_image, vector<vector<Point>> &contours, 
                  vector<RotatedRect> &minRect, size_t i) {
    RNG rng(63);

    /* Generate random colour for each contour and its rectangle */
    Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

    /* Draw the contour on the output image */
    drawContours(dest_image, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());

    Size2f recSize = Size2f();
    recSize = minRect[i].size;

    /* Draw the rectangle */
    Point2f rect_points[4];
    minRect[i].points( rect_points );

    for( int j = 0; j < 4; j++ )
        line( dest_image, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );

}

