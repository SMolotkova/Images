#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include "vert_gauss.h"

using namespace cv;

int main(int argc, char* argv[]) {

    Mat noise_photo = imread("shar.jpg");
    std::vector<double> matrix_b(noise_photo.rows * noise_photo.cols);
    std::vector<double> matrix_g(noise_photo.rows * noise_photo.cols);
    std::vector<double> matrix_r(noise_photo.rows * noise_photo.cols);
    for (int x = 0; x < noise_photo.rows; x++) {
        for (int y = 0; y < noise_photo.cols; y++) {
            Vec3b color = noise_photo.at<Vec3b>(x, y);
            matrix_b[x * noise_photo.cols + y] = color[0];
            matrix_g[x * noise_photo.cols + y] = color[1];
            matrix_r[x * noise_photo.cols + y] = color[2];
        }
    }
    int rows = noise_photo.rows;
    int cols = noise_photo.cols;
    matrix_b = transposition(matrix_b, rows, cols);
    matrix_g = transposition(matrix_g, rows, cols);
    matrix_r = transposition(matrix_r, rows, cols);
    int tmp = rows;
    rows = cols;
    cols = tmp;
    std::vector<double> sequence_blue = gauss_filter_sequence(matrix_b, rows, cols, 1, 7);
    std::vector<double> sequence_green = gauss_filter_sequence(matrix_g, rows, cols, 1, 7);
    std::vector<double> sequence_red = gauss_filter_sequence(matrix_r, rows, cols, 1, 7);
    sequence_blue = transposition(sequence_blue, rows, cols);
    sequence_green = transposition(sequence_green, rows, cols);
    sequence_red = transposition(sequence_red, rows, cols);
    tmp = rows;
    rows = cols;
    cols = tmp;
    Mat photo_after_gauss_filter_sequence(noise_photo.size(), noise_photo.type());
    for (int x = 0; x < noise_photo.rows; x++) {
        for (int y = 0; y < noise_photo.cols; y++) {
            photo_after_gauss_filter_sequence.at<Vec3b>(x, y)[0] = sequence_blue[x * noise_photo.cols + y];
            photo_after_gauss_filter_sequence.at<Vec3b>(x, y)[1] = sequence_green[x * noise_photo.cols + y];
            photo_after_gauss_filter_sequence.at<Vec3b>(x, y)[2] = sequence_red[x * noise_photo.cols + y];
        }
    }
    imwrite("Photo_after_gauss_filter_sequence.jpg", photo_after_gauss_filter_sequence);
    }