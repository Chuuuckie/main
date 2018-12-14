#include <ctime>
#include <iostream>
#include <raspicam_cv.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
 
int main(int argc, char **argv)
{
    int threshold = 100;
    const int frameDelay = 100, maxContours = 500;
    
    raspicam::RaspiCam_Cv cam;
    Mat image;
    cam.set(CV_CAP_PROP_FORMAT, CV_8UC1);
    if (!cam.open())
        return 1;
    
    const char szSourceWindow[] = "Source", szContoursWindow[] = "Contours";
    namedWindow(szSourceWindow, WINDOW_AUTOSIZE);
    namedWindow(szContoursWindow, WINDOW_AUTOSIZE);
    createTrackbar("Threshold:", szSourceWindow, &threshold, 255, NULL);

    for (;;)
    {
        RNG rng(12345);
        cam.grab();
        cam.retrieve(image);
        Mat smallImage;
        resize(image, smallImage, Size(), 0.5, 0.5);
        imshow(szSourceWindow, smallImage);
        
        Mat canny_output;
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        Canny(smallImage, canny_output, threshold, threshold * 2, 3);
        findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

        Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
        for (size_t i = 0; i < std::min(contours.size(), (size_t)maxContours); i++)
        {
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            drawContours(drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point());
        }

        imshow(szContoursWindow, drawing);
        waitKey(frameDelay);
    }
    cam.release();
}
