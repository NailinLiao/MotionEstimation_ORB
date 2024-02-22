#include <iostream>
#include "include/ORB_WORKER.h"

int main() {
    cv::VideoCapture cap("../test_2.mp4"); // 替换为你的视频文件路径
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return -1;
    }

    cv::Mat frame, laster_frame;
    ORB_WORKER oRB_WORKER = ORB_WORKER(0.2, 1920, 1080);
    cap >> frame; // 读取第一帧

    cv::cvtColor(frame, laster_frame, cv::COLOR_BGR2GRAY);
    cv::Point2f point_to_transform(frame.cols / 2, frame.rows / 2); // 假设这是你要变换的点

    for (int i = 0; i < 500; ++i) { // 循环处理前500帧
        if (i % 30 == 0) {// 30帧重置一下矩阵，矩阵累加会有误差；
            oRB_WORKER.reset_H();
        }
        cap >> frame; // 读取第一帧
        cv::Mat GAY;
        cv::cvtColor(frame, GAY, cv::COLOR_BGR2GRAY);
        auto start_time = std::chrono::high_resolution_clock::now();

        oRB_WORKER.main_run(frame);
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        std::cout << "耗时：" << duration << std::endl;
        cv::Point2f warp_point = oRB_WORKER.get_ORB_swap(point_to_transform);

        int radius = 5; // 圆的半径
        cv::Scalar color(0, 255, 255); // 蓝色圆圈 (BGR)
        int thickness = 2; // 线条粗细
////// 在frame上绘制圆
        cv::circle(frame, cv::Point(cvRound(warp_point.x), cvRound(warp_point.y)), radius, color,
                   thickness);
        cv::imshow("frame", frame);
        cv::waitKey(1); // 等待10毫秒以显示图像


    }
    return 0;
}
