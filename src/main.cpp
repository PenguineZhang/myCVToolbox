#include "CornerDetector.hpp"

int main(int argc, char** argv)
{
    string file = "test.png";

    pzCV::CornerDetector cd = pzCV::CornerDetector();

    float data[5] = {-1, 8, 0, -8, 1};
    cv::Mat kernel = cv::Mat(1, 5, CV_32F, data) / 12;

    cv::Mat img = cv::imread(file, CV_8U);

    if(img.empty())
    {
        cout << "error in reading image\n";
        exit(-1);
    }

    img.convertTo(img, CV_32F);
    cd.harrisDetector(img, kernel);

    return 0;
}