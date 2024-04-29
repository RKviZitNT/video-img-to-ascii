#include "imgasciic.h"

Image::Image(const std::string& imagePath) {
    image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
}

void Image::resize(int targetSize) {
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

void Image::imgAsciiInit(std::string gradientStr, bool inverse) {
    int index;

    gradient.assign(gradientStr.begin(), gradientStr.end());
    double asciiBrightness = 256.0f / (gradient.size() - 2);

    for (int j = 0; j < image.rows; ++j) {
        for (int i = 0; i < image.cols; ++i) {
            uchar brightness = image.at<uchar>(j, i);
            if (inverse)
                index = gradient.size() - 2 - std::round(brightness / asciiBrightness);
            else
                index = std::round(brightness / asciiBrightness);
            asciiImg.push_back(gradient[index]);
        }
    }
}

void Image::generateAsciiImg(int targetSize, std::string gradientStr, bool inverse) {
    Image::resize(targetSize);
    Image::imgAsciiInit(gradientStr, inverse);
}

void Image::write_to_terminal() {
    for (int i = 0; i < asciiImg.size(); i++) {
        if ((i+1) % width == 0)
            std::cout << std::endl;
        std::cout << asciiImg[i] << " ";
    }
}

void Image::write_to_file(std::string filename) {
    std::ofstream file(filename += ".txt");

    for (int i = 0; i < asciiImg.size(); i++) {
        if ((i + 1) % width == 0)
            file << '\n';
        file << asciiImg[i] << ' ';
    }

    file.close();
}