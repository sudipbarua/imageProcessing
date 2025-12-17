#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Dct.h"

int main(int argc, char *argv[])
{
    // programm arguments

    // run programm with: ./dct 8 1
    // first number: N
    // second number: Q

    std::cout << "arg: (1) N [default:8]   (2) Q [default:1]\n";
    int N = (argc > 1) ? atoi(argv[1]) : 8;
    int Q = (argc > 2) ? atoi(argv[2]) : 1;

    if (Q < 0)
    {
        std::cout << "Q to low\n";
        Q = 0;
    }
    else if (Q > N - 1)
    {
        std::cout << "Q to high\n";
        Q = N - 1;
    }
    std::cout << "N=" << N << "  Q=" << Q << std::endl;

    //create class instance
    Dct *dct = new Dct(N, Q);

    // read image
    cv::Mat img = cv::imread(INPUTIMAGE);
    //cv::imshow("Image BGR", img);

    // grayscale
    cv::Mat imgGray;

    // use complete image
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    //if the calculations take to long, use only a part of the image:
    //cv::cvtColor(img(cv::Rect(128, 128, 256, 256)), imgGray, cv::COLOR_BGR2GRAY);

    //show original image
    cv::imshow("1 Grayscale Image", imgGray);

    // send image to class instance
    dct->setImage(imgGray);

    // step 1: dct
    dct->startDct();
    dct->showImageDct("2 DCT");

    // step 2: quantize
    dct->quantize();

    // step 3: idct
    dct->startIdct();
    dct->showImageIdct("3 IDCT");
    //dct->saveImageIdct();

    //wait for key pressed
    cv::waitKey();

    return 0;
}
