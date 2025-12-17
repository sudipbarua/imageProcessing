#include <iostream>
#include <cmath>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Filter.h"

////////////////////////////////////////////////////////////////////////////////////
// constructor. Initialize the kernels
////////////////////////////////////////////////////////////////////////////////////
Filter::Filter()
{
    // Initialize Binomial kernels
    // 3x3
    signed char kernelB3[3 * 3] =  {1, 2, 1,
                             2, 4, 2,
                             1, 2, 1};

    Binomial3 = cv::Mat(3, 3, CV_8S, kernelB3).clone();

    // 5x5
    signed char kernelB5[5 * 5] =  {1,  4,  6,  4, 1,
                             4, 16, 24, 16, 4,
                             6, 24, 36, 24, 6,
                             4, 16, 24, 16, 4,
                             1,  4,  6,  4, 1};

    Binomial5 = cv::Mat(5, 5, CV_8S, kernelB5).clone();

    // initialize Sobel kernels
    // 3x3 in X direction
    signed char kernelS1[3 * 3] =  {-1, 0, 1,
                             -2, 0, 2,
                             -1, 0, 1};

    Sobel3_X = cv::Mat(3, 3, CV_8S, kernelS1).clone();

    // 3x3 in Y direction
    signed char kernelS2[3 * 3] =  {-1, -2, -1,
                              0,  0,  0,
                              1,  2,  1};

    Sobel3_Y = cv::Mat(3, 3, CV_8S, kernelS2).clone();

    // 5x5 in X direction
    signed char kernelS3[5 * 5] =  { -2, -1, 0, 1,  2,
                              -8, -4, 0, 4,  8,
                             -12, -6, 0, 6, 12,
                              -8, -4, 0, 4,  8,
                              -2, -1, 0, 1,  2};

    Sobel5_X = cv::Mat(5, 5, CV_8S, kernelS3).clone();

    // 5x5 in Y direction
    signed char kernelS4[5 * 5] =  {-2, -8, -12, -8, -2,
                             -1, -4,  -6, -4, -1,
                              0,  0,   0,  0,  0,
                              1,  4,   6,  4,  1,
                              2,  8,  12,  8,  2};

    Sobel5_Y = cv::Mat(5, 5, CV_8S, kernelS4).clone();
    
    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////
    
    // create new kernel e.g. for the part with the seperated filter kernel
    
}

Filter::~Filter(){}

////////////////////////////////////////////////////////////////////////////////////
// convolve the image with the kernel using the OpenCV function - only for reference
////////////////////////////////////////////////////////////////////////////////////
void Filter::convolve_cv(const cv::Mat &input, cv::Mat &output, const cv::Mat &kernel)
{
    int normFactor = 0;
    
    int rows = kernel.rows;
    int cols = kernel.cols;
    
    if (kernel.isContinuous())
    {
        cols = rows * cols;
        rows = 1;
    }
    
    // calculate the normalisation factor from the filter kernel
    for (int r = 0; r < rows; ++r)
    {
        const signed char *pKernel = kernel.ptr<signed char>(r);
        
        for (int c = 0; c < cols; ++c)
        {
            normFactor += abs(*pKernel);
            ++pKernel;
        }
    }
    
    if (input.empty() || kernel.empty())
    {  
        std::cout << "One ore more inputs are empty!" << std::endl;
        return;
    }

    cv::Mat floatInput, floatKernel;
    input.convertTo(floatInput, CV_32F);
    kernel.convertTo(floatKernel, CV_32F);

    cv::filter2D(floatInput, output, floatInput.depth(), floatKernel, cv::Point(-1,-1), 0, cv::BORDER_REPLICATE);

    output /= (normFactor);
}

///////////////////////////////////////////////////////////////////////////////
// convolve the image with the square-sized 3x3 kernel using pointer access
///////////////////////////////////////////////////////////////////////////////
void Filter::convolve_3x3(const cv::Mat &input, cv::Mat &output, const cv::Mat &kernel)
{
    if (input.empty() || kernel.empty())
    {
        std::cout << "One ore more inputs are empty!" << std::endl;
        return;
    }

    int rows = input.rows;
    int cols = input.cols;

    output.release();
    // create a float image initialized with zeros
    output = cv::Mat::zeros(rows, cols, CV_32F);


    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////

    // 1. calculate the normalisation value
    // 2. perform a 3x3 convolution with cropped edges
    
}

///////////////////////////////////////////////////////////////////////////////
// convolve the image with any filter kernel using pointer access
///////////////////////////////////////////////////////////////////////////////
void Filter::convolve_generic(const cv::Mat &input, cv::Mat &output, const cv::Mat &kernel)
{
    if (input.empty() || kernel.empty())
    {
        std::cout << "One ore more inputs are empty!" << std::endl;
        return;
    }
    
    int rows = input.rows;
    int cols = input.cols;
    
    output.release();
    // create a float image initialized with zeros
    output = cv::Mat::zeros(rows, cols, CV_32F); 
    
    
    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////
    
    // 1. calculate the normalisation value
    // 2. perform a generic convolution with cropped edges
    
}

///////////////////////////////////////////////////////////////////////////////
// calculate the abs() of the x-Sobel and y-Sobel image
///////////////////////////////////////////////////////////////////////////////
void Filter::getAbsOfSobel(const cv::Mat &input_1, const cv::Mat &input_2, cv::Mat &output)
{
    if (input_1.empty() || input_2.empty())
    {
        std::cout << "One ore more inputs are empty!" << std::endl;
        return;
    }

    int rows = input_1.rows;
    int cols = input_1.cols;

    output.release();
    // create a float image initialized with zeros
    output = cv::Mat::zeros(rows, cols, CV_32F);
    
    
    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////
    
    // calculate the abs() of the x-Sobel and y-Sobel results
    
    
}

///////////////////////////////////////////////////////////////////////////////
// return the Binomial kernel
///////////////////////////////////////////////////////////////////////////////
cv::Mat Filter::getBinomial(uchar size)
{
    if (size == 3)
        return Binomial3;
    else if (size == 5)
        return Binomial5;
    else
        return cv::Mat();
}

///////////////////////////////////////////////////////////////////////////////
// return the Sobel kernel in X direction
///////////////////////////////////////////////////////////////////////////////
cv::Mat Filter::getSobelX(uchar size)
{
    if (size == 3)
        return Sobel3_X;
    else if (size == 5)
        return Sobel5_X;
    else
        return cv::Mat();
}

///////////////////////////////////////////////////////////////////////////////
// return the Sobel kernel in Y direction
///////////////////////////////////////////////////////////////////////////////
cv::Mat Filter::getSobelY(uchar size)
{
    if (size == 3)
        return Sobel3_Y;
    else if (size == 5)
        return Sobel5_Y;
    else
        return cv::Mat();
}

///////////////////////////////////////////////////////////////////////////////
// scale a Sobel image for better displaying
///////////////////////////////////////////////////////////////////////////////
void Filter::scaleSobelImage(const cv::Mat &input, cv::Mat &output)
{
    // find max value
    double min, max;
    cv::minMaxLoc(input, &min, &max);

    // scale the image
    input.convertTo(output, CV_32F, (0.5f / max), 0.5f);
}