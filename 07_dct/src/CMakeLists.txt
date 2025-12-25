cmake_minimum_required(VERSION 3.5)

# set project name
project(dct)

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
set(InputImage_DIR ../data/lena.tiff CACHE FILEPATH "Input image file")
add_definitions(-DINPUTIMAGE=\"${InputImage_DIR}\")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_EXTENSIONS False)
set(CMAKE_BUILD_TYPE "Release")

# find libraries
find_package(OpenCV REQUIRED)
set(OPENCV_COMPONENTS
    opencv_core
    opencv_imgproc
    opencv_highgui
)

# set include directories
include_directories(${OpenCV_INCLUDE_DIR})

# define source files
set(SRCS
    main.cpp
    Dct.cpp
)

# define header files
set(HDRS
    Dct.h
)

# make executable
add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

# link against libraries
target_link_libraries(${PROJECT_NAME} ${OPENCV_COMPONENTS})

# copy dlls for windows
if(WIN32)
    if(OPENCV_COMPONENTS)
        foreach(OPENCV_COMPONENT ${OPENCV_COMPONENTS})
            list(APPEND COPY_FILES
            $<TARGET_FILE:${OPENCV_COMPONENT}>)
        endforeach()
    endif()
    foreach(COPY_FILE ${COPY_FILES})
        message(STATUS ${PROJECT_NAME})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${COPY_FILE} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endforeach()
endif()
