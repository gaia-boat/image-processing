#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#define IMAGE_PATH "./data/webcam.jpg"
/* #define IMAGE_PATH "./data/trash_on_water.jpg" */
#define OUTPUT_IMAG "./data/one_trash_cont.jpg"
#define IMAGE_HEIGHT 560 
#define IMAGE_WIDTH 720 
#define MAX_PIXEL_VAL 255

using namespace cv;
using namespace std;

void blur(Mat &image) 
{
    Size k(13, 13);
    GaussianBlur(image, image, k, 0);
}

void canny(Mat &image) 
{
    double threshold1 = 50;
    double threshold2 = 100;
    Canny(image, image, threshold1, threshold2);
}

void dilation(Mat &image) 
{
    Mat element = getStructuringElement( MORPH_RECT,
            Size( 3, 3 ));
    dilate(image, image, element);
}

void erosion(Mat &image) 
{
    int erosion_size = 1;
    Mat element = getStructuringElement( MORPH_RECT,
            Size( 3, 3 ));
    erode(image, image, element);

}

void get_rotated_recs(vector<RotatedRect> &minRect, vector<vector<Point>> &contours)
{
    for(int i = 0; i < contours.size(); i++)
    {
        minRect[i] = minAreaRect(Mat(contours[i]));
    }
}

void get_contours(Mat &image, vector<vector<Point>> &contours, vector<Vec4i> hierarchy)
{
    printf("Finding contours\n");
    findContours(image, contours, hierarchy,
            RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
}

void draw_objects(Mat &dest_image, vector<vector<Point>> &contours, vector<RotatedRect> &minRect) 
{
    RNG rng(63);

    for(int i = 0; i < contours.size(); i++) 
    {
        /* Generate random colour for each contour and its rectangle */
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

        /* Draw the contour on the output image */
        drawContours(dest_image, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());

        Size2f recSize = Size2f();
        recSize = minRect[i].size;

        printf("Height: %lf\n", recSize.height);
        printf("Width: %lf\n", recSize.width);

        /* Draw the rectangle */
        Point2f rect_points[4];
        minRect[i].points( rect_points );

        for( int j = 0; j < 4; j++ )
            line( dest_image, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );
    }

}

void capture()
{

    VideoCapture cap;

    if(!cap.open(2))
        exit(1);

    for(;;)
    {
        Mat frame;
        Mat orgFrame;
        Mat dest;
        cap.read(frame);

        if(frame.empty()) 
            break; 

        Size img_size(IMAGE_WIDTH, IMAGE_HEIGHT);
        resize(frame, frame, img_size);

        orgFrame = frame.clone();

        /* GrayScale */
        cvtColor(frame, frame, COLOR_BGR2GRAY);

        /* Blur */
        blur(frame);

        /* Canny */
        canny(frame);

        /* Dilatation */
        dilation(frame);

        /* Erosion */
        erosion(frame);

        /* Get contours */
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        get_contours(frame, contours, hierarchy);

        /* Get the rotated rectangle of each contour */
        vector<RotatedRect> minRect(contours.size());
        get_rotated_recs(minRect, contours);

        /* Image to draw the contours and rectangles */
        Mat drawing = Mat::zeros( frame.size(), CV_8UC3 );

        draw_objects(orgFrame, contours, minRect);
        draw_objects(drawing, contours, minRect);

        imshow("Original Image", orgFrame);
        imshow("Contours", drawing);

        if(waitKey(10) == 27)
            break; // stop capturing by pressing ESC 
    }
}


int main() {
    capture();
}
