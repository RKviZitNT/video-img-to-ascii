#ifndef IMGASCIIC_H
#define IMGASCIIC_H

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

    void resize(int targetSize);
    void imgAsciiInit(std::string gradientStr, bool inverse);

public:
    Image(const std::string& path);
    void generateAsciiImg(int targetSize, std::string gradientStr, bool inverse);
    void write_to_terminal();
    void write_to_file(std::string filename);
};

#endif