#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

class CornerDetector
{
    public:
        CornerDetector(string filename); // constructor
        ~CornerDetector(); // destructor

    // member variables
    private:
        cv::Mat m_img;

    public: 
        std::vector<std::pair<int, int>> harrisDetector();
        void replaceImage(cv::Mat&);
    
};

