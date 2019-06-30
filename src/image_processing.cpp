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


void capture() {

    VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(2))
        exit(1);
    for(;;)
    {
          Mat frame;
          Mat orgFrame;
          Mat dest;
          cap.read(frame);

          if(frame.empty()) 
              break; // end of video stream

          Size img_size(IMAGE_WIDTH, IMAGE_HEIGHT);
          resize(frame, frame, img_size);

          orgFrame = frame.clone();

          /* GrayScale */
          cvtColor(frame, frame, COLOR_BGR2GRAY);


          /* Blur */
          Size k(13, 13);
          GaussianBlur(frame, frame, k, 0);

          /* Canny */
          double threshold1 = 50;
          double threshold2 = 100;
          Canny(frame, frame, threshold1, threshold2);

          /* Dilatation */
          Mat element = getStructuringElement( MORPH_RECT,
                  Size( 3, 3 ));
          dilate(frame, frame, element);

          /* Erosion */
          int erosion_size = 1;
          erode(frame, frame, element);

          RNG rng(63);

          /* Get contours */
          vector<vector<Point>> contours;
          vector<Vec4i> hierarchy;

          printf("Finding contours\n");
          findContours(frame, contours, hierarchy,
                  RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));


          /* Get the rotated rectangle of each contour */
          vector<RotatedRect> minRect(contours.size());
          for(int i = 0; i < contours.size(); i++)
          {
              minRect[i] = minAreaRect(Mat(contours[i]));
          }

          /* Image to draw the contours and rectangles */
          Mat drawing = Mat::zeros( frame.size(), CV_8UC3 );

          for(int i = 0; i < contours.size(); i++) {
              /* Generate random colour for each contour and its rectangle */
              Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

              /* Draw the contour on the output image */
              drawContours(orgFrame, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());

              Size2f recSize = Size2f();
              recSize = minRect[i].size;

              printf("Height: %lf\n", recSize.height);
              printf("Width: %lf\n", recSize.width);

              /* Draw the rectangle */
              Point2f rect_points[4];
              minRect[i].points( rect_points );

              for( int j = 0; j < 4; j++ )
                  line( orgFrame, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );
          }


          imshow("this is you, smile! :)", orgFrame);
          /* imshow("this is you, smile! :)", frame); */
          if(waitKey(10) == 27)
              break; // stop capturing by pressing ESC 
    }

    // the camera will be closed automatically upon exit
     cap.close();
}


int main() {
    capture();
}