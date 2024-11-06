cmake_minimum_required(VERSION 3.10)
project(PROJECT4)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS}
                   ${PROJECT_SOURCE_DIR}/include)

# Augmented Reality executable
add_executable(augmented_reality src/main.cpp src/augmented_reality.cpp src/csv_util.cpp)
target_link_libraries(augmented_reality ${OpenCV_LIBS})

# Harris Corner Detection executable
add_executable(harris_corner_detection src/harris_corner_detection.cpp)
target_link_libraries(harris_corner_detection ${OpenCV_LIBS})
