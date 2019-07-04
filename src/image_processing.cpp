#include <Python.h> 
#include "base.h"
#include "morph_transformations.h"
#include "objects.h"
#include "drawing.h"

#define CICLES 10
#define MIN_CICLES 5

using namespace cv;
using namespace std;

long capture() {
    VideoCapture cap;

    if(!cap.open(2))
        exit(1);

    for(int i = 0; i < CICLES ; i++) {
        Mat frame;
        Mat org_frame;

        cap.read(frame);

        if(frame.empty())
            break;

        Size img_size(IMAGE_WIDTH, IMAGE_HEIGHT);
        resize(frame, frame, img_size);

        org_frame = frame.clone();

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

        /* Image to draw the contours and rectangles */
        Mat drawing = Mat::zeros( frame.size(), CV_8UC3 );

        /* Obstacle Flag */
        int obs = 0;

        for(size_t i = 0; i < contours.size(); i++) {
            get_rotated_recs(minRect, contours, i);

            if(i > MIN_CICLES) {
                obs = check_for_obstacle(contours, minRect, i);
            }

            draw_objects(org_frame, contours, minRect, i);
            draw_objects(drawing, contours, minRect, i);

        }

        if(obs) {
            return obs;
        }

        imshow("Original Image", org_frame);
        imshow("Contours", drawing);

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
