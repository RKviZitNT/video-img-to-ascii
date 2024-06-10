#include "asciic.h"

Ascii::Ascii(std::string pathToFile) : pathToFile(pathToFile) {}

void Ascii::resize(cv::Mat& frame) {
    scale = (double)targetSize / frame.cols;
    width = targetSize;
    height = frame.rows * scale;

    cv::resize(frame, frame, cv::Size(width, height));
}

void Ascii::AsciiInit(cv::Mat& frame) {
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

            asciiFrame.push_back(gradient[index]);
        }
    }
}

void Ascii::generateAscii(std::string gradientStr, int targetSize, int brightness, int contrast, bool inverse) {
    this->gradientStr = gradientStr;
    this->targetSize = targetSize;
    this->brightness = std::max(std::min(brightness, 256), 0);
    this->contrast = std::max(std::min(contrast, 100), 0);
    this->inverse = inverse;

    if (!cv::haveImageReader(pathToFile)) {
        Ascii::generateAsciiVideo();
        return;
    }
    
    Ascii::generateAsciiImage();
}

void Ascii::generateAsciiImage() {
    cv::Mat image = cv::imread(pathToFile);
    if (image.empty()) {
        std::cout << "Could not open or find the image" << std::endl;
        return;
    }

    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);

    Ascii::resize(image);
    Ascii::AsciiInit(image);
    Ascii::write_to_terminal();
}

void Ascii::generateAsciiVideo() {
    cv::VideoCapture cap(pathToFile);
    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open video file" << std::endl;
        return;
    }

    double fps = cap.get(cv::CAP_PROP_FPS);
    double frameTime = 1000.0f / fps;

    cv::Mat frame;
    while (true) {
        cap >> frame;
        std::cout << "\033";

        if (frame.empty()) {
            break;
        }

        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

        Ascii::resize(frame);
        Ascii::AsciiInit(frame);

        Ascii::write_to_terminal();
        asciiFrame.clear();

        cv::waitKey(frameTime / 2);
    }

    cap.release();
}

void Ascii::write_to_terminal() {
    std::string asciiOutputFrame = "";
    for (int i = 0; i < asciiFrame.size(); i++) {
        if ((i) % width == 0)
            asciiOutputFrame += "\n";
        asciiOutputFrame += asciiFrame[i];
        asciiOutputFrame += " ";
    }
    std::cout << asciiOutputFrame;
}