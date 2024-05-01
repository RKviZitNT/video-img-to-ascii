#ifndef HEADER
#define HEADER

#include <opencv2/opencv.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

class Image {
private:
    cv::Mat image;

    std::vector<char> gradient, asciiImg;

    int width, height;
    double scale;

    int targetSize, contrast, brightness;
    bool inverse;
    std::string gradientStr;

    void resize();
    void imgAsciiInit();

public:
    Image(const std::string& path);
    void generateAsciiImg(std::string gradientStr, int targetSize, int brightness, int contrast, bool inverse);
    void write_to_terminal();
    void write_to_file(std::string filename);
};

#endif