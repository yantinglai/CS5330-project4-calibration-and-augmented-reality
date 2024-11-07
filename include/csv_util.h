/**
 * Yanting Lai (002955701)
 * Fall 2024
 * CS 5330 Project 4
 * header file for csv_util
 */

// csv_util.h
#ifndef CSV_UTIL_H_
#define CSV_UTIL_H_

#include <string>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>

class CSVUtil {
public:

    /**
     * @brief Saves detected chessboard corners to CSV file
     * @param filename Path to output CSV file
     * @param points Vector of 2D corner points from multiple frames
     * @return true if save successful
     */
    static bool save2DPoints(const std::string& filename,
                           const std::vector<std::vector<cv::Point2f>>& points);
    
    /**
     * @brief Saves 3D world points to CSV file
     * @param filename Path to output CSV file
     * @param points Vector of 3D points from multiple frames
     * @return true if save successful
     */
    static bool save3DPoints(const std::string& filename,
                           const std::vector<std::vector<cv::Point3f>>& points);
    
    /**
     * @brief Saves calibration summary data to CSV file
     * @param filename Path to output CSV file
     * @param numFrames Number of calibration frames
     * @param boardSize Size of the chessboard pattern
     * @return true if save successful
     */
    static bool saveSummary(const std::string& filename,
                           int numFrames,
                           const cv::Size& boardSize);

private:
    /**
     * @brief Creates directory if it doesn't exist
     * @param path Directory path to create
     */
    static void createDirectory(const std::string& path);
};

#endif  // CSV_UTIL_H_