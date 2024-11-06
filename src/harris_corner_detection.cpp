#include <opencv2/opencv.hpp>
#include <iostream>
#include <numeric>

int thresh = 150;
int blockSize = 2;  // 添加滑动条参数
int kSize = 3;      // Sobel算子大小

void onTrackbarChange(int, void*) {}

int main() {
    cv::VideoCapture cap(1);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    // Set camera properties
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 30);

    // Create windows and trackbars for parameter tuning
    cv::namedWindow("Harris Corner Detection", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Threshold", "Harris Corner Detection", &thresh, 255, onTrackbarChange);
    cv::createTrackbar("Block Size", "Harris Corner Detection", &blockSize, 10, onTrackbarChange);
    cv::createTrackbar("Kernel Size", "Harris Corner Detection", &kSize, 7, onTrackbarChange);

    cv::Mat frame, gray, dst, dst_norm;
    std::vector<cv::Point2f> corners;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Ensure block size is odd
        int actualBlockSize = 2 * blockSize + 1;
        // Ensure kernel size is odd
        int actualKSize = 2 * kSize + 1;
        
        // Harris parameters
        double k = 0.04;
        
        // Pre-allocate matrices
        if (dst.empty()) {
            dst = cv::Mat::zeros(gray.size(), CV_32FC1);
            dst_norm = cv::Mat::zeros(gray.size(), CV_32FC1);
        }

        // Apply Harris corner detection with dynamic parameters
        cv::cornerHarris(gray, dst, actualBlockSize, actualKSize, k);
        
        // Normalize for visualization
        cv::normalize(dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1);

        corners.clear();
        float threshold = static_cast<float>(thresh);

        // More accurate corner detection
        for(int i = actualBlockSize; i < dst_norm.rows - actualBlockSize; i++) {
            const float* row = dst_norm.ptr<float>(i);
            for(int j = actualBlockSize; j < dst_norm.cols - actualBlockSize; j++) {
                if(row[j] > threshold) {
                    // Check if it's a local maximum in 3x3 neighborhood
                    bool isMax = true;
                    for(int dy = -1; dy <= 1 && isMax; dy++) {
                        for(int dx = -1; dx <= 1 && isMax; dx++) {
                            if(dx == 0 && dy == 0) continue;
                            if(dst_norm.at<float>(i+dy, j+dx) >= row[j]) {
                                isMax = false;
                            }
                        }
                    }
                    if(isMax) {
                        // Use sub-pixel accuracy
                        cv::Point2f cornerPoint(j, i);
                        corners.push_back(cornerPoint);
                    }
                }
            }
        }

        // Refine corner locations using sub-pixel accuracy
        if(!corners.empty()) {
            cv::Size winSize = cv::Size(5, 5);
            cv::Size zeroZone = cv::Size(-1, -1);
            cv::TermCriteria criteria = cv::TermCriteria(
                cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 40, 0.001);
            cv::cornerSubPix(gray, corners, winSize, zeroZone, criteria);
        }

        // Draw detected corners
        cv::Mat display = frame.clone();
        for (const auto& corner : corners) {
            // Draw cross marker
            cv::line(display, 
                    cv::Point(corner.x - 5, corner.y),
                    cv::Point(corner.x + 5, corner.y),
                    cv::Scalar(0, 0, 255), 2);
            cv::line(display, 
                    cv::Point(corner.x, corner.y - 5),
                    cv::Point(corner.x, corner.y + 5),
                    cv::Scalar(0, 0, 255), 2);
        }

        // Calculate and display FPS
        static float fps = 0;
        static int64 prev_tick = cv::getTickCount();
        int64 curr_tick = cv::getTickCount();
        float curr_fps = cv::getTickFrequency() / (curr_tick - prev_tick);
        fps = 0.9f * fps + 0.1f * curr_fps;
        prev_tick = curr_tick;
        
        // Display information
        cv::putText(display, 
                    "FPS: " + std::to_string(static_cast<int>(fps)) +
                    " Corners: " + std::to_string(corners.size()) +
                    " Block: " + std::to_string(actualBlockSize) +
                    " Kernel: " + std::to_string(actualKSize),
                    cv::Point(10, 30),
                    cv::FONT_HERSHEY_SIMPLEX, 0.7,
                    cv::Scalar(0, 255, 0), 2);

        cv::imshow("Harris Corner Detection", display);

        char key = (char)cv::waitKey(1);
        if (key == 27) break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}