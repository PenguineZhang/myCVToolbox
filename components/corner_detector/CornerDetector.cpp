#include "CornerDetector.hpp"

#include <chrono>
#include <vector>

using namespace std;

CornerDetector::CornerDetector() {}

CornerDetector::~CornerDetector() {}

void CornerDetector::computeGradientImage(cv::Mat& img, cv::Mat& kernel, cv::Mat& Ix, cv::Mat& Iy)
{
    // ddepth=-1 -> use the same depth as the source   (third parameter)
    if(kernel.rows > kernel.cols)
    {
        cv::filter2D(img, Ix, -1, kernel.t());
        cv::filter2D(img, Iy, -1, kernel);
    }
    else
    {
        cv::filter2D(img, Ix, -1, kernel);
        cv::filter2D(img, Iy, -1, kernel.t());
    }
}

vector<pair<int, int>> CornerDetector::harrisDetector(cv::Mat& img, cv::Mat& kernel, cv::Mat& filter)
{
    cv::Mat Ix, Iy;
    computeGradientImage(img, kernel, Ix, Iy);

    if(Ix.empty())
    {
        cout << "\033[1;31mIx is empty\033[0m" << endl;
        exit(-1);
    }

    if(Iy.empty())
    {
        cout << "\033[1;31mIy is empty\033[0m" << endl;
        exit(-1);
    }

    double epsilon = 1e-1;

    // precompute I_x^2, I_y^2, I_x*I_y
    cv::Mat I_x2 = Ix.mul(Ix);
    cv::Mat I_y2 = Iy.mul(Iy);
    cv::Mat I_xy = Ix.mul(Iy);

    cv::Mat corners = cv::Mat(img.rows, img.cols, CV_32F);

    int row_start = 1, row_end = img.rows - 1;
    int col_start = 1, col_end = img.cols - 1;

    auto start = std::chrono::high_resolution_clock::now();
    int kernel_element_size = kernel.total() * kernel.total();

    float eigen_thresh = 0.2;

    // vector<pair<int, int>> corners;
    cv::Mat eigenvalues = cv::Mat(cv::Size(1, 2), CV_32F, cv::Scalar(0));

    cv::Mat A = cv::Mat(cv::Size(2,2), CV_32F, cv::Scalar(0));

    for(int i = row_start; i < row_end; i++)
    {
        for(int j = col_start; j < col_end; j++)
        {
            // TODO: inplment other weighting matrix in the future
            // so far the box filter is easiest to implement
            A.at<float>(0, 0) = cv::sum(I_x2(cv::Range(i - 1, i + 2), cv::Range(j - 1, j + 2)).mul(filter))[0];//.mul(filter))[0];
            A.at<float>(1, 1) = cv::sum(I_y2(cv::Range(i - 1, i + 2), cv::Range(j - 1, j + 2)).mul(filter))[0];// / kernel_element_size;
            A.at<float>(1, 0) = cv::sum(I_xy(cv::Range(i - 1, i + 2), cv::Range(j - 1, j + 2)).mul(filter))[0];// / kernel_element_size;
            A.at<float>(0, 1) = A.at<float>(1, 0);
            // corners.at<float>(i, j) = (2 * cv::determinant(A) /  (cv::trace(A)[0] + epsilon)) / 255;
            cv::eigen(A, eigenvalues);
            if(1/eigenvalues.at<float>(0,1) < eigen_thresh)
            {
                // corners.push_back(make_pair(i, j));
                corners.at<float>(i, j) = (2 * cv::determinant(A) /  (cv::trace(A)[0] + epsilon)) / 255;
            }

        }
    }
    // cout << corners.rows << " " << corners.cols << endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    cout << duration.count() << endl;

    cv::imshow("corner", corners);
    // cv::imwrite("corners2.jpg", corners*255);
    cv::waitKey(0);

    // return corners;
    return {{1,2}};
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
