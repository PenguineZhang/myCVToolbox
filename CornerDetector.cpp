#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("/Users/pengzhang/projects/myCVToolbox/test.png");

    if(img.empty())
    {
        std::cout << "invalid image" << std::endl;
        return -1;
    }

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::imshow("img", img);
    cv::waitKey(0);

    return 0;
} 