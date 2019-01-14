//
// Created by yanggs on 18-11-02.
//

#ifndef HANDY_MAT_OPERATION_H
#define HANDY_MAT_OPERATION_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

namespace handy {	
	
    /**
    * 将一张图片Z遍历成一行数据，仅支持一通道float型Mat
    * @param src	带遍历的Mat (n, m)
    * @param dst	遍历结果    (1, n*m)
    * @return
    */
	bool zt(const cv::Mat& src, cv::Mat& dst);

    /**
    * zt函数的逆变换
    * @param src (1, n*m)
    * @param dst (n, m)
    * @param size (n, m)
    * @return
    */
	bool izt(const cv::Mat& src, cv::Mat& dst, cv::Size& size);
}

#endif //HANDY_MAT_OPERATION_H
