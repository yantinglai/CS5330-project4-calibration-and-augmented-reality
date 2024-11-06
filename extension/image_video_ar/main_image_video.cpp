#include "image_video_ar.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "=== AR System with Image/Video Support ===" << std::endl;
    
    // Create AR object with 9x6 chessboard (inner corners)
    ImageVideoAR imageVideoAR(9, 6);
    
    // Display menu options
    std::cout << "\nChoose input type:" << std::endl;
    std::cout << "1. Process image file" << std::endl;
    std::cout << "2. Process video file" << std::endl;
    std::cout << "\nEnter your choice (1-2): ";
    
    int choice;
    std::cin >> choice;
    std::cin.ignore();  // Clear input buffer

    std::string filePath;
    std::cout << "Enter file path: ";
    std::getline(std::cin, filePath);

    bool success = false;
    switch (choice) {
        case 1:
            success = imageVideoAR.processImage(filePath);
            break;
        case 2:
            success = imageVideoAR.processVideo(filePath);
            break;
        default:
            std::cout << "Invalid choice" << std::endl;
            return -1;
    }

    if (!success) {
        std::cout << "Failed to process file" << std::endl;
        return -1;
    }

    cv::destroyAllWindows();
    return 0;
}