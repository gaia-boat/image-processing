#include <Python.h> 
#include "base.h"
#include "morph_transformations.h"
#include "objects.h"
#include "drawing.h"

using namespace cv;
using namespace std;

long capture()
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
        int obs = 0;

        obs = check_for_obstacle(contours, minRect);

        /* if(obs){ */
        /*     return obs; */
        /* } */

        imshow("Original Image", orgFrame);
        imshow("Contours", drawing);

        /* waitKey(0); */
        if(waitKey(10) == 27)
            break; // stop capturing by pressing ESC
    }

    return 0;
}

static PyObject * capture_wrapper(PyObject *self, PyObject *args) {
	long result;
	result = capture();

	return PyLong_FromLong(result);
}

static PyMethodDef ImageProcessingMethods[] = {
	{"capture", capture_wrapper, METH_VARARGS, "Capture image and get obstacles"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef image_processing_module = {
	PyModuleDef_HEAD_INIT,
	"image_processing",
	NULL,
	-1,
	ImageProcessingMethods
};

PyMODINIT_FUNC PyInit_image_processing(void) {
	return PyModule_Create(&image_processing_module);
}

int main() {
    if(capture())
        return 1;

    return 0;
}
