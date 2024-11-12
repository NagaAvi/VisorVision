#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <deque>
#include <iostream>

#ifdef _DEBUG
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK()
#endif

const int SMOOTHING_WINDOW_SIZE = 5;

// Function to sort contours by their area (descending order)
bool compareContourAreas(const std::vector<cv::Point>& c1, const std::vector<cv::Point>& c2) {
    return fabs(cv::contourArea(c1)) > fabs(cv::contourArea(c2));
}

// Function to smooth bounding box positions
cv::Rect smoothBoundingBox(const std::deque<cv::Rect>& recentBoxes) {
    int x = 0, y = 0, width = 0, height = 0;
    for (const auto& box : recentBoxes) {
        x += box.x;
        y += box.y;
        width += box.width;
        height += box.height;
    }
    int count = recentBoxes.size();
    return cv::Rect(x / count, y / count, width / count, height / count);
}

void processFrame(cv::Mat& frame, cv::Mat& objDetectFrame, cv::Mat& envDetectFrame, cv::Mat& motionFrame, cv::Mat& prevGray, double minAreaThreshold, std::deque<cv::Rect>& recentBoxes) {
    // Convert to grayscale
    cv::Mat gray;
    cv::cvtColor(objDetectFrame, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, gray, cv::Size(5, 5), 0);

    // Edge Detection for Object Detection Display
    cv::Mat edges;
    double highThresh = cv::threshold(gray, edges, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
    double lowThresh = 0.5 * highThresh;
    cv::Canny(gray, edges, lowThresh, highThresh);
    cv::imshow("Object Detection Display", edges);

    // Environment Detection
    cv::Mat morphEdges;
    cv::morphologyEx(edges, morphEdges, cv::MORPH_CLOSE, cv::Mat::ones(5, 5, CV_8U));
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(morphEdges, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    std::sort(contours.begin(), contours.end(), compareContourAreas);

    for (const auto& contour : contours) {
        if (cv::contourArea(contour) >= minAreaThreshold) {
            cv::drawContours(envDetectFrame, std::vector<std::vector<cv::Point>>{contour}, -1, cv::Scalar(0, 255, 0), 2);
        }
    }
    cv::imshow("Environment Detection Display", envDetectFrame);

    // Motion Detection
    if (!prevGray.empty()) {
        cv::Mat diff, threshDiff;
        cv::absdiff(prevGray, gray, diff);
        cv::threshold(diff, threshDiff, 25, 255, cv::THRESH_BINARY);
        cv::imshow("Motion Detection Display", threshDiff);
    }
    gray.copyTo(prevGray);

    // Light Estimation
    double avgBrightness = cv::mean(gray)[0];
    cv::Mat lightEstFrame = cv::Mat::zeros(frame.size(), CV_8UC3);
    std::string brightnessText = "Avg Brightness: " + std::to_string(avgBrightness);
    cv::putText(lightEstFrame, brightnessText, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);

    // Resize Light Estimation Display to 1/4 size
    cv::Mat smallLightEstFrame;
    cv::resize(lightEstFrame, smallLightEstFrame, cv::Size(frame.cols / 2, frame.rows / 2));
    cv::imshow("Light Estimation Display", smallLightEstFrame);
}

int main() {
    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        std::cerr << "Cannot open camera.\n";
        return -1;
    }

    cv::Mat frame, prevGray;
    std::deque<cv::Rect> recentBoxes;
    const double minAreaThreshold = 100.0;

    std::cout << "Press 'q' to exit the video stream." << std::endl;

    while (true) {
        camera >> frame;
        if (frame.empty()) {
            std::cerr << "Empty frame captured.\n";
            DEBUG_BREAK();
            break;
        }

        cv::Mat objDetectFrame = frame.clone();
        cv::Mat envDetectFrame = frame.clone();
        cv::Mat motionFrame = frame.clone();

        processFrame(frame, objDetectFrame, envDetectFrame, motionFrame, prevGray, minAreaThreshold, recentBoxes);

        cv::imshow("User Camera Output", frame);

        if (cv::waitKey(25) == 'q') {
            break;
        }
    }

    camera.release();
    cv::destroyAllWindows();
    return 0;
}
