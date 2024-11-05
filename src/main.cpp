// main.cpp
#include "augmented_reality.h"
#include <iostream>
#include <iomanip>

int main() {
    cv::VideoCapture cap(1);
    if(!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    cv::namedWindow("Chessboard Detection", cv::WINDOW_AUTOSIZE);
    
    AugmentedReality ar(8, 6);
    
    std::cout << "\n=== Chessboard Detection and Pose Estimation ===\n";
    std::cout << "Step 1: Gather calibration images\n";
    std::cout << "Step 2: Calibrate the camera\n";
    std::cout << "Step 3: View real-time pose estimation\n\n";
    std::cout << "Controls:\n";
    std::cout << "  's' - Save current frame for calibration\n";
    std::cout << "  'c' - Calibrate camera (requires at least 5 frames)\n";
    std::cout << "  'ESC' - Exit and save all data\n\n";
    std::cout << "Instructions:\n";
    std::cout << "1. Move the chessboard to different positions\n";
    std::cout << "2. Press 's' when corners are detected (shown in green)\n";
    std::cout << "3. Collect at least 5 frames from different angles\n";
    std::cout << "4. Press 'c' to calibrate\n";
    std::cout << "5. After calibration, pose will show automatically\n\n";
    
    cv::Mat frame;
    while(true) {
        cap >> frame;
        if(frame.empty()) {
            std::cerr << "Error: Blank frame grabbed" << std::endl;
            break;
        }

        bool patternFound = ar.detectChessboard(frame);

        if (patternFound && ar.isCalibrated() && ar.getCorners().size() >= 4) {
            cv::Mat rvec, tvec;
            if (ar.computePose(rvec, tvec)) {
                ar.draw3DAxis(frame, rvec, tvec); // Draw 3D axis if pose is computed
            }
        }

        cv::imshow("Chessboard Detection", frame);

        char key = (char)cv::waitKey(30);
        if(key == 27) { // ESC
            break;
        } else if(key == 's' || key == 'S') {
            ar.saveCalibrationData();
        } else if (key == 'c' || key == 'C') {
            ar.calibrateCamera();
        }
    }

    if (ar.getSavedFramesCount() > 0) {
        std::cout << "\nSaving calibration data..." << std::endl;
        ar.saveAllData("calibration_data");
        
        std::cout << "\nCalibration session summary:" << std::endl;
        std::cout << "- Total frames saved: " << ar.getSavedFramesCount() << std::endl;
        std::cout << "- Data location: ./calibration_data/" << std::endl;
        std::cout << "  ├── corners.csv (2D corner coordinates)\n";
        std::cout << "  ├── points.csv (3D world coordinates)\n";
        std::cout << "  ├── summary.csv (Session information)\n";
        if (ar.isCalibrated()) {
            std::cout << "  ├── camera_params.yml (Camera parameters)\n";
        }
        std::cout << "  └── frame_*.png (Captured images)\n";
    } else {
        std::cout << "\nNo frames were saved during this session." << std::endl;
    }

    cap.release();
    cv::destroyAllWindows();
    
    return 0;
}