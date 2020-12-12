#ifndef __CORNER_DETECTOR_HPP__
#define __CORNER_DETECTOR_HPP__

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

namespace pzCV
{
    class CornerDetector
    {
        public:
            CornerDetector(); // constructor
            ~CornerDetector(); // destructor

        // member variables
        private:
            cv::Mat m_defaultKernel;

        public:
            std::vector<std::pair<int, int>> harrisDetector(cv::Mat&, cv::Mat&, string filter="box");
            void replaceImage(cv::Mat&);
            void replaceKernel(cv::Mat&);
            void nonMaximalSuppression(cv::Mat&, cv::Mat&, cv::Mat&);

        private:
            void computeGradientImage(cv::Mat&, cv::Mat&, cv::Mat&, cv::Mat&);

    };

}

#endif //__CORNER_DETECTOR_HPP__