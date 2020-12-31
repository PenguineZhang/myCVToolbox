#include "corner_detector/CornerDetector.hpp"
#include "utils/utils.hpp"

int main(int argc, char** argv)
{
    string file = argv[1];

    CornerDetector cd = CornerDetector();

    float data[5] = {-1, 8, 0, -8, 1};
    cv::Mat kernel = cv::Mat(1, 5, CV_32F, data) / 12;

    cv::Mat img = cv::imread(file, CV_8U);

    if(img.empty())
    {
        cout << "error in reading image\n";
        exit(-1);
    }

    img.convertTo(img, CV_32F);
    cv::Mat gauss_kernel = cv::Mat(cv::Size(3,3), CV_32F, cv::Scalar(0));

    gaussianKernelGenerator(gauss_kernel, 3, 3, 0.0, 0.0, 0.3, 0.3);

    cd.harrisDetector(img, kernel, gauss_kernel);

    return 0;
}
