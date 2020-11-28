#include "CornerDetector.hpp"
#include <chrono>
#include <vector>

using namespace std;

CornerDetector::CornerDetector  (string filename)
{
    this->m_img = cv::imread(filename, CV_8U);
    this->m_img.convertTo(this->m_img, CV_32F);

    if(m_img.empty())
    {
        cout << "\033[1;31mImage failed to open\033[0m" << endl;
        exit(-1);
    }

}

CornerDetector::~CornerDetector() {}

void CornerDetector::computeGradientImage(cv::Mat& kernel)
{
    // ddepth=-1 -> use the same depth as the source   (third parameter)
    if(kernel.rows > kernel.cols)
    {
        cv::filter2D(this->m_img, this->m_Ix, -1, kernel.t());
        cv::filter2D(this->m_img, this->m_Iy, -1, kernel);
    }
    else
    {
        cv::filter2D(this->m_img, this->m_Ix, -1, kernel);
        cv::filter2D(this->m_img, this->m_Iy, -1, kernel.t());
    }
}

vector<pair<int, int>> CornerDetector::harrisDetector(cv::Mat& kernel)
{
    this->computeGradientImage(kernel);
    if(this->m_Ix.empty())
    {
        cout << "\033[1;31mIx is empty\033[0m" << endl;
        exit(-1);
    }

    if(this->m_Iy.empty())
    {
        cout << "\033[1;31mIy is empty\033[0m" << endl;
        exit(-1);
    }

    double epsilon = 1e-1;

    // precompute I_x^2, I_y^2, I_x*I_y
    cv::Mat I_x2 = this->m_Ix.mul(this->m_Ix);
    cv::Mat I_y2 = this->m_Iy.mul(this->m_Iy);
    cv::Mat I_xy = this->m_Ix.mul(this->m_Iy);

    cv::Mat corners = cv::Mat(this->m_img.rows, this->m_img.cols, CV_32F);


    cv::Mat filter = cv::Mat(cv::Size(3,3), CV_32F, cv::Scalar(1)) / 9;

    cv::Mat A = cv::Mat(cv::Size(2,2), CV_32F, cv::Scalar(0));

    int row_start = 1, row_end = this->m_img.rows - 1;
    int col_start = 1, col_end = this->m_img.cols - 1;

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = row_start; i < row_end; i++)
    {
        for(int j = col_start; j < col_end; j++)
        {
            A.at<float>(0, 0) = cv::sum(I_x2(cv::Range(i - 1, i + 2), cv::Range(j - 1, j + 2)).mul(filter))[0];
            A.at<float>(1, 1) = cv::sum(I_y2(cv::Range(i - 1, i + 2), cv::Range(j - 1, j + 2)).mul(filter))[0];
            A.at<float>(1, 0) = cv::sum(I_xy(cv::Range(i - 1, i + 2), cv::Range(j - 1, j + 2)).mul(filter))[0];
            A.at<float>(0, 1) = A.at<float>(1, 0);
            corners.at<float>(i, j) = (2 * cv::determinant(A) /  (cv::trace(A)[0] + epsilon)) / 255;
            // cout << corners.at<float>(i, j) << endl;
        }
    }
    // cout << corners.rows << " " << corners.cols << endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    cout << duration.count() << endl;

    cv::imshow("corner", corners);
    cv::waitKey(0);

    return {{1,2}};
}

void CornerDetector::replaceImage(cv::Mat& img)
{
    m_img = img;
}

void CornerDetector::replaceKernel(cv::Mat& kernel)
{

}

void CornerDetector::nonMaximalSuppression(cv::Mat& src, cv::Mat& des, cv::Mat& window)
{
    assert(src.rows == des.rows);
    assert(src.cols == des.cols);

    cv::Size window_size = window.size();
    int width = window_size.width;
    int height = window_size.height;

    for(int i = height/2; i < src.rows - height/2; i++)
    {
        for(int j = width/2; j < src.cols - width/2; j++)
        {
            cv::Mat ROI = src(cv::Range(i - height/2, i + height/2), cv::Range(j - width/2, j + width/2));

            // TODO: implement max masking here
            cv::Mat mask = cv::Mat(height, width, src.type(), cv::Scalar(0));


            des(cv::Range(i - height/2, i + height/2), cv::Range(j - width/2, j + width/2)) = mask;
        }
    }
}