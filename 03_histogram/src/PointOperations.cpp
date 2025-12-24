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
    for (int r = 0; r < rows; r++)
    {
        const uchar* inputPtr = input.ptr<uchar>(r);
        uchar* outputPtr = output.ptr<uchar>(r);

        for (int c = 0; c < cols; c++)
        {
            float newValue = alpha * (static_cast<float>(inputPtr[c]) - static_cast<float>(center)) + static_cast<float>(center);
            if (newValue < 0.0f)
                newValue = 0.0f;
            else if (newValue > 255.0f)
                newValue = 255.0f;

            outputPtr[c] = static_cast<uchar>(newValue);
        }
    }
    
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
    for (int r = 0; r < rows; r++)
    {
        const uchar* inputPtr = input.ptr<uchar>(r);
        uchar* outputPtr = output.ptr<uchar>(r);

        for (int c = 0; c < cols; c++)
        {
            int newValue = static_cast<int>(inputPtr[c]) + alpha;
            if (newValue < 0)
                newValue = 0;
            else if (newValue > 255)
                newValue = 255;

            outputPtr[c] = static_cast<uchar>(newValue);
        }
    }
    

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
    for (int r = 0; r < rows; r++)
    {
        const uchar* inputPtr = input.ptr<uchar>(r);
        uchar* outputPtr = output.ptr<uchar>(r);

        for (int c = 0; c < cols; c++)
        {
            outputPtr[c] = 255 - inputPtr[c];
        }
    }
    
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
    uchar bins = pow(2, n);
    for (int r = 0; r < rows; r++)
    {
        const uchar* inputPtr = input.ptr<uchar>(r);
        uchar* outputPtr = output.ptr<uchar>(r);

        for (int c = 0; c < cols; c++)
        {
            uchar pixelValue = inputPtr[c];
            uchar j = pixelValue * (bins / 256);
            uchar quantizedValue = (j + 0.5f) * (256 / bins);  // midpoint of the bin
            outputPtr[c] = quantizedValue;
        }
    }
}
