cmake_minimum_required(VERSION 3.5)

# set project name
project(grayscale)

# reject msvc10 caused by not supporting cpp11
if(MSVC10)
    message(FATAL_ERROR "Please use an newer Visual Studio than 2010! It does not support C++11 which is required for this lab.")
endif()

if(MSVC)
    set(OpenCV_DIR "${CMAKE_CURRENT_LIST_DIR}/../opencv/build/")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    # Replace path with linux path IMPORTANT NEED TO BE DONE BEFORE LAB
    set(OpenCV_DIR "${CMAKE_CURRENT_LIST_DIR}/../opencv_2.4.10/share/OpenCV")
endif()

# input image selection
set(InputImage_DIR ../lena.tiff CACHE FILEPATH "Input image file")
add_definitions(-DINPUTIMAGE=\"${InputImage_DIR}\")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_EXTENSIONS False)
set(CMAKE_BUILD_TYPE "Release")

# find libraries
find_package(OpenCV REQUIRED)
set(OPENCV_COMPONENTS
    opencv_core
    opencv_imgcodecs
    opencv_imgproc
    opencv_highgui
)

add_subdirectory(src)