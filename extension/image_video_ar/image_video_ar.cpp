/**
 * Yanting Lai (002955701)
 * Fall 2024
 * CS 5330 Project 4
 * image_video_ar.cpp
 */

#include "image_video_ar.h"
#include <iostream>
#include <sstream>

ImageVideoAR::ImageVideoAR(int boardWidth, int boardHeight)
    : ar(boardWidth, boardHeight),
      isPaused(false),
      currentFrame(0),
      isVideo(false) {
}

bool ImageVideoAR::processImage(const std::string& imagePath) {
    std::cout << "Loading image: " << imagePath << std::endl;
    
    cv::Mat image = cv::imread(imagePath);
    if (image.empty()) {
        std::cerr << "Error: Could not load image: " << imagePath << std::endl;
        return false;
    }

    // Rotate the image
    cv::Mat rotated;
    cv::rotate(image, rotated, cv::ROTATE_180);
    image = rotated;
    
    std::cout << "Image loaded. Size: " << image.size() << std::endl;
    
    // Create window and show controls
    cv::namedWindow("AR Image Processing", cv::WINDOW_AUTOSIZE);
    displayControls();

    // Print instructions
    std::cout << "\nInstructions:" << std::endl;
    std::cout << "1. Wait for chessboard detection (green text)" << std::endl;
    std::cout << "2. Press 's' to save calibration frame" << std::endl;
    std::cout << "3. Move/rotate image and repeat steps 1-2 at least 5 times" << std::endl;
    std::cout << "4. Press 'c' to calibrate camera" << std::endl;
    std::cout << "5. Press ESC to exit" << std::endl;
    
    while (true) {
        cv::Mat frame = image.clone();
        processFrame(frame);
        
        char key = (char)cv::waitKey(30);
        if (key == 27) { // ESC
            break;
        } else if (key == 's' || key == 'S') {
            if (ar.getCorners().size() > 0) {
                std::cout << "Saving calibration frame..." << std::endl;
                ar.saveCalibrationData();
                std::cout << "Frame saved. Total frames: " << ar.getSavedFramesCount() << std::endl;
            } else {
                std::cout << "No chessboard detected - cannot save frame" << std::endl;
            }
        } else if (key == 'c' || key == 'C') {
            if (ar.getSavedFramesCount() >= 5) {
                std::cout << "Calibrating camera..." << std::endl;
                ar.calibrateCamera();
            } else {
                std::cout << "Need at least 5 frames for calibration. Currently have: " 
                         << ar.getSavedFramesCount() << std::endl;
            }
        }
    }

    return true;
}

bool ImageVideoAR::processVideo(const std::string& videoPath) {
    if (!videoCapture.open(videoPath)) {
        std::cerr << "Error: Could not open video: " << videoPath << std::endl;
        return false;
    }

    isVideo = true;
    cv::namedWindow("AR Video Processing", cv::WINDOW_AUTOSIZE);
    
    // Show initial instructions
    std::cout << "\nVideo Processing Controls:" << std::endl;
    std::cout << "- Press 's' anytime when you see a good chessboard pattern" << std::endl;
    std::cout << "- Press SPACE to pause/resume if needed" << std::endl;
    std::cout << "- Press 'c' after saving 5 frames to calibrate" << std::endl;
    std::cout << "- Press ESC to exit" << std::endl;

    cv::Mat frame;
    const int KEY_WAIT_TIME = 1;  // Fast key response

    while (true) {
        // Get new frame if not paused
        if (!isPaused) {
            if (!videoCapture.read(frame)) {
                std::cout << "End of video reached" << std::endl;
                break;
            }
            currentFrame = videoCapture.get(cv::CAP_PROP_POS_FRAMES);
        }

        if (!frame.empty()) {
            cv::Mat processedFrame = frame.clone();
            processFrame(processedFrame);
            cv::imshow("AR Video Processing", processedFrame);
        }

        char key = (char)cv::waitKey(KEY_WAIT_TIME);
        if (key == 27) break;  // ESC

        switch (key) {
            case ' ':  // Space - Pause/Resume
                isPaused = !isPaused;
                std::cout << (isPaused ? "Video paused" : "Video resumed") << std::endl;
                break;
                
            case 's':  // Save frame
            case 'S':
                if (ar.getCorners().size() > 0) {  // If chessboard is detected
                    ar.saveCalibrationData();
                    std::cout << "Frame " << currentFrame << " saved. Total frames: " 
                             << ar.getSavedFramesCount() << std::endl;
                    if (ar.getSavedFramesCount() >= 5) {
                        std::cout << "You can now press 'c' to calibrate" << std::endl;
                    }
                } else {
                    std::cout << "No chessboard detected in current frame" << std::endl;
                }
                break;
                
            case 'c':  // Calibrate
            case 'C':
                if (ar.getSavedFramesCount() >= 5) {
                    std::cout << "Calibrating camera..." << std::endl;
                    ar.calibrateCamera();
                    if (ar.isCalibrated()) {
                        std::cout << "Calibration successful! Virtual object will now be displayed." << std::endl;
                    } else {
                        std::cout << "Calibration failed. Try collecting different views." << std::endl;
                    }
                } else {
                    std::cout << "Need " << (5 - ar.getSavedFramesCount()) 
                             << " more frames before calibration" << std::endl;
                }
                break;
        }
    }

    videoCapture.release();
    cv::destroyWindow("AR Video Processing");
    return true;
}

