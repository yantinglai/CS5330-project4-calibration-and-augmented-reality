# Augmented Reality Program
## CS5330 Project 4 - Fall 2024

### Author Information
- **Name:** Yanting Lai
- **NUID:** 002955701

### Video Demonstration Links
- Video demo for pyramid:
https://drive.google.com/file/d/14xmNXshD4a7BVUosNGi_4qW2CmNQ-dSB/view?usp=sharing

- Video demo for harris corner:
https://drive.google.com/file/d/1EbaAiFpkKOE6GMyr8f4yY9y2jA74h4HI/view?usp=sharing

### Development Environment
- **Operating System:** macOS
- **IDE:** Visual Studio Code
- **Required Libraries:** OpenCV 4.x

### Main Project Instructions

1. **Build Project**
   ```bash
   cd /Users/sundri/Desktop/CS5330/Project4
   mkdir build
   cd build
   cmake ..
   make
   ```

2. **Run Main AR Program**
   ```bash
   ./augmented_reality
   ./harris_corner_detection
   ```

3. **Key Controls**
   - 's': Save current frame for calibration
   - 'c': Perform camera calibration
   - 'p': Toggle pyramid display
   - 'Esc': Exit program and see the print result

### Extension: Image/Video Input Selection

1. **Build Extension**
   ```bash
   cd /Users/sundri/Desktop/CS5330/Project4/extension/image_video_ar
   mkdir build
   cd build
   cmake ..
   make
   ```

2. **Run Extension Program**
   ```bash
   ./extension/image_video_ar/image_video_ar
   ```

3. **Extension Features**
   - User can choose between image or video input
   - Input options:
     - Enter '1': Process image file
     - Enter '2': Process video file
   - Same AR functionality as main program
   - Supports various image and video formats

### Time Travel Days
- Got approval from professor using clause "stuff happens"

---
© 2024 Yanting Lai - Northeastern University
