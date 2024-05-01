#include "asciic.h"

Ascii::Ascii(std::string pathToFile) : pathToFile(pathToFile) {}

void Ascii::resize(cv::Mat& frame) {
    if (frame.cols > frame.rows) {
        scale = (double)targetSize / frame.cols;
        this->width = targetSize;
        this->height = frame.rows * scale;
    } else {
        scale = (double)targetSize / frame.rows;
        this->width = frame.cols * scale;
        this->height = targetSize;
    }

    cv::resize(frame, frame, cv::Size(width, height));
}

void Ascii::frameAsciiConvert(cv::Mat& frame) {
    gradient.assign(gradientStr.begin(), gradientStr.end());

    int index, contrastGradient = std::round((gradient.size() - 1) / 100.0f * static_cast<float>(100 - contrast));
    double averageBrightness = 256 - brightness;

    double darkBrightness = averageBrightness / contrastGradient;
    double lightBrightness = (256.0f - averageBrightness) / (gradient.size() - 1 - contrastGradient);

    for (int j = 0; j < frame.rows; ++j) {
        for (int i = 0; i < frame.cols; ++i) {
            uchar brightnessPixel = frame.at<uchar>(j, i);
            if (brightnessPixel < averageBrightness) {
                if (inverse)
                    index = gradient.size() - 1 - std::round(brightnessPixel / darkBrightness);
                else
                    index = std::round(brightnessPixel / darkBrightness);
            } else {
                if (inverse)
                    index = contrastGradient + (gradient.size() - 1 - std::round((brightnessPixel - averageBrightness) / lightBrightness));
                else
                    index = contrastGradient + std::round((brightnessPixel - averageBrightness) / lightBrightness);
            }

            asciiImg.push_back(gradient[index]);
        }
    }
}

void Ascii::generateAscii(std::string gradientStr, int targetSize, int brightness, int contrast, bool inverse) {
    this->gradientStr = gradientStr;
    this->targetSize = targetSize;
    this->brightness = std::max(std::min(brightness, 256), 0);
    this->contrast = std::max(std::min(contrast, 100), 0);
    this->inverse = inverse;

    if (cv::haveImageReader(pathToFile))
        Ascii::generateImgAscii();    
}

void Ascii::generateImgAscii() {
    cv::Mat image = cv::imread(pathToFile);
    Ascii::resize(image);
    Ascii::frameAsciiConvert(image);
    Ascii::write_to_terminal();
}

void Ascii::write_to_terminal() {
    for (int i = 0; i < asciiImg.size(); i++) {
        if ((i+1) % width == 0)
            std::cout << std::endl;
        std::cout << asciiImg[i] << " ";
    }
}

void Ascii::write_to_file(std::string filename) {
    std::ofstream file(filename + ".txt");

    for (int i = 0; i < asciiImg.size(); i++) {
        if ((i + 1) % width == 0)
            file << '\n';
        file << asciiImg[i] << ' ';
    }

    file.close();
}