void ImageVideoAR::processFrame(cv::Mat& frame) {
    bool patternFound = ar.detectChessboard(frame);
    
    // Draw virtual object if calibrated
    if (patternFound && ar.isCalibrated()) {
        cv::Mat rvec, tvec;
        if (ar.computePose(rvec, tvec)) {
            ar.drawVirtualObject(frame, rvec, tvec);
        }
    }

    // Display status at the top-right corner
    int rightX = frame.cols - 400;  // X position for right-aligned text
    int startY = 30;                // Starting Y position
    int lineHeight = 30;            // Vertical spacing between lines
    
    // Detection and calibration status (top-right)
    std::string status = patternFound ? 
            (ar.isCalibrated() ? "Calibrated - Showing virtual object" : "Detected - Press 's' to save frame") : 
            "No chessboard detected";
            
    cv::putText(frame, status, cv::Point(rightX, startY), 
                cv::FONT_HERSHEY_SIMPLEX, 0.7,
                patternFound ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255), 2);

    // Frame count and calibration info (next line)
    std::string calibMsg = "Saved Frames: " + std::to_string(ar.getSavedFramesCount());
    if (ar.isCalibrated()) {
        calibMsg += " (Calibrated)";
    } else if (ar.getSavedFramesCount() >= 5) {
        calibMsg += " (Ready to calibrate - Press 'c')";
    } else {
        calibMsg += " (Need " + std::to_string(5 - ar.getSavedFramesCount()) + " more)";
    }
    cv::putText(frame, calibMsg, cv::Point(rightX, startY + lineHeight),
                cv::FONT_HERSHEY_SIMPLEX, 0.7,
                cv::Scalar(0, 255, 0), 2);

    cv::imshow(isVideo ? "AR Video Processing" : "AR Image Processing", frame);
}

void ImageVideoAR::nextFrame() {
    if (isPaused && isVideo) {
        cv::Mat frame;
        if (videoCapture.read(frame)) {
            currentFrame++;
            processFrame(frame);
        }
    }
}

void ImageVideoAR::previousFrame() {
    if (isPaused && isVideo && currentFrame > 1) {
        currentFrame--;
        videoCapture.set(cv::CAP_PROP_POS_FRAMES, currentFrame - 1);
        cv::Mat frame;
        if (videoCapture.read(frame)) {
            processFrame(frame);
        }
    }
}

void ImageVideoAR::displayControls() const {
    std::cout << "\nControls:" << std::endl;
    std::cout << "  ESC - Exit" << std::endl;
    std::cout << "  s - Save calibration frame" << std::endl;
    std::cout << "  c - Calibrate camera" << std::endl;
    if (isVideo) {
        std::cout << "  Space - Pause/Resume video" << std::endl;
        std::cout << "  Right Arrow - Next frame (when paused)" << std::endl;
        std::cout << "  Left Arrow - Previous frame (when paused)" << std::endl;
    }
}