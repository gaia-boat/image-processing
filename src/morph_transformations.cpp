#include "morph_transformations.h"

void blur(Mat &image) {
    Size k(13, 13);
    GaussianBlur(image, image, k, 0);
}

void canny(Mat &image) {
    double threshold1 = 50;
    double threshold2 = 100;
    Canny(image, image, threshold1, threshold2);
}

void dilation(Mat &image) {
    Mat element = getStructuringElement( MORPH_RECT,
            Size( 3, 3 ));
    dilate(image, image, element);
}

void erosion(Mat &image) {
    Mat element = getStructuringElement( MORPH_RECT,
            Size( 3, 3 ));
    erode(image, image, element);

}

