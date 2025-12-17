#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Filter.h"
#include "Timer.h"
#include "imshow_multiple.h"

int main(int argc, char *argv[])
{
    //read image
    cv::Mat img = cv::imread(INPUTIMAGE);

    //convert to grayscale
    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    // convert to a float image
    cv::Mat imgGray_float;
    imgGray.convertTo(imgGray_float, CV_32F, 1.0/255.0);
    
    //declare output variables
    cv::Mat imgSmoothed3x3, imgSmoothed5x5;
    cv::Mat img_x_Sobel3x3, img_y_Sobel3x3, img_x_Sobel5x5, img_y_Sobel5x5;
    cv::Mat imgAbsSobel3x3, imgAbsSobel5x5;

    //create class instances
    Filter *filter = new Filter();

    // begin processing ///////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////
    // Binomial filter with pre-defined kernels
    //////////////////////////////////////////////////////////////////////////////
    filter->convolve_3x3(imgGray_float, imgSmoothed3x3, filter->getBinomial(3));
    filter->convolve_generic(imgGray_float, imgSmoothed5x5, filter->getBinomial(5));
    imshow_multiple("Gaussian Filter", 3, &imgGray_float, &imgSmoothed3x3, &imgSmoothed5x5);

    
    //////////////////////////////////////////////////////////////////////////////
    // x-Sobel filter with pre-defined kernels
    //////////////////////////////////////////////////////////////////////////////
    filter->convolve_3x3(imgGray_float, img_x_Sobel3x3, filter->getSobelX(3));
    filter->convolve_generic(imgGray_float, img_x_Sobel5x5, filter->getSobelX(5));
    
    // new image value scale -> so we can see more
    filter->scaleSobelImage(img_x_Sobel3x3, img_x_Sobel3x3);
    filter->scaleSobelImage(img_x_Sobel5x5, img_x_Sobel5x5);
    imshow_multiple("Sobel Filter X", 3, &imgGray_float, &img_x_Sobel3x3, &img_x_Sobel5x5);

    
    //////////////////////////////////////////////////////////////////////////////
    // y - Sobel filter with pre-defined kernels
    //////////////////////////////////////////////////////////////////////////////
    filter->convolve_3x3(imgGray_float, img_y_Sobel3x3, filter->getSobelY(3));
    filter->convolve_generic(imgGray_float, img_y_Sobel5x5, filter->getSobelY(5));
    
    // new image value scale -> so we can see more
    filter->scaleSobelImage(img_y_Sobel3x3, img_y_Sobel3x3);
    filter->scaleSobelImage(img_y_Sobel5x5, img_y_Sobel5x5);
    imshow_multiple("Sobel Filter Y", 3, &imgGray_float, &img_y_Sobel3x3, &img_y_Sobel5x5);

    
    //////////////////////////////////////////////////////////////////////////////
    // calculate the abs() of the Sobel images
    //////////////////////////////////////////////////////////////////////////////
    filter->getAbsOfSobel(img_x_Sobel3x3, img_y_Sobel3x3, imgAbsSobel3x3);
    filter->getAbsOfSobel(img_x_Sobel5x5, img_y_Sobel5x5, imgAbsSobel5x5);
    imshow_multiple("Abs() Sobel", 2, &imgAbsSobel3x3, &imgAbsSobel5x5);


    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////
    
    // e.g. seperated filtering

    // end processing /////////////////////////////////////////////////////////////

    //wait for key pressed
    cv::waitKey();

    return 0;
}
