// csv_util.h
#ifndef CSV_UTIL_H_
#define CSV_UTIL_H_

#include <string>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>

class CSVUtil {
public:
    static bool save2DPoints(const std::string& filename,
                           const std::vector<std::vector<cv::Point2f>>& points);
    
    static bool save3DPoints(const std::string& filename,
                           const std::vector<std::vector<cv::Vec3f>>& points);
    
    static bool saveSummary(const std::string& filename,
                           int numFrames,
                           const cv::Size& boardSize);

private:
    static void createDirectory(const std::string& path);
};

#endif  // CSV_UTIL_H_