/**
 * Yanting Lai (002955701)
 * Fall 2024
 * CS 5330 Project 4
 * augmented_reality.h
 */

#ifndef AUGMENTED_REALITY_H
#define AUGMENTED_REALITY_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "csv_util.h"

class AugmentedReality {
public:
    explicit AugmentedReality(int boardWidth = 9, int boardHeight = 6);
    
    /**
     * @brief Detects chessboard corners and displays results on frame
     * @param frame Input/output video frame for detection
     * @return true if chessboard detected, false otherwise
     */
    bool detectChessboard(cv::Mat& frame);
    
    /**
     * @brief Stores current successful detection for camera calibration
     */
    void saveCalibrationData();

    /**
     * @brief Saves calibration data including frames, corners, and camera parameters
     * @param directory Output directory path for saving data
     */
    void saveAllData(const std::string& directory = "/Users/sundri/Desktop/CS5330/Project4/calibration_data");
    
    /**
     * @brief Performs camera calibration from saved frames
     */
    void calibrateCamera();

    /**
     * @brief Estimates camera position and orientation
     * @param rvec Output rotation vector
     * @param tvec Output translation vector
     * @return true if pose computed successfully
     */
    bool computePose(cv::Mat& rvec, cv::Mat& tvec);

    /**
     * @brief Renders 3D coordinate axes on frame
     * @param frame Input/output frame to draw on
     * @param rvec Rotation vector for projection
     * @param tvec Translation vector for projection
     */
    void draw3DAxis(cv::Mat& frame, const cv::Mat& rvec, const cv::Mat& tvec);

    /**
     * @brief Renders virtual pyramid on detected chessboard
     * @param frame Input/output frame to draw on
     * @param rvec Rotation vector for projection
     * @param tvec Translation vector for projection
     */
    void drawVirtualObject(cv::Mat& frame, const cv::Mat& rvec, const cv::Mat& tvec);
    
    // Getters
    std::vector<cv::Point2f> getCorners() const;
    size_t getSavedFramesCount() const;
    const std::vector<std::vector<cv::Point2f>>& getCornerList() const;
    const std::vector<std::vector<cv::Point3f>>& getPointList() const;

    // Flag
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
    
    
    std::vector<cv::Point3f> createWorldPoints() const; // Generate the 3D world points corresponding to the chessboard pattern
    std::vector<cv::Point3f> virtualObjectPoints;       // 3D points of the virtual object (e.g., pyramid) defined in world coordinates
};

#endif // AUGMENTED_REALITY_H