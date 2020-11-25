#include "CornerDetector.hpp"
#include <vector>

using namespace std;

CornerDetector::CornerDetector(string filename) 
{
    m_img = cv::imread(filename);
    if(m_img.empty())
    {
        cout << "\033[1;31mImage failed to open\033[0m" << endl;
        exit(-1);
    }
}

CornerDetector::~CornerDetector() {}

vector<pair<int, int>> CornerDetector::harrisDetector()
{
    return {{1,2}};
}

void CornerDetector::replaceImage(cv::Mat& img)
{
    m_img = img;
}