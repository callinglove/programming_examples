#include "cvUtils/OpencvText.h"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

getImageByStr(std::string& str, cv::Mat& dst)
{
    std::string text = str;
    int font_face = cv::FONT_HERSHEY_COMPLEX;
    double font_scale = 2;
    int thickness = 2;
    int baseline;

    //cv::Size textSize = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
    //dst = cv::Mat::zeros(cv::Size(textSize.width + 2, textSize.height + 2), CV_8U);
    //cv::Point org = cv::Point(1, textSize.height - 1);
    //cv::putText(dst, text, org, font_face, font_scale, cv::Scalar(255), thickness, 8, 0);

    const char* font_path = "../res/font/STKAITI.TTF";
    handy::Cv310Text put_text(font_path, 150);

    cv::Size size = put_text.getTextSize(str.c_str());
    dst = cv::Mat::zeros(size.height + 2, size.width + 2, CV_8U);

    put_text.putText(dst, str.c_str(), cv::Point(1, size.height - 1), cv::Scalar(255, 5, 46));

    for (int i = rand() % 2; i < dst.rows; i += 3)
    {
        dst.row(i) = 0;
    }

    for (int i = rand() % 2; i < dst.cols; i += 3)
    {
        dst.col(i) = 0;
    }

    return true;
}


int main(int argc, char *argv[])
{
	// 在MinGW环境下,源码文件是ANSI编码方式
	std::string str = "中华人民共和国合同法";
    cv::Mat textMat;
	getImageByStr(str, textMat);
	cv::imshow("view", textMat);
	
	cv::waitKey(0);
	
	return 0;
}
