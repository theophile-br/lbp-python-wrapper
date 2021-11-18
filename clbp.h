//
// Created by teto on 18/11/2021.
//
#ifndef CLBP_CLBP_H
#define CLBP_CLBP_H

#include <opencv2/core/core.hpp>
#include <string>

/**
 * Array of float to string join by a char
 * @param array
 * @param size
 * @param del a delimiter char
 * @return the array join by a delimiteur
 */
std::string float_array_join(float array[], int size, char del = ',');

/**
 * Round a float number
 * @param value
 * @param prec
 * @return
 */
float roundoff(float value, unsigned char prec);

/**
 * Normalise image histogram by pixel
 * @param img
 * @param lbpHist
 */
void normalize_hist(cv::Mat &img, float lbpHist[256]);

/**
 * Do LBP on a center pixel
 * @param img the image
 * @param x vertical center pixel position
 * @param y horizontal center pixel position
 * @param channel the number of the channel
 * @return
 */
int lbp_encode_pixel(cv::Mat &img, int x, int y, int channel);

/**
 * LBP routine
 * @param img the image
 * @param lbpHist histograme result
 */
void img_2_lbp_hist(cv::Mat &img, float lbpHist[256]);

#endif //CLBP_CLBP_H
