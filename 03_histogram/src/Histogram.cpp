#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Histogram.h"


Histogram::Histogram(){
    histSize = 256;
}

Histogram::~Histogram(){}

////////////////////////////////////////////////////////////////////////////////////
// compute Histogram using the OpenCV function - only for reference
////////////////////////////////////////////////////////////////////////////////////
void Histogram::calcHist_cv(const cv::Mat &input, cv::Mat &hist)
{
    float range[2] = {0.0, (float)(histSize - 1)};   // range of pixel values (min and max value)
    const float* ranges[] = {range};
    
    int channels = 0;
    
    // call OpenCV function for a grayscale image
    cv::calcHist(&input, 1, &channels, cv::Mat(), hist, 1, &histSize, ranges );
}

///////////////////////////////////////////////////////////////////////////////
// compute Histogram by looping over the elements
///////////////////////////////////////////////////////////////////////////////
void Histogram::calcHist(const cv::Mat &input, cv::Mat &hist)
{

    hist.create(1, histSize, CV_32F);
    hist.setTo(cv::Scalar(0.0));

    float *pHist = hist.ptr<float>(0);

    int rows = input.rows;
    int cols = input.cols;

    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////

}

///////////////////////////////////////////////////////////////////////////////
// calculate statistics of histogram:
//  - min: bin with lowest intensity (darkest pixel)
//  - max: bin with highest intensity (brightest pixel)
//  - mean: mean brightness level of the picture
///////////////////////////////////////////////////////////////////////////////
void Histogram::calcStats(const cv::Mat &hist, uchar &min, uchar &max, uchar &mean)
{
    // find minimum
    // use variable "min" for your result
    // min = 0;
    
    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////

    
//############################################################
    
    // find maximum
    // use variable "max" for your result
    // max = 255;
    
    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////
    
    
//############################################################
    
    // calculate mean
    // use variable "max" for your result
    // mean = 127;
    
    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////
    
}


///////////////////////////////////////////////////////////////////////////////
// display Histogram as bar graph
///////////////////////////////////////////////////////////////////////////////
void Histogram::show(const cv::String &winname, const cv::Mat &hist)
{
    // get min and max bin values
    double minVal = 0, maxVal = 0;
    cv::minMaxLoc(hist, &minVal, &maxVal);

    // create new image for displaying the histogram
    cv::Mat histImg(histSize, histSize, CV_8U, cv::Scalar(255));

    // set maximum height of the bars to 90% of the image height
    int maxBinHeight = (int)(0.9 * histSize);

    // draw the bars
    for (int i = 0; i < histSize; i++){

        float binVal = hist.at<float>(i);
        int binHeight = (int) ( (binVal * maxBinHeight) / maxVal);

        cv::line(histImg, cv::Point(i, histSize),
                          cv::Point(i, histSize - binHeight),
                          cv::Scalar::all(0));

    }

    // show the histogram in a named window
    cv::imshow(winname, histImg);
}
