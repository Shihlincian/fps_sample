cmake_minimum_required(VERSION "3.7.1")
project(fps_example VERSION 1.0)

set(FPS_EXAMPLE "fps_example")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/fps_example.cpp")

# build as library
ADD_EXECUTABLE( ${FPS_EXAMPLE}
    "${SOURCES}"
    "${HEADERS}"
)

# set variable for opencv
set(OpenCV_DIR "${OPENCV_INSTALL_PATH}/x64/vc15/lib")
# find openCV package
find_package(OpenCV REQUIRED)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
set_target_properties(${FPS_EXAMPLE}
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>
)
message(${OpenCV_INCLUDE_DIRS})
# link header
target_include_directories(${FPS_EXAMPLE} PUBLIC
        ${OpenCV_INCLUDE_DIRS}
    )

# link k4a lib
target_link_libraries(${FPS_EXAMPLE} 
        ${OpenCV_LIBS}
    )
