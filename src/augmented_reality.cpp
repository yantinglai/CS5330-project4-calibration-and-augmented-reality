// augmented_reality.cpp
#include "augmented_reality.h"

AugmentedReality::AugmentedReality(int boardWidth, int boardHeight)
    : patternSize(boardWidth, boardHeight), 
      lastFrameSuccess(false),
      calibrationDone(false) {

      float scaleFactor = 2.0;
          
    // Define the 3D points for a pyramid virtual object in world coordinates
    virtualObjectPoints = {
        cv::Point3f(0, 0, 0)  * scaleFactor,        // Center of the base
        cv::Point3f(-0.5, -0.5, 0)  * scaleFactor,  // Bottom-left of the base
        cv::Point3f(0.5, -0.5, 0)  * scaleFactor,   // Bottom-right of the base
        cv::Point3f(0.5, 0.5, 0)  * scaleFactor,    // Top-right of the base
        cv::Point3f(-0.5, 0.5, 0)  * scaleFactor,   // Top-left of the base
        cv::Point3f(0, 0, 1) * scaleFactor          // The apex of the pyramid
    };
}


bool AugmentedReality::detectChessboard(cv::Mat& frame) {
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    
    bool patternFound = cv::findChessboardCorners(gray, patternSize, corners,
                         cv::CALIB_CB_ADAPTIVE_THRESH +
                         cv::CALIB_CB_NORMALIZE_IMAGE +
                         cv::CALIB_CB_FAST_CHECK);
    
    if(patternFound) {
        cv::cornerSubPix(gray, corners, cv::Size(11,11), cv::Size(-1,-1),
                        cv::TermCriteria(cv::TermCriteria::EPS + 
                                       cv::TermCriteria::COUNT, 30, 0.1));
        
        cv::drawChessboardCorners(frame, patternSize, corners, patternFound);
        
        frame.copyTo(lastSuccessfulFrame);
        lastSuccessfulCorners = corners;
        lastFrameSuccess = true;

        if (calibrationDone) {
            cv::Mat rvec, tvec;
            if (computePose(rvec, tvec)) {
                std::cout << "\rRotation vector: [" << std::fixed << std::setprecision(2) 
                         << rvec.at<double>(0) << ", " 
                         << rvec.at<double>(1) << ", " 
                         << rvec.at<double>(2) << "] " 
                         << "Translation vector: [" 
                         << tvec.at<double>(0) << ", "
                         << tvec.at<double>(1) << ", "
                         << tvec.at<double>(2) << "]     " 
                         << std::flush;
                std::stringstream ss;
                ss << std::fixed << std::setprecision(2);
                
                // display rotation vector on video
                ss << "R: [" << rvec.at<double>(0) << ", " 
                        << rvec.at<double>(1) << ", " 
                        << rvec.at<double>(2) << "]";
                cv::putText(frame, ss.str(), cv::Point(10, 60), 
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, 
                        cv::Scalar(0, 255, 0), 2);
                
                // display translation vector on video
                ss.str("");
                ss << "T: [" << tvec.at<double>(0) << ", "
                            << tvec.at<double>(1) << ", "
                            << tvec.at<double>(2) << "]";
                cv::putText(frame, ss.str(), cv::Point(10, 90), 
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, 
                        cv::Scalar(0, 255, 0), 2);
            }
        }
        
        std::string msg = calibrationDone ? 
                         "Calibrated - Showing pose estimation" :
                         "Corners found. Press 's' to save. Saved: " + 
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

void AugmentedReality::calibrateCamera() {
    if (corner_list.size() < 5) {
        std::cout << "\nNot enough calibration frames. Need at least 5, current: " 
                  << corner_list.size() << std::endl;
        return;
    }

    camera_matrix = cv::Mat::eye(3, 3, CV_64F);
    distortion_coefficients = cv::Mat::zeros(8, 1, CV_64F);
    std::vector<cv::Mat> rvecs, tvecs;

    double rms = cv::calibrateCamera(point_list, corner_list, 
                                   lastSuccessfulFrame.size(),
                                   camera_matrix, distortion_coefficients, 
                                   rvecs, tvecs);

    calibrationDone = true;
    std::cout << "\nCalibration complete!\n" 
              << "RMS error: " << rms << "\n"
              << "Camera matrix:\n" << camera_matrix << "\n"
              << "Distortion coefficients:\n" << distortion_coefficients << std::endl;
}

bool AugmentedReality::computePose(cv::Mat& rvec, cv::Mat& tvec) {
    if (!calibrationDone || corners.empty()) {
        return false;
    }
    
    std::vector<cv::Point3f> objectPoints = createWorldPoints();
    return cv::solvePnP(objectPoints, corners, camera_matrix, 
                       distortion_coefficients, rvec, tvec);
}

void AugmentedReality::saveAllData(const std::string& directory) {
    system(("mkdir -p " + directory).c_str());
    
    if (!CSVUtil::save2DPoints(directory + "/corners.csv", corner_list)) {
        std::cerr << "Failed to save corner data" << std::endl;
    }
    
    if (!CSVUtil::save3DPoints(directory + "/points.csv", point_list)) {
        std::cerr << "Failed to save 3D points data" << std::endl;
    }
    
    if (!CSVUtil::saveSummary(directory + "/summary.csv", 
                             calibration_frames.size(), 
                             patternSize)) {
        std::cerr << "Failed to save summary data" << std::endl;
    }
    
    for(size_t i = 0; i < calibration_frames.size(); ++i) {
        std::string filename = directory + "/frame_" + 
                             std::to_string(i) + ".png";
        if (!cv::imwrite(filename, calibration_frames[i])) {
            std::cerr << "Failed to save frame " << i << std::endl;
        }
    }
    
    // Save camera calibration parameters if calibrated
    if (calibrationDone) {
        cv::FileStorage fs(directory + "/camera_params.yml", cv::FileStorage::WRITE);
        fs << "camera_matrix" << camera_matrix;
        fs << "dist_coeffs" << distortion_coefficients;
        fs.release();
    }
    
    std::cout << "Saved " << calibration_frames.size() << " frames to " 
              << directory << " directory" << std::endl;
}

std::vector<cv::Point3f> AugmentedReality::createWorldPoints() const {
    std::vector<cv::Point3f> points;
    for(int i = 0; i < patternSize.height; ++i) {
        for(int j = 0; j < patternSize.width; ++j) {
            points.push_back(cv::Point3f(j, -i, 0));
        }
    }
    return points;
}

void AugmentedReality::draw3DAxis(cv::Mat& frame, const cv::Mat& rvec, const cv::Mat& tvec) {
    // Define the 3D points for the axis (X, Y, Z). Each axis is 3 units in length.
    std::vector<cv::Point3f> axisPoints;
    axisPoints.push_back(cv::Point3f(0, 0, 0));  // Origin
    axisPoints.push_back(cv::Point3f(3, 0, 0));  // X-axis endpoint
    axisPoints.push_back(cv::Point3f(0, 3, 0));  // Y-axis endpoint
    axisPoints.push_back(cv::Point3f(0, 0, -3)); // Z-axis endpoint (negative for upward in image)

    // Project the 3D points to the 2D image plane
    std::vector<cv::Point2f> imagePoints;
    cv::projectPoints(axisPoints, rvec, tvec, camera_matrix, distortion_coefficients, imagePoints);

    // Draw the 3D axis on the image
    cv::line(frame, imagePoints[0], imagePoints[1], cv::Scalar(0, 0, 255), 3); // X-axis in red
    cv::line(frame, imagePoints[0], imagePoints[2], cv::Scalar(0, 255, 0), 3); // Y-axis in green
    cv::line(frame, imagePoints[0], imagePoints[3], cv::Scalar(255, 0, 0), 3); // Z-axis in blue
}

// Draws the virtual object - a pyramid on the image
void AugmentedReality::drawVirtualObject(cv::Mat& frame, const cv::Mat& rvec, const cv::Mat& tvec) {
    if (virtualObjectPoints.empty()) {
        std::cerr << "Virtual object points not initialized." << std::endl;
        return;
    }

    // Project 3D points to the 2D image plane
    std::vector<cv::Point2f> imagePoints;
    cv::projectPoints(virtualObjectPoints, rvec, tvec, camera_matrix, distortion_coefficients, imagePoints);

    // Draw the base of the pyramid
    cv::line(frame, imagePoints[0], imagePoints[1], cv::Scalar(255, 0, 0), 2); // Base edges in blue
    cv::line(frame, imagePoints[1], imagePoints[2], cv::Scalar(255, 0, 0), 2);
    cv::line(frame, imagePoints[2], imagePoints[3], cv::Scalar(255, 0, 0), 2);
    cv::line(frame, imagePoints[3], imagePoints[4], cv::Scalar(255, 0, 0), 2);
    cv::line(frame, imagePoints[4], imagePoints[0], cv::Scalar(255, 0, 0), 2);

    // Draw lines from base to the apex of the pyramid
    cv::line(frame, imagePoints[0], imagePoints[5], cv::Scalar(0, 255, 0), 2); // Lines to apex in green
    cv::line(frame, imagePoints[1], imagePoints[5], cv::Scalar(0, 255, 0), 2);
    cv::line(frame, imagePoints[2], imagePoints[5], cv::Scalar(0, 255, 0), 2);
    cv::line(frame, imagePoints[3], imagePoints[5], cv::Scalar(0, 255, 0), 2);
    cv::line(frame, imagePoints[4], imagePoints[5], cv::Scalar(0, 255, 0), 2);
}


std::vector<cv::Point2f> AugmentedReality::getCorners() const {
    return corners;
}

size_t AugmentedReality::getSavedFramesCount() const {
    return corner_list.size();
}

const std::vector<std::vector<cv::Point2f>>& AugmentedReality::getCornerList() const {
    return corner_list;
}

const std::vector<std::vector<cv::Point3f>>& AugmentedReality::getPointList() const {
    return point_list;
}