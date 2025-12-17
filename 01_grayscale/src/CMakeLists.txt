# set include directories
include_directories(${OpenCV_INCLUDE_DIR})

# define source files
set(SRCS
    main.cpp
)

# define header files
set(HDRS
    Timer.h
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
