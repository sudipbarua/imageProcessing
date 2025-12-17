#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Dct.h"


///////////////////////////////////////////////////////////////////////////////
// DCT & IDCT functions
///////////////////////////////////////////////////////////////////////////////

void Dct::calcDct(const cv::Mat &input, cv::Mat &output, const int N, const int blocksX, const int blocksY)
{
    // input image: imageOrg (float)
    // output image: imageDct (float, already the correct size)
    // block size: N
    // number of blocks: blocksX, blocksY
		
    for (int bx = 0; bx < blocksX; ++bx){
		int posx = N * bx;
		for (int by = 0; by < blocksY; ++by){
			int posy = N * by;
			
			cv::Rect ROI = cv::Rect(posx, posy, N, N);
			
			cv::Mat iBlock = input(ROI);
			cv::Mat oBlock = output(ROI);
			
			dctTransform(iBlock, oBlock, N);
		}
	}
    
}

void Dct::dctTransform (const cv::Mat &input, cv::Mat &output, const int N){
	
	for (int u = 0; u < N; ++u){
		float *pOutput = output.ptr<float>(u);
		float cu = (u==0)? oneDivSqrtTwo : 1;
		
		for (int v = 0; v < N; ++v){
			float cv = (v==0)? oneDivSqrtTwo : 1;
			float sum = 0.0f;
			
			for (int x = 0; x < N; ++x){
				const float *pInput = input.ptr<float>(x);
								
				float cosx = piFactor * (2 * x + 1) * u;
				
				for (int y = 0; y < N; ++y){
					float cosy = piFactor * (2 * y + 1) * v;
					
					sum += (*pInput * cosx * cosy);
					++pInput;
				}
			}
			sum = 0.25 * cu * cv * sum;
			*pOutput = sum;
			++pOutput;
		}
	}
	
	
}

void Dct::calcIdct(const cv::Mat &input, cv::Mat &output, const int N, const int blocksX, const int blocksY)
{
    // input image: imageQuantized (float)
    // output image: imageIdct (float, already the correct size)
    // block size: N
    // number of blocks: blocksX, blocksY
	
	for (int bx = 0; bx < blocksX; bx++){
		int posx = bx * N;
		for (int by = 0; by < blocksY; by++){
			int posy = by * N;
			
			cv::Rect ROI(posx, posy, N, N);
			cv::Mat iBlock = input(ROI);
			cv::Mat oBlock = output(ROI);
			
			idctTransform(iBlock, oBlock, N);
		}
	}

    
}

void idctTransform(const cv::Mat &input, cv::Mat &output, const int N){
	
	float sum = 0.0f;
	for (int y =0; y < N; ++y){
		float *pOutput = output.ptr<float>(y);
		for (int x =0; x < N; ++x){
			for (int v =0; v < N; ++v){
				
				const float *pInput = input.ptr<float>(v);
				float cv = (v==0)? oneDivSqrtTwo : 1; 
				float cosy = piFactor * (2 * v +1) * y;
				
				for (int u =0; u < N; ++u){
					float cu = (u==0)? oneDivSqrtTwo : 1;
					float cosx = piFactor * (2 * u +1) * x;
					
					sum += *pInput * cosx * cosy * cu * cv;
					++pInput;
				}
				
			}
			sum *= 0.25;
			*pOutput = sum;
			++pOutput;
		}
		
	}
}

///////////////////////////////////////////////////////////////////////////////
// other functions which use the DCT and IDCT functions
//
// note: some parameters and all images are stored inside the class instance
///////////////////////////////////////////////////////////////////////////////

Dct::Dct(const int _N, const int _Q)
{
    // store arguments in the class instance
    N = _N;
    Q = _Q;

    // calculate values: only once
    piFactor = float(CV_PI) / 2.0f / float(N);
    oneDivSqrtTwo = 1.0f / sqrt(2);
}

Dct::~Dct(){}


///////////////////////////////////////////////////////////////////////////////
// 1. some functions to convert and show the images
// (to spare you the trouble of converting between float and uchar)
///////////////////////////////////////////////////////////////////////////////

