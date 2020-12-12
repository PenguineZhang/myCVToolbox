#ifndef __UTILS_HPP__
#define __UTILS_HPP__

// #include <iostream>
#include <opencv2/opencv.hpp>

#define PI 3.1415926

// TODO: non maximal suppression
void nonMaximalSuppresion(cv::Mat& src, cv::Mat& dest, int& window_size);

///
///  generate 2d Gaussian kernel
///
///  \param kernel reference to the output kernel
///  \param row desired number of rows for the kernel
///  \param col desired number of columns for the kernel
///  \param mean_x desired number of columns for the kernel
///  \param mean_y desired number of columns for the kernel
///
void gaussianKernelGenerator(cv::Mat& kernel, int row, int col, double mean_x, double mean_y, double sigma_x, double sigma_y);

#endif //__UTILS_HPP__