#ifndef DCT_H
#define DCT_H

#include <opencv2/core/core.hpp>

class Dct
{
public:
    Dct(const int _N, const int _Q);
    ~Dct();
    void setImage(const cv::Mat &input);
    void startDct();
    void startIdct();
    void quantize();

    void showImageOrg(std::string name);
    void showImageOrgFloat(std::string name);
    void showImageDct(std::string name);
    void showImageDctFloat(std::string name);
    void showImageQuantized(std::string name);
    void showImageQuantizedFloat(std::string name);
    void showImageIdct(std::string name);
    void saveImageIdct();
    void showImageIdctFloat(std::string name);

private:
    void calcDct(const cv::Mat &input, cv::Mat &output, const int N, const int blocksX, const int blocksY);
    void calcIdct(const cv::Mat &input, cv::Mat &output, const int N, const int blocksX, const int blocksY);
    void convertToUchar(const cv::Mat & input);
    void dctTransform(const cv::Mat &input, cv::Mat &output, const int N);
    void idctTransform(const cv::Mat &input, cv::Mat &output, const int N);
    void quantizeSub(int posx, int posy);

    int blocksX, blocksY;
    int cols, rows;
    int colsCont, rowsCont;
    int N;
    int Q;

    float oneDivSqrtTwo, piFactor;

    cv::Mat imageUchar;
    cv::Mat imageOrg;
    cv::Mat imageDct;
    cv::Mat imageQuantized;
    cv::Mat imageIdct;
};

#endif /* DCT_H */