void Dct::setImage(const cv::Mat &input)
{
    input.convertTo(imageOrg, CV_32F);
    cols = input.cols;
    rows = input.rows;
    colsCont = cols;
    rowsCont = rows;
    if (input.isContinuous())
    {
        colsCont = rowsCont * colsCont;
        rowsCont = 1;
    }
    blocksX = cols / N;
    blocksY = rows / N;
    imageUchar.release();
    imageUchar.create(rows, cols, CV_8U);

    imageDct.release();
    imageDct.create(rows, cols, CV_32F);
    imageQuantized.release();
    imageQuantized.create(rows, cols, CV_32F);
    imageIdct.release();
    imageIdct.create(rows, cols, CV_32F);
}

void Dct::convertToUchar(const cv::Mat &input)
{
    float min = input.at<float>(0, 0);
    float max = min;
    for (int r = 0; r < rowsCont; ++r)
    {
        const float *pInput = input.ptr<float>(r);
        for (int c = 0; c < colsCont; ++c)
        {
            if (*pInput < min)
                min = *pInput;
            else if (*pInput > max)
                max = *pInput;
            ++pInput;
        }
    }
    max = (max - min) / 255.0f;
    for (int r = 0; r < rowsCont; ++r)
    {
        const float *pInput = input.ptr<float>(r);
        uchar *pOutput = imageUchar.ptr<uchar>(r);
        for (int c = 0; c < colsCont; ++c)
        {
            *pOutput = round((*pInput - min) / max);
            ++pInput;
            ++pOutput;
        }
    }
}

void Dct::showImageOrgFloat(std::string name)
{
    cv::imshow(name + "(imageOrg, float)", imageOrg);
}

void Dct::showImageOrg(std::string name)
{
    convertToUchar(imageOrg);
    cv::imshow(name + "(imageOrg, uchar)", imageUchar);
}

void Dct::showImageDctFloat(std::string name)
{
    cv::imshow(name + "(imageDct, float)", imageDct);
}

void Dct::showImageDct(std::string name)
{
    convertToUchar(imageDct);
    cv::imshow(name + "(imageDct, uchar)", imageUchar);
}

void Dct::showImageQuantizedFloat(std::string name)
{
    cv::imshow(name + "(imageQuantized, float)", imageQuantized);
}

void Dct::showImageQuantized(std::string name)
{
    convertToUchar(imageQuantized);
    cv::imshow(name + "(imageQuantized, uchar)", imageUchar);
}

void Dct::showImageIdctFloat(std::string name)
{
    cv::imshow(name + "(imageIdct, float)", imageIdct);
}

void Dct::showImageIdct(std::string name)
{
    convertToUchar(imageIdct);
    cv::imshow(name + "(imageIdct, uchar)", imageUchar);
}

void Dct::saveImageIdct()
{
    // save image as png file
    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    std::string filename = "output_n" + std::to_string(N) + "_q" + std::to_string(Q) + ".png";
    cv::imwrite(filename, imageIdct, compression_params);
    std::cout << "image saved: " << filename << std::endl;
}


///////////////////////////////////////////////////////////////////////////////
// 2. DCT
///////////////////////////////////////////////////////////////////////////////

void Dct::startDct()
{
    calcDct(imageOrg, imageDct, N, blocksX, blocksY);
    imageDct.copyTo(imageQuantized);
}


///////////////////////////////////////////////////////////////////////////////
// 3. Quantizaton
///////////////////////////////////////////////////////////////////////////////

void Dct::quantize()
{
    // primitive quantizaton, JPEG uses much better one
    int bx, by, posx;
    for (bx = 0; bx < blocksX; ++bx)
    {
        posx = N * bx;
        for (by = 0; by < blocksY; ++by)
        {
            quantizeSub(posx, N * by);
        }
    }
}

void Dct::quantizeSub(int posx, int posy)
{
    int x, y;

    for (x = 0; x < N; ++x)
    {
        for (y = 0; y < N; ++y)
        {
            if (x + y > Q)
                imageQuantized.at<float>(posy + y, posx + x) = 0.0f;
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
// 4. IDCT
///////////////////////////////////////////////////////////////////////////////

void Dct::startIdct()
{
    calcIdct(imageQuantized, imageIdct, N, blocksX, blocksY);
}
