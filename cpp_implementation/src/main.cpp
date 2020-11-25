#include "CornerDetector.hpp"

int main(int argc, char** argv)
{
    string file = "/home/peng/code_playground/python_code/myCVToolbox/test.png";

    CornerDetector cd = CornerDetector(file);

    float data[5] = {-1, 8, 0, -8, 1};
    cv::Mat kernel = cv::Mat(1, 5, CV_32F, data) / 12;



    cd.harrisDetector(kernel);


    return 0;
}