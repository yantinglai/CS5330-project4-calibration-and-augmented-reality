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
    void saveAllData(const std::string& directory = "/Users/sundri/Desktop/CS5330/Project4/calibaration_data");
    
    // Getters
    std::vector<cv::Point2f> getCorners() const;
    size_t getSavedFramesCount() const;
    const std::vector<std::vector<cv::Point2f>>& getCornerList() const;
    const std::vector<std::vector<cv::Vec3f>>& getPointList() const;
    void calibrateCamera();

private:
    cv::Size patternSize;                              // Size of the chessboard
    std::vector<cv::Point2f> corners;                  // Current detected corners
    bool lastFrameSuccess;                             // Flag indicating if last frame was successful
    cv::Mat lastSuccessfulFrame;                       // Store the last successful frame
    std::vector<cv::Point2f> lastSuccessfulCorners;    // Store the last successful corners
    
    std::vector<std::vector<cv::Point2f>> corner_list; // All saved corner sets
    std::vector<std::vector<cv::Vec3f>> point_list;    // All saved 3D point sets
    std::vector<cv::Mat> calibration_frames;           // Saved frames for calibration
    
    cv::Mat camera_matrix;               // camera matrix
    cv::Mat distortion_coefficients;      // distortion coefficients
    std::vector<cv::Vec3f> createWorldPoints() const;
};

#endif // AUGMENTED_REALITY_H

