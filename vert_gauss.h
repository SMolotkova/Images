#include <vector>
#include <random>
#include <ctime>
#include <cmath>

int clamp(int n, int upper, int lower) {
    return n <= lower ? lower : n >= upper ? upper : n;
};
std::vector<double> createRandomMatrix(int rows, int cols) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<double> result(rows * cols);
    for (int i = 0; i < rows * cols; i++)
        result[i] = gen() % 256;
    return result;};
std::vector<double> transposition(const std::vector<double>& matrix, int rows, int cols) {
    std::vector<double> result(rows * cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i + j * rows] = matrix[i * cols + j];
        }
    }
    return result;};
std::vector<double> createGaussianKernel(int radius, int sigma) {
    const int size = 2 * radius + 1;
    double norm = 0;
    std::vector<double> kernel(size * size);
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            int idx = (i + radius) * size + j + radius;
            kernel[idx] = exp(-(i * i + j * j) / (sigma * sigma));
            norm += kernel[idx];
        }
    }
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            kernel[i * size + j] /= norm;
    return kernel;
};
std::vector<double> gauss_filter_sequence(const std::vector<double>& matrix, int rows, int cols, int radius, int sigma) {
    std::vector<double> resultMatrix(rows * cols);
    const unsigned int size = 2 * radius + 1;
    std::vector<double> kernel = createGaussianKernel(radius, sigma);
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            double res = 0;
            for (int i = -radius; i <= radius; i++) {
                for (int j = -radius; j <= radius; j++) {
                    int idx = (i + radius) * size + j + radius;
                    int x_ = clamp(x + j, rows - 1, 0);
                    int y_ = clamp(y + i, cols - 1, 0);
                    double value = matrix[x_ * cols + y_];
                    res += value * kernel[idx];
                }
            }
            res = clamp(res, 255, 0);
            resultMatrix[x * cols + y] = res;
        }
    }
    return resultMatrix;
};

