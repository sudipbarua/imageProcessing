#include <iostream>
#include <cmath>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Segmentation.h"

////////////////////////////////////////////////////////////////////////////////////
// constructor and destructor
////////////////////////////////////////////////////////////////////////////////////
Segmentation::Segmentation(){}

Segmentation::~Segmentation(){}

////////////////////////////////////////////////////////////////////////////////////
// Cut template image from input and save as file
////////////////////////////////////////////////////////////////////////////////////
void Segmentation::cutAndSave(const cv::Mat &input, cv::Point origin, cv::Size size, const cv::String &filename)
{
    // define rectangle from origin and size
    cv::Rect rect(origin, size);

    // cut the rectangle and create template
    cv::Mat templ = input(rect);

    // save template to file
    cv::imwrite(filename, templ);
}

////////////////////////////////////////////////////////////////////////////////////
// Compute normalized cross correlation function
////////////////////////////////////////////////////////////////////////////////////
void Segmentation::crossCorrelate(const cv::Mat &input, const cv::Mat &templ, cv::Mat &output)
{
    int rows = input.rows;
    int cols = input.cols;

    int tRows = templ.rows;
    int tCols = templ.cols;

    output.release();

    ///////////////////////////////
    // insert your code here ...
    //////////////////////////////
    
    // create a float image for the output;
    output = cv::Mat((rows - tRows +1), (cols - tCols +1), CV_32F);
    
	if (templ.isContinuous()){
		tRows = tRows * tCols;
		tCols = 1;
	}
	
	double normFactor_tmpl = 0;
	for (int tr = 0; tr < tRows; ++tr){
		const float *pTempl = templ.ptr<float>(tr);
		for (int tc = 0; tc < tCols; ++tc){
			normFactor_tmpl += pow(*pTempl, 2);
			++pTempl;
		}
	}
	
	normFactor_tmpl = sqrt(normFactor_tmpl);
	
	tRows = templ.rows;
    tCols = templ.cols;
	
	// calculate and normalize cross correlation
	
	for (int r =0; r < (rows - tRows +1); ++r)
	{
		float *pOutput = output.ptr<float>(r);
		
		for (int c =0; c < (cols - tCols +1); ++c)
		{
			float result = 0.0f;
			float normFactor_input = 0.0f;
			
			for (int tr = 0; tr < tRows; ++tr)
			{
				const float *pTempl = templ.ptr<float>(tr);
				const float *pInput = input.ptr<float>(r + tr) + c;
				
				for (int tc = 0; tc < tCols; ++tc)
				{
					normFactor_input += pow(*pInput, 2);
					result += (*pTempl) * (*pInput);
					
					++pTempl;
					++pInput;
				}
			}
			normFactor_input = sqrt(normFactor_input);
			float normFactor = normFactor_input * normFactor_tmpl;
			result /= normFactor;
			
			*pOutput = result;
			++pOutput;
		}
	}
    

}

////////////////////////////////////////////////////////////////////////////////////
// Find brightest pixel and return its coordinates as Point
////////////////////////////////////////////////////////////////////////////////////
cv::Point Segmentation::findMaximum(const cv::Mat &input)
{
    // declare array to hold the indizes
    int maxIndex[2];

    // find the maximum
    cv::minMaxIdx(input, 0, 0, 0, maxIndex);

    // create Point and return
    return cv::Point(maxIndex[1], maxIndex[0]);
}

////////////////////////////////////////////////////////////////////////////////////
// Add a black rectangle to an image
////////////////////////////////////////////////////////////////////////////////////
void Segmentation::drawRect(const cv::Mat &input, cv::Point origin, cv::Size size, cv::Mat &output)
{
    // define rectangle from origin and size
    cv::Rect rect(origin, size);

    // copy input image to output
    output = input.clone();

    // draw the rectangle
    cv::rectangle(output, rect, 0, 2);
}

