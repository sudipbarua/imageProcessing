#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Timer.h"

////////////////////////////////////////////////////////////////////////////////////
// compute threshold image using the OpenCV function - only for reference
////////////////////////////////////////////////////////////////////////////////////
void threshold_cv(const cv::Mat &input, cv::Mat &output, int threshold)
{
    cv::threshold(input, output, threshold, 255, cv::THRESH_BINARY);
}

////////////////////////////////////////////////////////////////////////////////////
// compute threshold image by looping over the elements
////////////////////////////////////////////////////////////////////////////////////
void threshold_loop(const cv::Mat &input, cv::Mat &output, int threshold)
{
    int rows = input.rows;
    int cols = input.cols;
    
    // cv::Mat for result
    output.create(rows, cols, CV_8U);
    
    ///////////////////////////////
    // insert your code here ... 
    //////////////////////////////  

}

////////////////////////////////////////////////////////////////////////////////////
// compute threshold image by looping over the elements (pointer with index access)
////////////////////////////////////////////////////////////////////////////////////
void threshold_loop_ptr(const cv::Mat &input, cv::Mat &output, int threshold)
{
    int rows = input.rows;
    int cols = input.cols;
    
    // cv::Mat for result
    output.create(rows, cols, CV_8U);
    
    ///////////////////////////////
    // insert your code here ... 
    //////////////////////////////
    
}

////////////////////////////////////////////////////////////////////////////////////
// compute threshold image by looping over the elements (pointer arithmetic access)
////////////////////////////////////////////////////////////////////////////////////
void threshold_loop_ptr2(const cv::Mat &input, cv::Mat &output, int threshold)
{
    int rows = input.rows;
    int cols = input.cols;
    
    output.create(rows, cols, CV_8U);
    
    ///////////////////////////////
    // insert your code here ... 
    //////////////////////////////

}

int main(int argc, char *argv[])
{
    //default threshold value
    int thresholdValue = 128;

    //old threshold value
    int thresholdValueOld = -1;

    //read color image
    cv::Mat img = cv::imread("D:\\projects\\imageProcessing\\02_threshold\\data\\lena.tiff");

    //display color image
    cv::imshow("Image", img);

    //add trackbar to the color image window
    cv::createTrackbar("Threshold", "Image", &thresholdValue, 400, nullptr);

    //convert to grayscale
    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    //display grayscale
    cv::imshow("Grayscale", imgGray);

    //declare output variables
    cv::Mat output_cv;
    cv::Mat output_loop;
    cv::Mat output_loop_ptr;
    cv::Mat output_loop_ptr2;

    //endless loop
    while(true)
    {
        int key = cv::waitKey(10);
        if (key >= 0 && key < 255)
        {
            break; //leave endless loop
        }

        if (thresholdValue == thresholdValueOld) //threshold value was not changed
        {
            continue;
        }

        thresholdValueOld = thresholdValue;
        std::cout << std::endl;

        // begin processing ///////////////////////////////////////////////////////////

        INIT_TIMER

        START_TIMER
        threshold_cv(imgGray, output_cv, thresholdValue);
        STOP_TIMER("threshold_cv  \t")

        cv::imshow("threshold_cv", output_cv);


        START_TIMER
        threshold_loop(imgGray, output_loop, thresholdValue);
        STOP_TIMER("threshold_loop\t")

        cv::imshow("threshold_loop", output_loop);


        START_TIMER
        threshold_loop_ptr(imgGray, output_loop_ptr, thresholdValue);
        STOP_TIMER("threshold_loop_ptr\t")

        cv::imshow("threshold_loop_ptr", output_loop_ptr);


        START_TIMER
        threshold_loop_ptr2(imgGray, output_loop_ptr2, thresholdValue);
        STOP_TIMER("threshold_loop_ptr2\t")

        cv::imshow("threshold_loop_ptr2", output_loop_ptr2);

        // end processing /////////////////////////////////////////////////////////////
    }

    return 0;
}
