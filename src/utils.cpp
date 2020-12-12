#include "utils.hpp"

void nonMaximalSuppresion(cv::Mat &src, cv::Mat &dest, int &window_size)
{
}

void gaussianKernelGenerator(cv::Mat &kernel, int row, int col, double mean_x, double mean_y, double sigma_x, double sigma_y)
{
    kernel = cv::Mat(cv::Size(row, col), CV_32F, cv::Scalar(0));

    // bivariate gaussian distribution with independent x and y
    // float norm_coeff = 1 / (2 * PI * sigma_x * sigma_y);   // uncomment coefficient if you need it
    //                    1         (-1/2 * (x - µ_x)^2/σ_x^2 + (y - µ_y)^2/σ_y^2)
    //   N(x, y) = ------------   e
    //              2 π σ_1 σ_2
    for (int i = -row / 2; i < row / 2 + 1; i++)
    {
        for (int j = -col / 2; j < col / 2 + 1; j++)
        {
            kernel.at<float>(i + row / 2, j + col / 2) = exp(-0.5 * (pow((i - mean_x) / sigma_x, 2) + pow((j - mean_y) / sigma_y, 2)));
        }
    }

    std::cout << kernel << std::endl;
}