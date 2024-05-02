#ifndef HEADER
#define HEADER

#include <opencv2/opencv.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

class Ascii {
private:
    std::string pathToFile;

    std::vector<char> gradient, asciiFrame;

    int width, height;
    double scale;

    int targetSize, contrast, brightness;
    bool inverse;
    std::string gradientStr;

    void resize(cv::Mat& frame);
    void AsciiInit(cv::Mat& frame);

    void write_to_terminal();

    void generateAsciiImage();
    void generateAsciiVideo();

public:
    Ascii(std::string pathToFile);
    void generateAscii(std::string gradientStr, int targetSize, int brightness, int contrast, bool inverse);
    
    void saveAsciiImage(const std::string& outputPath);
};

#endif