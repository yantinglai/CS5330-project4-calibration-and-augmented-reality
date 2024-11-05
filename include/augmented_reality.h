// augmented_reality.h
#ifndef AUGMENTED_REALITY_H
#define AUGMENTED_REALITY_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "csv_util.h"

class AugmentedReality {
public:
    explicit AugmentedReality(int boardWidth = 8, int boardHeight = 6);
    
    bool detectChessboard(cv::Mat& frame);
    void saveCalibrationData();
    void saveAllData(const std::string& directory = "/Users/sundri/Desktop/CS5330/Project4/calibration_data");
    void calibrateCamera();
    bool computePose(cv::Mat& rvec, cv::Mat& tvec);
    
    // Getters
    std::vector<cv::Point2f> getCorners() const;
    size_t getSavedFramesCount() const;
    const std::vector<std::vector<cv::Point2f>>& getCornerList() const;
    const std::vector<std::vector<cv::Point3f>>& getPointList() const;
    bool isCalibrated() const { return calibrationDone; }

private:
    cv::Size patternSize;                              // Size of the chessboard
    std::vector<cv::Point2f> corners;                  // Current detected corners
    bool lastFrameSuccess;                             // Flag indicating if last frame was successful
    cv::Mat lastSuccessfulFrame;                       // Store the last successful frame
    std::vector<cv::Point2f> lastSuccessfulCorners;    // Store the last successful corners
    
    std::vector<std::vector<cv::Point2f>> corner_list; // All saved corner sets
    std::vector<std::vector<cv::Point3f>> point_list;    // Changed to Point3f
    std::vector<cv::Mat> calibration_frames;           // Saved frames for calibration
    
    cv::Mat camera_matrix;                             // Camera matrix
    cv::Mat distortion_coefficients;                   // Distortion coefficients
    bool calibrationDone;                              // Flag to track calibration status
    
    std::vector<cv::Point3f> createWorldPoints() const;
};

#endif // AUGMENTED_REALITY_H