#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>

#include "PointOperations.h"


PointOperations::PointOperations()
{}

PointOperations::~PointOperations()
{}
////////////////////////////////////////////////////////////////////////////////////
// adjust the contrast of an image by alpha around center
////////////////////////////////////////////////////////////////////////////////////
void PointOperations::adjustContrast(cv::Mat &input, cv::Mat &output, float alpha, uchar center)
{
    int rows = input.rows;
    int cols = input.cols;

    output.release();
    output.create(rows, cols, CV_8U);

    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////
    
}

////////////////////////////////////////////////////////////////////////////////////
// adjust the brightness of an image by alpha
////////////////////////////////////////////////////////////////////////////////////
void PointOperations::adjustBrightness(cv::Mat &input, cv::Mat &output, int alpha)
{
    int rows = input.rows;
    int cols = input.cols;

    output.release();
    output.create(rows, cols, CV_8U);

    if (input.isContinuous())
    {
        cols = rows * cols;
        rows = 1;
    }
    
    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////
    

}

////////////////////////////////////////////////////////////////////////////////////
// inversion of an image
////////////////////////////////////////////////////////////////////////////////////
void PointOperations::invert(cv::Mat &input, cv::Mat &output)
{
    int rows = input.rows;
    int cols = input.cols;

    output.release();
    output.create(rows, cols, CV_8U);

    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////
    
}

////////////////////////////////////////////////////////////////////////////////////
// quantization of an image with n bits
////////////////////////////////////////////////////////////////////////////////////
void PointOperations::quantize(cv::Mat &input, cv::Mat &output, uchar n)
{
    int rows = input.rows;
    int cols = input.cols;

    output.release();
    output.create(rows, cols, CV_8U);


    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////
}
