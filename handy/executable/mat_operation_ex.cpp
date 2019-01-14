#include "cvUtils/MatOperation.h"
#include <iostream>

int main(int argc, char *argv[])
{
    cv::Size size(4, 5);
    cv::Mat src(size, CV_32F, cv::Scalar(0));
    cv::randn(src, 0, 1);

    std::cout << "ori mat:" << std::endl;
    std::cout << src << std::endl;

    cv::Mat dst;
    handy::zt(src, dst);
    std::cout << "after zt :" << std::endl;
    std::cout << dst << std::endl;

	
	return 0;
}
