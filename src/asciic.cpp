#include "asciic.h"

Image::Image(const std::string& imagePath) {
    this->image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
}

void Image::resize() {
    if (image.cols > image.rows) {
        scale = (double)targetSize / image.cols;
        width = targetSize;
        height = image.rows * scale;
    } else {
        scale = (double)targetSize / image.rows;
        width = image.cols * scale;
        height = targetSize;
    }

    cv::resize(image, image, cv::Size(width, height));
}

void Image::imgAsciiInit() {
    gradient.assign(gradientStr.begin(), gradientStr.end());

    int index, contrastGradient = std::round((gradient.size() - 1) / 100.0f * static_cast<float>(100 - contrast));
    double averageBrightness = 256 - brightness;

    double darkBrightness = averageBrightness / contrastGradient;
    double lightBrightness = (256.0f - averageBrightness) / (gradient.size() - 1 - contrastGradient);

    for (int j = 0; j < image.rows; ++j) {
        for (int i = 0; i < image.cols; ++i) {
            uchar brightnessPixel = image.at<uchar>(j, i);
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

void Image::generateAsciiImg(std::string gradientStr, int targetSize, int brightness, int contrast, bool inverse) {
    this->gradientStr = gradientStr;
    this->targetSize = targetSize;
    this->brightness = std::max(std::min(brightness, 256), 0);
    this->contrast = std::max(std::min(contrast, 100), 0);
    this->inverse = inverse;

    Image::resize();
    Image::imgAsciiInit();
}

void Image::write_to_terminal() {
    for (int i = 0; i < asciiImg.size(); i++) {
        if ((i+1) % width == 0)
            std::cout << std::endl;
        std::cout << asciiImg[i] << " ";
    }
}

void Image::write_to_file(std::string filename) {
    std::ofstream file(filename + ".txt");

    for (int i = 0; i < asciiImg.size(); i++) {
        if ((i + 1) % width == 0)
            file << '\n';
        file << asciiImg[i] << ' ';
    }

    file.close();
}