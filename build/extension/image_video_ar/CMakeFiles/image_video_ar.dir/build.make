# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sundri/Desktop/CS5330/Project4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sundri/Desktop/CS5330/Project4/build

# Include any dependencies generated for this target.
include extension/image_video_ar/CMakeFiles/image_video_ar.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include extension/image_video_ar/CMakeFiles/image_video_ar.dir/compiler_depend.make

# Include the progress variables for this target.
include extension/image_video_ar/CMakeFiles/image_video_ar.dir/progress.make

# Include the compile flags for this target's objects.
include extension/image_video_ar/CMakeFiles/image_video_ar.dir/flags.make

extension/image_video_ar/CMakeFiles/image_video_ar.dir/main_image_video.cpp.o: extension/image_video_ar/CMakeFiles/image_video_ar.dir/flags.make
extension/image_video_ar/CMakeFiles/image_video_ar.dir/main_image_video.cpp.o: /Users/sundri/Desktop/CS5330/Project4/extension/image_video_ar/main_image_video.cpp
extension/image_video_ar/CMakeFiles/image_video_ar.dir/main_image_video.cpp.o: extension/image_video_ar/CMakeFiles/image_video_ar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sundri/Desktop/CS5330/Project4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object extension/image_video_ar/CMakeFiles/image_video_ar.dir/main_image_video.cpp.o"
	cd /Users/sundri/Desktop/CS5330/Project4/build/extension/image_video_ar && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT extension/image_video_ar/CMakeFiles/image_video_ar.dir/main_image_video.cpp.o -MF CMakeFiles/image_video_ar.dir/main_image_video.cpp.o.d -o CMakeFiles/image_video_ar.dir/main_image_video.cpp.o -c /Users/sundri/Desktop/CS5330/Project4/extension/image_video_ar/main_image_video.cpp

extension/image_video_ar/CMakeFiles/image_video_ar.dir/main_image_video.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/image_video_ar.dir/main_image_video.cpp.i"
	cd /Users/sundri/Desktop/CS5330/Project4/build/extension/image_video_ar && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sundri/Desktop/CS5330/Project4/extension/image_video_ar/main_image_video.cpp > CMakeFiles/image_video_ar.dir/main_image_video.cpp.i

extension/image_video_ar/CMakeFiles/image_video_ar.dir/main_image_video.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/image_video_ar.dir/main_image_video.cpp.s"
	cd /Users/sundri/Desktop/CS5330/Project4/build/extension/image_video_ar && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sundri/Desktop/CS5330/Project4/extension/image_video_ar/main_image_video.cpp -o CMakeFiles/image_video_ar.dir/main_image_video.cpp.s

extension/image_video_ar/CMakeFiles/image_video_ar.dir/image_video_ar.cpp.o: extension/image_video_ar/CMakeFiles/image_video_ar.dir/flags.make
extension/image_video_ar/CMakeFiles/image_video_ar.dir/image_video_ar.cpp.o: /Users/sundri/Desktop/CS5330/Project4/extension/image_video_ar/image_video_ar.cpp
extension/image_video_ar/CMakeFiles/image_video_ar.dir/image_video_ar.cpp.o: extension/image_video_ar/CMakeFiles/image_video_ar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sundri/Desktop/CS5330/Project4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object extension/image_video_ar/CMakeFiles/image_video_ar.dir/image_video_ar.cpp.o"
	cd /Users/sundri/Desktop/CS5330/Project4/build/extension/image_video_ar && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT extension/image_video_ar/CMakeFiles/image_video_ar.dir/image_video_ar.cpp.o -MF CMakeFiles/image_video_ar.dir/image_video_ar.cpp.o.d -o CMakeFiles/image_video_ar.dir/image_video_ar.cpp.o -c /Users/sundri/Desktop/CS5330/Project4/extension/image_video_ar/image_video_ar.cpp

