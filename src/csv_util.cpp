/**
 * Yanting Lai (002955701)
 * Fall 2024
 * CS 5330 Project 4
 * cpp file for csv util
 */

// csv_util.cpp
#include "csv_util.h"
#include <iostream>
#include <cstdlib>

void CSVUtil::createDirectory(const std::string& path) {
    std::string dir = path.substr(0, path.find_last_of("/\\"));
    if (!dir.empty()) {
        int result = system(("mkdir -p " + dir).c_str());
        if (result != 0) {
            std::cerr << "Failed to create directory: " << dir << std::endl;
        }
    }
}

bool CSVUtil::save2DPoints(const std::string& filename,
                          const std::vector<std::vector<cv::Point2f>>& points) {
    // Debug: find filename path
    std::cout << "Attempting to save 2D points to file: " << filename << std::endl;
    createDirectory(filename);
    std::ofstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }
    
    // Write header
    file << "Frame,PointIndex,X,Y\n";
    
    // Write data with high precision
    file.precision(10);
    for (size_t frame = 0; frame < points.size(); ++frame) {
        for (size_t i = 0; i < points[frame].size(); ++i) {
            file << frame << "," 
                 << i << "," 
                 << points[frame][i].x << "," 
                 << points[frame][i].y << "\n";
        }
    }
    file.close();
    return true;
}

bool CSVUtil::save3DPoints(const std::string& filename,
                          const std::vector<std::vector<cv::Point3f>>& points) {
    createDirectory(filename);
    std::ofstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }
    
    // Write header
    file << "Frame,PointIndex,X,Y,Z\n";
    
    // Write data with high precision
    file.precision(10);
    for (size_t frame = 0; frame < points.size(); ++frame) {
        for (size_t i = 0; i < points[frame].size(); ++i) {
            file << frame << "," 
                 << i << "," 
                 << points[frame][i].x << ","
                 << points[frame][i].y << ","
                 << points[frame][i].z << "\n";
        }
    }
    file.close();
    return true;
}

bool CSVUtil::saveSummary(const std::string& filename,
                         int numFrames,
                         const cv::Size& boardSize) {
    createDirectory(filename);
    std::ofstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }
    
    file << "Parameter,Value\n";
    file << "Number of frames," << numFrames << "\n";
    file << "Board width," << boardSize.width << "\n";
    file << "Board height," << boardSize.height << "\n";
    file << "Points per frame," << boardSize.width * boardSize.height << "\n";
    file << "Total points," << numFrames * boardSize.width * boardSize.height << "\n";
    
    file.close();
    return true;
}