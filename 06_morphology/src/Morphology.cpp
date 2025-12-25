#include <iostream>
#include <cmath>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Morphology.h"

////////////////////////////////////////////////////////////////////////////////////
// constructor. initialize the kernels
////////////////////////////////////////////////////////////////////////////////////
Morphology::Morphology()
{
    // Initialize kernels
    uchar kernel3x3_plus[3 * 3] = {
          0, 255,   0,
        255, 255, 255,
          0, 255,   0 };
    kernel3x3Plus = cv::Mat(3, 3, CV_8U, kernel3x3_plus).clone();

    uchar kernel1x5_line[5] = { 255, 255, 255, 255, 255 };
    kernel1x5Line = cv::Mat(5, 1, CV_8U, kernel1x5_line).clone();

    uchar kernel3x3_full[3 * 3] = {
        255, 255, 255,
        255, 255, 255,
        255, 255, 255 };
    kernel3x3Full = cv::Mat(3, 3, CV_8U, kernel3x3_full).clone();

    uchar kernel4x4_full[4 * 4] = {
        255, 255, 255, 255,
        255, 255, 255, 255,
        255, 255, 255, 255,
        255, 255, 255, 255 };
    kernel4x4Full = cv::Mat(4, 4, CV_8U, kernel4x4_full).clone();
}

Morphology::~Morphology(){}

cv::Mat Morphology::getKernelPlus()
{
    return kernel3x3Plus;
}

cv::Mat Morphology::getKernelLine()
{
    return kernel1x5Line;
}

cv::Mat Morphology::getKernelFull(int size)
{
    if (size == 4)
        return kernel4x4Full;
    return kernel3x3Full;
}

void Morphology::dilate(const cv::Mat &input, cv::Mat &output, const cv::Mat &kernel)
{
    if (input.empty() || kernel.empty())
    {
        std::cout << "One or more inputs are empty!" << std::endl;
        return;
    }

    int rows = input.rows;
    int cols = input.cols;

    output.release();
    output = cv::Mat::zeros(rows, cols, CV_8U);



    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////



}

void Morphology::erode(const cv::Mat &input, cv::Mat &output, const cv::Mat &kernel)
{
    if (input.empty() || kernel.empty())
    {
        std::cout << "One or more inputs are empty!" << std::endl;
        return;
    }

    int rows = input.rows;
    int cols = input.cols;

    output.release();
    output = cv::Mat::zeros(rows, cols, CV_8U);



    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////



}

void Morphology::subtract(const cv::Mat &input, cv::Mat &output, const cv::Mat &subtract)
{
    if (input.empty() || subtract.empty())
    {
        std::cout << "One or more inputs are empty!" << std::endl;
        return;
    }

    int rows = input.rows;
    int cols = input.cols;

    if (subtract.rows != rows || subtract.cols != cols)
    {
        std::cout << "subtract image does not fit input image!" << std::endl;
        return;
    }

    output.release();
    output = cv::Mat::zeros(rows, cols, CV_8U);



    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////



}
