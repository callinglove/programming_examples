#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
  
using namespace std;
using namespace cv;

// 得到图像的直方图
bool getHistogram(const Mat& image, Mat& hist)
{
    int channels[] = {0};
    int dims = 1;  
    int histSize[] = {256};
    float granges[] = {0, 256};
    const float *ranges[] = {granges};
    calcHist(&image, 1, channels, Mat(), hist, dims, histSize, ranges);

    return true;
}
 //  将图像直方图展示出来
bool getHistogramImage(const Mat& image, Mat& histImage) 
{
    Mat hist;
    getHistogram(image, hist);

    double maxValue = 0;  
    minMaxLoc(hist, 0, &maxValue, 0, 0);  

#if 0
    histImage.create(256, 256, CV_8U);
    histImage.setTo(0);

    for(int i = 0; i < 256; i++)  
    {  
        float value = hist.at<float>(i, 0);
        int intensity = saturate_cast<int>(256 - 256* (value/maxValue));  
        rectangle(showImage, Point(i,256 - 1), Point((i+1)-1, intensity), Scalar(255));  
    }
#else
    int scale = 1;
    int histHeight = hist.rows;

    histImage.create(histHeight, hist.rows * scale, CV_8UC3);  //初始化直方图输出图像
    histImage.setTo(0);

    int hpt = saturate_cast<int>(0.9 * histHeight);  //设置最大值并防止溢出
    for (int i = 0; i < 256; i++)
    {
        float binValue = hist.at<float>(i, 0);
        int realValue = saturate_cast<int>(binValue * hpt / maxValue);  //归一化数据
        line(histImage, Point(i * scale, histHeight - 1), Point(i * scale, histHeight - realValue), Scalar(0, 255, 0), scale, 8);
    }
#endif

    return true;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "special image for histogram" << endl;
    }

    Mat image = imread(argv[1]);
    if(image.empty())
    {  
        cout << "fail to load the image" << endl;  
        return 0;  
    }  
    Mat histogramImage;
    getHistogramImage(image, histogramImage);

    imshow("image", image);  
    imshow("histogramImage", histogramImage);

    waitKey(0);
    destroyAllWindows();

    return 0;  
}
/* 
--------------------- 
作者：Jasen_Fu 
来源：CSDN 
原文：https://blog.csdn.net/piaoxuezhong/article/details/54588270 
版权声明：本文为博主原创文章，转载请附上博文链接！

https://blog.csdn.net/xiaowei_cqu/article/details/8833799
单个直方图灰色图
多个直方图的彩色图
二维直方图
 */
