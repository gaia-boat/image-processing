#include "morph_transformations.h"

void blur(Mat &image) {
    Size k(BLUR_SIZE , BLUR_SIZE);
    GaussianBlur(image, image, k, 0);
}

void canny(Mat &image) {
    Canny(image, image, CANNY_THRESHOLD_1, CANNY_THRESHOLD_2);
}

void dilation(Mat &image) {
    Mat element = getStructuringElement( MORPH_RECT,
            Size(DILATION_SIZE, DILATION_SIZE));
    dilate(image, image, element);
}

void erosion(Mat &image) {
    Mat element = getStructuringElement( MORPH_RECT,
            Size(EROSION_SIZE, EROSION_SIZE));
    erode(image, image, element);

}

