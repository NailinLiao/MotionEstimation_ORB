cmake_minimum_required(VERSION 3.18)
project(ORB_Jitter)

set(CMAKE_CXX_STANDARD 17)


if (${WITH_X86})
    include(env/3rdparty_x86.cmake)
elseif (${WITH_RV1126})
    include(env/3rdparty_rv1126.cmake)
elseif (${WITH_RK3588})
    include(env/3rdparty_rk3588.cmake)
else ()
    # 添加OpenCV查找模块
    find_package(OpenCV REQUIRED core highgui imgproc features2d videoio imgcodecs calib3d)

    if (NOT OpenCV_FOUND)
        message(FATAL_ERROR "OpenCV not found.")
    endif ()
endif ()


include_directories(include ${OpenCV_INCLUDE_DIRS})

# 收集源文件
file(GLOB_RECURSE ORB_SRC src/*.cpp src/*.cc)
file(GLOB_RECURSE ORB_HEAD include/*.hpp include/*.h)

#add_executable(ORB_Jitter main.cpp src/ORB_WORKER.cpp)

add_executable(ORB_DEMO
        ${ORB_SRC}
        ${ORB_HEAD}
        ${CORE_LIB_SRC}
        ${CORE_LIB_HEAD}
        ${OPENCV_LIB_SRC}
        ${OPENCV_LIB_HEAD}
        ORB_DEMO.cpp
        )

target_link_libraries(ORB_DEMO
        pthread
        ${FMT_LIBRARY}
        ${BOOST_LIBRARY}
        ${RGA_LIBRARY}
        ${OpenCV_LIBS}
        ${RKNN_LIBRARY}
        ${FFTW_LIBRARY}
        ${FREETYPE_LIBRARY}
        ${MPP_LIBRARY}
        ${MPPENCODER_LIBRARY}
        ${RKAIQ_LIBRARY}
        ${DB_LIBRARY}
        )

## 链接OpenCV库到目标可执行文件
#target_link_libraries(ORB_Jitter PRIVATE ${OpenCV_LIBS})