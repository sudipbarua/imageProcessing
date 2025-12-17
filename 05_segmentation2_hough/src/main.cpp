#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Segmentation.h"

int main(int argc, char *argv[])
{
    //read images
    cv::Mat img = cv::imread(INPUTIMAGEDIR "/lines.tiff");

    //convert to grayscale
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

    // convert to a float image
    img.convertTo(img, CV_32F, 1.0/255.0);

    //declare output variables
    cv::Mat imgCorrelation;
    cv::Mat imgMatched;
    cv::Mat houghTransform;
    cv::Mat imgHough;
    cv::Mat imgDetectedLines;

    //create class instance
    Segmentation *segmentation = new Segmentation();

    // begin processing ///////////////////////////////////////////////////////////

    // Hough Transformation
    cv::imshow("Stright Lines", img);
    // compute Hough Transformation
    // define step size of the angle in degrees
    float phiStep = 1.0f;
    segmentation->houghTransform(img, phiStep, houghTransform);
    // find the lines
    cv::Mat lines = segmentation->findMaxima(houghTransform, 4);
    // scale and display the Hough transformation
    segmentation->scaleHoughImage(houghTransform, imgHough);
    cv::imshow("Hough Transformation", imgHough);
    // draw detected lines on the image and show
    segmentation->drawLines(img, lines, phiStep, imgDetectedLines);
    cv::imshow("Detected Lines", imgDetectedLines);

    // end processing /////////////////////////////////////////////////////////////

    //wait for key pressed
    cv::waitKey();

    return 0;
}
