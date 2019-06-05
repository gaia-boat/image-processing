#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#define IMAGE_PATH "./data/trash_on_water_no_sky.jpg"
#define OUTPUT_IMAG "./data/trash_on_water_no_sky/binary_by_mean_with_erosion.png"
#define IMAGE_HEIGHT 90 
#define IMAGE_WIDTH 160
#define MAX_PIXEL_VAL 255

using namespace cv;


int mode(Mat image) {
    // get the highest value on the list
    int max = MAX_PIXEL_VAL;

    int t = max + 1;
    int *count;

    int height = image.size().height;
    int width = image.size().width;

    count = (int *)calloc(t, sizeof(int));


    for(int i = 0; i < width; i++) {
        int pixel = (int)image.at<uchar>(1, i);
        count[pixel]++;
    }

    int mode = 0;
    int k = count[0];

    for(int i = 1; i < t; i++) {
        if(count[i] > k) {
            k = count[i];
            mode = i;
        }
    }

    return mode;
}

void write_bin(Mat image) {
    std::ofstream filebin;

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

std::array<int, IMAGE_HEIGHT> array_of_mode(Mat image) {
    std::array<int, IMAGE_HEIGHT> rows_mode;

    for(int i = 0; i < image.rows; i++) {
        int mode_val;
        mode_val = mode(image.row(i));

        rows_mode[i] = mode_val;
    }

    return rows_mode;
}

double avg_by_mode(Mat image) {

    std::array<int, IMAGE_HEIGHT> rows_mode;
    rows_mode = array_of_mode(image);

    double sum_pixels = 0.0;
    
    for(int i = 0; i < rows_mode.size(); i++) {
        sum_pixels += rows_mode[i];
        
    }

    double avg_pixels = sum_pixels / rows_mode.size();

    return avg_pixels;
}

double avg_by_mean(Mat image) {

    std::array<int, IMAGE_HEIGHT> rows_mode;
    double sum_pixels = 0.0;

    const int height = image.size().height;
    const int width = image.size().width;

    for(int i = 0; i < image.rows; i++) {
        for(int j = 0; j < image.cols; j++) {
            sum_pixels += (int)image.at<uchar>(i, j);
        }

    }

    double avg_pixels = sum_pixels / (height * width);

    return avg_pixels;
    
}

int mode_of_mode(Mat image) {

    std::array<int, IMAGE_HEIGHT> rows_mode;
    rows_mode = array_of_mode(image); 

    int max = MAX_PIXEL_VAL;

    int t = max + 1;
    int *count;
    count = (int *)calloc(t, sizeof(int));


    for(int i = 0; i < rows_mode.size(); i++) {
        int val = rows_mode[i];
        count[val]++;
    }

    int mode = 0;
    int k = count[0];

    for(int i = 1; i < t; i++) {
        if(count[i] > k) {
            k = count[i];
            mode = i;
        }
    }

    free(count);

    return mode;

}

void erosion(Mat image) {

    int erosion_size = 1;
    Mat element = getStructuringElement( MORPH_RECT,
                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                       Point( erosion_size, erosion_size ) );
    erode(image, image, element);
}

int main(int argc, char **argv) {
    String image_name(IMAGE_PATH);
    Size img_size(IMAGE_WIDTH, IMAGE_HEIGHT);

    Mat image;
    image = imread(image_name, 0);
    resize(image, image, img_size);

    const int height = image.size().height;
    const int width = image.size().width;

    printf("Height: %d\n", height);
    printf("Width: %d\n", width);

    double avg_pixels = avg_by_mean(image); 
    /* double avg_pixels = avg_by_mode(image); */ 
    /* int avg_pixels = mode_of_mode(image); */ 

    printf("Avg of pixels: %lf \n", avg_pixels);

    threshold(image, image, avg_pixels, 255, THRESH_BINARY);

    erosion(image);

    /* imshow("Output", image); */
    imwrite(OUTPUT_IMAG, image);
    waitKey(0);

    return 0;

}
