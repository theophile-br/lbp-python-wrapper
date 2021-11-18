#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <filesystem>
#include "clbp.h"

using namespace std;
using namespace cv;
using namespace filesystem;

// HELP
// 1rth argument the file to process
// 2nd argument color mode 0: GRAYSCALE 1: COLOR

int main(int argc, char **argv) {
    string file_path;
    int color_mode = IMREAD_GRAYSCALE;
    if (argc == 1) {
        cout << "No arguments" << endl;
        return EXIT_FAILURE;
    }
    file_path = current_path().string() / path(string(argv[1]));
    if(argc == 3){
        color_mode = stoi(string(argv[2]));
    }
    Mat img = imread(file_path, color_mode);
    if(img.empty()){
        cout << "Image : " << file_path << " doesn't exist !" << endl;
        return EXIT_FAILURE;
    }
    float histogramme[256] = {0};
    img_2_lbp_hist(img,histogramme);
    cout << float_array_join(histogramme,256,',');
    return EXIT_SUCCESS;
}

// LBP FUNCTIONS

void img_2_lbp_hist(Mat &img, float lbpHist[256]) {
    for (int y = 1; y < img.rows - 1; y++) {
        for (int x = 1; x < img.cols - 1; x++) {
            for (int c = 0; c < img.channels(); c++) {
                int decimal_value = lbp_encode_pixel(img, x, y, c);
                lbpHist[decimal_value] = lbpHist[decimal_value] + 1;
            }
        }
    }
    // COMMENT / UNCOMMENT FOR HISTOGRAM NORMALISATION
    //normalize_hist(img, lbpHist);
}

int lbp_encode_pixel(Mat &img, int x, int y, int cn) {
    uchar bits[8];
    int center_pixel = img.at<Vec3b>(y, x).val[cn];

    bits[0] = (center_pixel >= img.at<Vec3b>(y - 1, x - 1).val[cn]) ? 1 : 0;
    bits[1] = (center_pixel >= img.at<Vec3b>(y - 1, x).val[cn]) ? 1 : 0;
    bits[2] = (center_pixel >= img.at<Vec3b>(y - 1, x + 1).val[cn]) ? 1 : 0;
    bits[3] = (center_pixel >= img.at<Vec3b>(y, x + 1).val[cn]) ? 1 : 0;
    bits[4] = (center_pixel >= img.at<Vec3b>(y + 1, x + 1).val[cn]) ? 1 : 0;
    bits[5] = (center_pixel >= img.at<Vec3b>(y + 1, x).val[cn]) ? 1 : 0;
    bits[6] = (center_pixel >= img.at<Vec3b>(y + 1, x - 1).val[cn]) ? 1 : 0;
    bits[7] = (center_pixel >= img.at<Vec3b>(y, x - 1).val[cn]) ? 1 : 0;

    int decimal_value = 0;
    for (int i = 0; i < 8; i++)
        decimal_value += pow(2, i) * bits[i];
    return decimal_value;
}

// UTILS FUNCTIONS

string float_array_join(float array[], int size, char del) {
    stringstream ss;
    ss.str();
    for (int i = 0; i < size; i++) {
        ss << array[i];
        if (i != size - 1)
            ss << del;
    }
    return ss.str();
}

float roundoff(float value, unsigned char prec) {
    float pow_10 = pow(10.0f, (float) prec);
    return round(value * pow_10) / pow_10;
}

void normalize_hist(Mat &img, float lbpHist[256]) {
    int imgSurface = img.cols * img.rows * img.channels();
    for (int i = 0; i < 256; i++) {
        lbpHist[i] = roundoff(lbpHist[i] / (float) imgSurface, 20);
    };
}

