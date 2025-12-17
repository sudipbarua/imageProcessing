#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Segmentation.h"

int main(int argc, char *argv[])
{
    //read images
    cv::Mat img = cv::imread(INPUTIMAGEDIR "/lena.tiff");
    cv::Mat imgTemplate = cv::imread(INPUTIMAGEDIR "/template_1.tiff");

    //convert to grayscale
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    cv::cvtColor(imgTemplate, imgTemplate, cv::COLOR_BGR2GRAY);

    // convert to a float image
    img.convertTo(img, CV_32F, 1.0/255.0);
    imgTemplate.convertTo(imgTemplate, CV_32F, 1.0/255.0);

    //declare output variables
    cv::Mat imgCorrelation;
    cv::Mat imgMatched;

    //create class instance
    Segmentation *segmentation = new Segmentation();

    // begin processing ///////////////////////////////////////////////////////////

    // create a template image
    //segmentation->cutAndSave(img, cv::Point(316, 252), cv::Size(30, 30), "../data/template.tiff");

    // Template Matching
    // compute and show normalized cross correlation
    segmentation->crossCorrelate(img, imgTemplate, imgCorrelation);
    cv::imshow("Cross Correlation", imgCorrelation);
    // find the best match between image and template
    cv::Point matchPoint = segmentation->findMaximum(imgCorrelation);
    std::cout << "Found best match at " << matchPoint << "\n";
    // draw a rectangle at the match position
    segmentation->drawRect(img, matchPoint, imgTemplate.size(), imgMatched);
    cv::imshow("Matched Template", imgMatched);

    // end processing /////////////////////////////////////////////////////////////

    //wait for key pressed
    cv::waitKey();

    return 0;
}