extension/image_video_ar/CMakeFiles/image_video_ar.dir/image_video_ar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/image_video_ar.dir/image_video_ar.cpp.i"
	cd /Users/sundri/Desktop/CS5330/Project4/build/extension/image_video_ar && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sundri/Desktop/CS5330/Project4/extension/image_video_ar/image_video_ar.cpp > CMakeFiles/image_video_ar.dir/image_video_ar.cpp.i

extension/image_video_ar/CMakeFiles/image_video_ar.dir/image_video_ar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/image_video_ar.dir/image_video_ar.cpp.s"
	cd /Users/sundri/Desktop/CS5330/Project4/build/extension/image_video_ar && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sundri/Desktop/CS5330/Project4/extension/image_video_ar/image_video_ar.cpp -o CMakeFiles/image_video_ar.dir/image_video_ar.cpp.s

# Object files for target image_video_ar
image_video_ar_OBJECTS = \
"CMakeFiles/image_video_ar.dir/main_image_video.cpp.o" \
"CMakeFiles/image_video_ar.dir/image_video_ar.cpp.o"

# External object files for target image_video_ar
image_video_ar_EXTERNAL_OBJECTS =

extension/image_video_ar/image_video_ar: extension/image_video_ar/CMakeFiles/image_video_ar.dir/main_image_video.cpp.o
extension/image_video_ar/image_video_ar: extension/image_video_ar/CMakeFiles/image_video_ar.dir/image_video_ar.cpp.o
extension/image_video_ar/image_video_ar: extension/image_video_ar/CMakeFiles/image_video_ar.dir/build.make
extension/image_video_ar/image_video_ar: libar_lib.a
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_gapi.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_stitching.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_alphamat.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_aruco.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_bgsegm.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_bioinspired.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_ccalib.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_dnn_objdetect.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_dnn_superres.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_dpm.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_face.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_freetype.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_fuzzy.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_hfs.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_img_hash.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_intensity_transform.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_line_descriptor.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_mcc.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_quality.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_rapid.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_reg.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_rgbd.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_saliency.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_sfm.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_signal.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_stereo.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_structured_light.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_superres.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_surface_matching.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_tracking.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_videostab.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_viz.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_wechat_qrcode.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_xfeatures2d.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_xobjdetect.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_xphoto.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_phase_unwrapping.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_optflow.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_highgui.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_datasets.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_plot.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_text.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_videoio.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_ml.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_shape.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_ximgproc.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_video.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_imgcodecs.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_objdetect.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_calib3d.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_dnn.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_features2d.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_flann.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_photo.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_imgproc.4.10.0.dylib
extension/image_video_ar/image_video_ar: /opt/homebrew/lib/libopencv_core.4.10.0.dylib
extension/image_video_ar/image_video_ar: extension/image_video_ar/CMakeFiles/image_video_ar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/sundri/Desktop/CS5330/Project4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable image_video_ar"
	cd /Users/sundri/Desktop/CS5330/Project4/build/extension/image_video_ar && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/image_video_ar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extension/image_video_ar/CMakeFiles/image_video_ar.dir/build: extension/image_video_ar/image_video_ar
.PHONY : extension/image_video_ar/CMakeFiles/image_video_ar.dir/build

extension/image_video_ar/CMakeFiles/image_video_ar.dir/clean:
	cd /Users/sundri/Desktop/CS5330/Project4/build/extension/image_video_ar && $(CMAKE_COMMAND) -P CMakeFiles/image_video_ar.dir/cmake_clean.cmake
.PHONY : extension/image_video_ar/CMakeFiles/image_video_ar.dir/clean

extension/image_video_ar/CMakeFiles/image_video_ar.dir/depend:
	cd /Users/sundri/Desktop/CS5330/Project4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sundri/Desktop/CS5330/Project4 /Users/sundri/Desktop/CS5330/Project4/extension/image_video_ar /Users/sundri/Desktop/CS5330/Project4/build /Users/sundri/Desktop/CS5330/Project4/build/extension/image_video_ar /Users/sundri/Desktop/CS5330/Project4/build/extension/image_video_ar/CMakeFiles/image_video_ar.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : extension/image_video_ar/CMakeFiles/image_video_ar.dir/depend

