cmake_minimum_required(VERSION 3.7)
project(CameraChecker)

SET(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV 2.4.3 REQUIRED)
find_package(Qt5Gui)
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Test)
find_package(Qt5Concurrent)
find_package(Qt5OpenGL)



set(SOURCE_FILES main.cpp)
add_executable(CameraChecker ${SOURCE_FILES})

target_link_libraries(
        CameraChecker
        pthread
        opencv_core
        opencv_highgui
        opencv_calib3d
        boost_date_time
        boost_chrono
        boost_system
        boost_thread
        boost_filesystem
        GL
        ${EIGEN3_LIBS}
        ${Pangolin_LIBRARIES}
        ${CHOLMOD_LIBRARIES}
        ${BLAS_LIBRARIES}
        ${LAPACK_LIBRARIES}
)
