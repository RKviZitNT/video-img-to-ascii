#ifndef IMGASCIIC_H
#define IMGASCIIC_H

#include <opencv2/opencv.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

class Ascii {
private:
    std::string pathToFile;

    std::vector<char> gradient, asciiImg;

    int width, height;
    double scale;

    int targetSize, contrast, brightness;
    bool inverse;
    std::string gradientStr;

    void resize(cv::Mat& frame);
    void frameAsciiConvert(cv::Mat& frame);

    void generateImgAscii();

public:
    Ascii(std::string pathToFile);
    void generateAscii(std::string gradientStr, int targetSize, int brightness, int contrast, bool inverse);
    void write_to_terminal();
    void write_to_file(std::string filename);
};

#endif