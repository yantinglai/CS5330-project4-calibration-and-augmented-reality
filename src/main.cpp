// main.cpp
#include "augmented_reality.h"
#include <iostream>
#include <iomanip>

int main() {
    // Open the default camera
    cv::VideoCapture cap(0);
    if(!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    // Create window
    cv::namedWindow("Chessboard Detection", cv::WINDOW_AUTOSIZE);
    
    // Create detector instance (8x6 chessboard)
    AugmentedReality ar(8, 6);
    
    // Print instructions
    std::cout << "\n=== Chessboard Corner Detection ===\n";
    std::cout << "Controls:\n";
    std::cout << "  's' - Save current frame for calibration\n";
    std::cout << "  'c' - Calibrate camera (requires at least 5 frames)\n";
    std::cout << "  'ESC' - Exit and save all data\n";
    std::cout << "\nRecommendations:\n";
    std::cout << "- Capture at least 10 frames from different angles\n";
    std::cout << "- Ensure good lighting conditions\n";
    std::cout << "- Keep the chessboard still when saving\n\n";
    
    cv::Mat frame;
    while(true) {
        // Capture frame
        cap >> frame;
        if(frame.empty()) {
            std::cerr << "Error: Blank frame grabbed" << std::endl;
            break;
        }

        // Detect chessboard
        ar.detectChessboard(frame);
        
        // Show result
        cv::imshow("Chessboard Detection", frame);

        // Handle keyboard input
        char key = (char)cv::waitKey(30);
        if(key == 27) { // ESC
            break;
        } else if(key == 's' || key == 'S') {
            ar.saveCalibrationData();
        } else if (key == 'c' || key == 'C') {
            ar.calibrateCamera();
        }
    }

    // Save all data if any frames were captured
    if (ar.getSavedFramesCount() > 0) {
        std::cout << "\nSaving calibration data..." << std::endl;
        ar.saveAllData("calibration_data");
        
        std::cout << "\nCalibration session summary:" << std::endl;
        std::cout << "- Total frames saved: " << ar.getSavedFramesCount() << std::endl;
        std::cout << "- Data location: ./calibration_data/" << std::endl;
        std::cout << "  ├── corners.csv (2D corner coordinates)\n";
        std::cout << "  ├── points.csv (3D world coordinates)\n";
        std::cout << "  ├── summary.csv (Session information)\n";
        std::cout << "  └── frame_*.png (Captured images)\n";
    } else {
        std::cout << "\nNo frames were saved during this session." << std::endl;
    }

    // Cleanup
    cap.release();
    cv::destroyAllWindows();
    
    return 0;
}