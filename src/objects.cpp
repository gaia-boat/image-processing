#include "objects.h"

void get_rotated_recs(vector<RotatedRect> &minRect, 
                      vector<vector<Point>> &contours) {
    for(size_t i = 0; i < contours.size(); i++)
    {
        minRect[i] = minAreaRect(Mat(contours[i]));
    }
}

void get_contours(Mat &image, 
                  vector<vector<Point>> &contours,
                  vector<Vec4i> hierarchy) {

    findContours(image, contours, hierarchy,
            RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
}

double pixel_to_cm(double pixel) {
    return pixel/CM_PER_PIXEL;
}

long check_for_obstacle(vector<vector<Point>> &contours, vector<RotatedRect> &minRect)
{
    for(size_t i = 0; i < contours.size(); i++)
    {
        Size2f recSize = Size2f();
        recSize = minRect[i].size;

        double px_height = pixel_to_cm(recSize.height);
        double px_width = pixel_to_cm(recSize.width);

        if(px_height >= HEIGHT_THRESHOLD || px_height >= WIDTH_THRESHOLD )
        {
            printf("\n\n>>>>>> Obstacle detected! <<<<<<\n");
            printf(">>>>>> Obstacle height: %.2lf cm <<<<<<\n", px_height);
            printf(">>>>>> Obstacle witdh:  %.2lf cm <<<<<<\n", px_width);
            return 1;
        }
    }
	return 0;
}

