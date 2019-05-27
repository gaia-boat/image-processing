#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string>
#include <iostream>

#define IMAGE_PATH "./data/plastic-trash.jpg"

using namespace cv;


int main(int argc, char **argv) {
    String image_name(IMAGE_PATH);

    Mat image;
    image = imread(image_name, 0);
    resize(image, image, cv::Size(), 0.25, 0.25);

    int height = image.size().height;
    int width = image.size().width;

    double sum_pixels = 0.0;
    for(int i = 0; i < image.rows; i++) {
        for(int j = 0; j < image.cols; j++) {
            sum_pixels += (int)image.at<uchar>(i, j);
        }
    }

    double avg_pixels = sum_pixels / (height * width);

    printf("Avg of pixels: %lf \n", avg_pixels);

    threshold(image, image, avg_pixels, 255, THRESH_BINARY);

    imshow("Output", image);
    waitKey(0);

    return 0;

}
