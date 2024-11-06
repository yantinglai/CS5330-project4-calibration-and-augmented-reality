# Add the extension executable
add_executable(image_video_ar
    main_image_video.cpp
    image_video_ar.cpp
)

# Link against the AR library and OpenCV
target_link_libraries(image_video_ar
    ar_lib
    ${OpenCV_LIBS}
)