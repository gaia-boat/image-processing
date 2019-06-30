#include <opencv2/opencv.hpp>
#include <stdio.h>

#define IMAGE_PATH "./data/webcam.jpg"
#define OUTPUT_IMAG "./data/one_trash_cont.jpg"
#define IMAGE_HEIGHT 560
#define IMAGE_WIDTH 720
#define MAX_PIXEL_VAL 255

#define HEIGHT_THRESHOLD 50
#define WIDTH_THRESHOLD 50

// This must be a float
#define CM_PER_PIXEL 1.0

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

        /* Draw the rectangle */
        Point2f rect_points[4];
        minRect[i].points( rect_points );

        for( int j = 0; j < 4; j++ )
            line( dest_image, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );
    }

}

double pixel_to_cm(double pixel)
{

    return pixel/CM_PER_PIXEL;
}

int check_for_obstacle(vector<vector<Point>> &contours, vector<RotatedRect> &minRect)
{
    for(int i = 0; i < contours.size(); i++)
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
        return 0;
    }
}

int capture()
{

    VideoCapture cap;

    if(!cap.open(2))
        exit(1);

    for(int i = 0; i < 10; i++)
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
        int obs = 0;

        obs = check_for_obstacle(contours, minRect);

        if(obs){
            return obs;
        }


        imshow("Original Image", orgFrame);
        imshow("Contours", drawing);

        waitKey(0);
        /* if(waitKey(10) == 27) */
        /*     break; // stop capturing by pressing ESC */
    }

    return 0;
}


int main() {
    if(capture())
        return 1;

}
