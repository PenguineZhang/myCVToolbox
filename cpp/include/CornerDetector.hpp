#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

class CornerDetector
{
    public:
        CornerDetector(string); // constructor
        ~CornerDetector(); // destructor

    // member variables
    private:
        cv::Mat m_img;
        cv::Mat m_defaultKernel;
        cv::Mat m_Ix;
        cv::Mat m_Iy;

    public:
        std::vector<std::pair<int, int>> harrisDetector(cv::Mat&);
        void replaceImage(cv::Mat&);
        void replaceKernel(cv::Mat&);
        void nonMaximalSuppression(cv::Mat&, cv::Mat&, cv::Mat&);

    private:
        void computeGradientImage(cv::Mat&);

};

