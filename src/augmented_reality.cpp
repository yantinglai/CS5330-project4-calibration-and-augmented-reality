#include "augmented_reality.h"

AugmentedReality::AugmentedReality(int boardWidth, int boardHeight)
    : patternSize(boardWidth, boardHeight), lastFrameSuccess(false) {
}

bool AugmentedReality::detectChessboard(cv::Mat& frame) {
    // Convert frame to grayscale
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    
    // Find chessboard corners
    bool patternFound = cv::findChessboardCorners(gray, patternSize, corners,
                         cv::CALIB_CB_ADAPTIVE_THRESH +
                         cv::CALIB_CB_NORMALIZE_IMAGE +
                         cv::CALIB_CB_FAST_CHECK);
    
    if(patternFound) {
        // Refine corner positions
        cv::cornerSubPix(gray, corners, cv::Size(11,11), cv::Size(-1,-1),
                        cv::TermCriteria(cv::TermCriteria::EPS + 
                                       cv::TermCriteria::COUNT, 30, 0.1));
        
        // Draw the corners
        cv::drawChessboardCorners(frame, patternSize, corners, patternFound);
        
        // Store successful frame and corners
        frame.copyTo(lastSuccessfulFrame);
        lastSuccessfulCorners = corners;
        lastFrameSuccess = true;
        
        // Display information
        std::string msg = "Corners found. Press 's' to save. Saved: " + 
                         std::to_string(getSavedFramesCount());
        cv::putText(frame, msg, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 
                    0.8, cv::Scalar(0, 255, 0), 2);
    } else {
        lastFrameSuccess = false;
        cv::putText(frame, "No chessboard detected", cv::Point(10, 30),
                    cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 0, 255), 2);
        
        if (!lastSuccessfulFrame.empty()) {
            cv::putText(frame, "Last successful frame available", cv::Point(10, 60),
                    cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);
        }
    }
    
    return patternFound;
}

void AugmentedReality::saveCalibrationData() {
    if (lastSuccessfulFrame.empty() || lastSuccessfulCorners.empty()) {
        std::cout << "\nNo valid frame available to save" << std::endl;
        return;
    }
    
    corner_list.push_back(lastSuccessfulCorners);
    point_list.push_back(createWorldPoints());
    calibration_frames.push_back(lastSuccessfulFrame.clone());
    
    std::cout << "\nSaved frame " << calibration_frames.size() 
              << " (using " << (lastFrameSuccess ? "current" : "last successful")
              << " detection)" << std::endl;
}

std::vector<cv::Vec3f> AugmentedReality::createWorldPoints() const {
    std::vector<cv::Vec3f> points;
    for(int i = 0; i < patternSize.height; ++i) {
        for(int j = 0; j < patternSize.width; ++j) {
            points.push_back(cv::Vec3f(j, -i, 0));
        }
    }
    return points;
}

void AugmentedReality::saveAllData(const std::string& directory) {
    system(("mkdir -p " + directory).c_str());
    
    // Save corner points
    if (!CSVUtil::save2DPoints(directory + "/corners.csv", corner_list)) {
        std::cerr << "Failed to save corner data" << std::endl;
    }
    
    // Save 3D world points
    if (!CSVUtil::save3DPoints(directory + "/points.csv", point_list)) {
        std::cerr << "Failed to save 3D points data" << std::endl;
    }
    
    // Save summary
    if (!CSVUtil::saveSummary(directory + "/summary.csv", 
                             calibration_frames.size(), 
                             patternSize)) {
        std::cerr << "Failed to save summary data" << std::endl;
    }
    
    // Save images
    for(size_t i = 0; i < calibration_frames.size(); ++i) {
        std::string filename = directory + "/frame_" + 
                             std::to_string(i) + ".png";
        if (!cv::imwrite(filename, calibration_frames[i])) {
            std::cerr << "Failed to save frame " << i << std::endl;
        }
    }
    
    std::cout << "Saved " << calibration_frames.size() << " frames to " 
              << directory << " directory" << std::endl;
}

void AugmentedReality::calibrateCamera() {
    if (corner_list.size() < 5) {
        std::cerr << "Not enough calibration frames. Capture at least 5 frames." << std::endl;
        return;
    }

    cv::Mat camera_matrix = (cv::Mat_<double>(3, 3) << 1, 0, lastSuccessfulFrame.cols / 2.0,
                                                       0, 1, lastSuccessfulFrame.rows / 2.0,
                                                       0, 0, 1);
    
    cv::Mat distortion_coefficients = cv::Mat::zeros(8, 1, CV_64F);
    std::vector<cv::Mat> rotations, translations; 
    
    double reprojection_error = cv::calibrateCamera(point_list, corner_list, 
                                                    lastSuccessfulFrame.size(),
                                                    camera_matrix, distortion_coefficients, 
                                                    rotations, translations,
                                                    cv::CALIB_FIX_ASPECT_RATIO);
    
    std::cout << "Calibration complete. Reprojection error: " << reprojection_error << std::endl;
    std::cout << "Camera matrix:\n" << camera_matrix << std::endl;
    std::cout << "Distortion coefficients:\n" << distortion_coefficients.t() << std::endl;

    this->camera_matrix = camera_matrix.clone();
    this->distortion_coefficients = distortion_coefficients.clone();
}

// Getter implementations
std::vector<cv::Point2f> AugmentedReality::getCorners() const {
    return corners;
}

size_t AugmentedReality::getSavedFramesCount() const {
    return corner_list.size();
}

const std::vector<std::vector<cv::Point2f>>& AugmentedReality::getCornerList() const {
    return corner_list;
}

const std::vector<std::vector<cv::Vec3f>>& AugmentedReality::getPointList() const {
    return point_list;
}