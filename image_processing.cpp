#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
/* #include <raspicam/raspicam.h> */

#define IMAGE_PATH "./data/plastic-trash.jpg"
/* #define IMAGE_PATH "./data/trash_on_water.jpg" */
#define OUTPUT_IMAG "./data/one_trash_cont.jpg"
#define IMAGE_HEIGHT 560
#define IMAGE_WIDTH 780
#define MAX_PIXEL_VAL 255

using namespace cv;
using namespace std;

void write_bin(Mat image) {
    ofstream filebin;

    filebin.open("bins.txt");

    int height = image.size().height;
    int width = image.size().width;

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            filebin << (int)image.at<uchar>(i, j) << " ";
        }
        filebin << "\n";
    }

    filebin.close();
}

void erosion(Mat image) {

    int erosion_size = 1;
    Mat element = getStructuringElement( MORPH_RECT,
                       Size( 3, 3 ));
    erode(image, image, element);
}

/* void get_image_form_rasp() { */
/*     raspicam::RaspiCam Camera; */

/*     if(!Camera.open()) { */
/*         cerr << "Error opening camera" << endl; */
/*         return -1; */
/*     } */

/*     Camera.grab() */

/* 	unsigned char *data=new unsigned char[  Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )]; */

/*     Camera.retrieve(data, raspicam::RASPICAM_FORMAT_RGB); */

/*     Camera.retrieve(data, raspicam::RASPICAM_FORMAT_RGB) */
/* } */

void dilation(Mat image){
    Mat element = getStructuringElement( MORPH_RECT,
                       Size( 3, 3 ));
    dilate(image, image, element);
}

void apply_blur(Mat image){

    Size k(7, 7);

    GaussianBlur(image, image, k, 0);
}

void apply_canny(Mat image){
    double threshold1 = 50;
    double threshold2 = 100;
    Canny(image, image, threshold1, threshold2);
}

int main(int argc, char **argv) {

    Size img_size(IMAGE_WIDTH, IMAGE_HEIGHT);

    Mat image;
    image = imread(IMAGE_PATH, 0);
    resize(image, image, img_size);

    const int height = image.size().height;
    const int width = image.size().width;

    /* Morphological transformation */
    apply_blur(image);
    apply_canny(image);
    dilation(image);
    erosion(image);

    /* To generate random colors */
    RNG rng(63);

    /* Get contours */
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(image, contours, hierarchy,
            RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    /* Get the rotated rectangle of each contour */
    vector<RotatedRect> minRect(contours.size());
    for(int i = 0; i < contours.size(); i++)
    {
        minRect[i] = minAreaRect(Mat(contours[i]));
    }

    /* Image to draw the contours and rectangles */
    Mat drawing = Mat::zeros( image.size(), CV_8UC3 );

    for(int i = 0; i < contours.size(); i++) {
        /* Generate random colour for each contour and its rectangle */
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

        /* Draw the contour on the output image */
        drawContours(drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());

        Size2f recSize = Size2f();
        recSize = minRect[i].size;

        printf("Height: %lf\n", recSize.height);
        printf("Width: %lf\n", recSize.width);

        /* Draw the rectangle */
        Point2f rect_points[4];
        minRect[i].points( rect_points );

        for( int j = 0; j < 4; j++ )
            line( drawing, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );
    }

    imshow("Contours", drawing);
    waitKey(0);

    return 0;

}
