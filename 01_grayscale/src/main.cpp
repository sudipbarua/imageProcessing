#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Timer.h"

void grayscale_cpp(const cv::Mat &input, cv::Mat &output)
{
    // get image size
    int rows = input.rows;
    int cols = input.cols;
    
    // make output a grayscale (8 bit) image with the same size as the input image
    output.release();
    output.create(rows, cols, CV_8U);
    
    // loop over all pixels of the input image
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            // input is a BGR image, therefore, every pixel has 3 values
            
            // input.at<uchar>(y,x) reads only 1 uchar value
            // note: there are other ways which allows the .at method to read all 3 BRG values at once
            
            // get the 3 BGR values (note: defining "int" variables inside the loops is not very efficient)
            int b = input.at<uchar>(row, col * 3);
            int g = input.at<uchar>(row, col * 3 + 1);
            int r = input.at<uchar>(row, col * 3 + 2);
            
            // build weighted average
            int gray = r * 0.299 + g * 0.587 + b * 0.114; 
            // write grayscaled value to the output image
            output.at<uchar>(row, col) = gray;
        }
    }
}

int main(int argc, char *argv[]) {
    // initialize timer (a very simple way to measure time, but not very precisely)
    INIT_TIMER
    
    // read image
    cv::Mat img = cv::imread("D:/projects/imageProcessing/01_grayscale/data/lena.tiff");
    // cv::Mat img = cv::imread("../data/lena.tiff");
    
    // convert to grayscale with OpenCV
    cv::Mat imgGrayCv;
    START_TIMER
    cv::cvtColor(img, imgGrayCv, cv::COLOR_BGR2GRAY);
    STOP_TIMER("Grayscale_OpenCV  ")
    
    // manually convert to grayscale with C++ function
    cv::Mat imgGray;
    START_TIMER
    grayscale_cpp(img, imgGray);
    STOP_TIMER("Grayscale_With_C++")
    
    // display images
    cv::imshow("Original Image", img);
    cv::imshow("Grayscale OpenCV", imgGrayCv);
    cv::imshow("Grayscale C++", imgGray);

    //wait for key pressed
    cv::waitKey();

    return 0;
}
