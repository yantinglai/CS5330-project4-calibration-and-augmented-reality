#ifndef IMAGE_VIDEO_AR_H
#define IMAGE_VIDEO_AR_H

#include "../../include/augmented_reality.h"
#include <opencv2/opencv.hpp>
#include <string>

class ImageVideoAR {
public:
    // Constructor with default chessboard dimensions (8x6 inner corners)
    ImageVideoAR(int boardWidth = 8, int boardHeight = 6);
    
    // Main processing functions
    bool processImage(const std::string& imagePath);  // Process a single image
    bool processVideo(const std::string& videoPath);  // Process a video file
    
    // Video control functions
    void togglePause() { isPaused = !isPaused; }
    void nextFrame();     // Move to next frame
    void previousFrame(); // Move to previous frame
    
private:
    AugmentedReality ar;           // Instance of the original AR system
    cv::VideoCapture videoCapture; // Video capture object
    bool isPaused;                 // Flag for video pause state
    int currentFrame;              // Current frame counter
    bool isVideo;                  // Flag to indicate video mode
    
    // Helper functions
    void processFrame(cv::Mat& frame);
    void displayControls() const;
    bool handleKeyboard();
};

#endif // IMAGE_VIDEO_AR_H