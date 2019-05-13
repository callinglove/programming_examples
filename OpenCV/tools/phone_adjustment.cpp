#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
  
using namespace cv;
  
cv::Mat org,dst,img,tmp;
std::vector<cv::Point2f> points;

void on_mouse(int event,int x,int y,int flags,void *ustc)//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号  
{
    static Point pre_pt(-1,-1);//初始坐标  
    static Point cur_pt(-1,-1);//实时坐标  
    char temp[16];  
    if (event == CV_EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处划圆  
    {
        pre_pt = Point(x,y);
        points.push_back(cv::Point2f(pre_pt));

        // sprintf(temp,"(%d,%d)",x,y);
        // putText(img,temp,pre_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255),1,8);//在窗口上显示坐标
        circle(img, pre_pt, 5, Scalar(0,0,255), CV_FILLED, CV_AA, 0);//划圆  
        imshow("img", img);

        // std::cout << "[" << x << ", " << y << "]" << std::endl;
    }
/*
    else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//左键没有按下的情况下鼠标移动的处理函数  
    {  
        // img.copyTo(tmp);//将img复制到临时图像tmp上，用于显示实时坐标  
        // sprintf(temp,"(%d,%d)",x,y);  
        // cur_pt = Point(x,y);  
        // putText(tmp,temp,cur_pt,FONT_HERSHEY_SIMPLEX,2,Scalar(0,0,0,255));//只是实时显示鼠标移动的坐标  
        // imshow("img",tmp);
        printf("[%d, %d]\n", x, y);
    }  
    else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))//左键按下时，鼠标移动，则在图像上划矩形  
    {  
        img.copyTo(tmp);  
        sprintf(temp,"(%d,%d)",x,y);  
        cur_pt = Point(x,y);  
        putText(tmp,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255));  
        rectangle(tmp,pre_pt,cur_pt,Scalar(0,255,0,0),1,8,0);//在临时图像上实时显示鼠标拖动时形成的矩形  
        imshow("img",tmp);  
    }  
    else if (event == CV_EVENT_LBUTTONUP)//左键松开，将在图像上划矩形  
    {  
        org.copyTo(img);  
        sprintf(temp,"(%d,%d)",x,y);  
        cur_pt = Point(x,y);  
        putText(img,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255));  
        circle(img,pre_pt,2,Scalar(255,0,0,0),CV_FILLED,CV_AA,0);  
        rectangle(img,pre_pt,cur_pt,Scalar(0,255,0,0),1,8,0);//根据初始点和结束点，将矩形画到img上  
        imshow("img",img);  
        img.copyTo(tmp);  
        //截取矩形包围的图像，并保存到dst中  
        int width = abs(pre_pt.x - cur_pt.x);  
        int height = abs(pre_pt.y - cur_pt.y);  
        if (width == 0 || height == 0)  
        {  
            printf("width == 0 || height == 0");  
            return;  
        }  
        dst = org(Rect(min(cur_pt.x,pre_pt.x),min(cur_pt.y,pre_pt.y),width,height));  
        namedWindow("dst");  
        imshow("dst",dst);  
        waitKey(0);  
    }
*/
}

bool cmp(cv::Point2f& fst, cv::Point2f& scd) {
    if (abs(fst.y - scd.y) < 300) {
        return fst.x < scd.x;
    }
    else {
        return fst.y < scd.y;
    }
}

void image_ajustment()
{
    if (points.size() != 4) {
        points.clear();
        org.copyTo(img);

        return;
    }

    // 左上 右上 左下 右下
    std::sort(points.begin(), points.end(), cmp);
    std::cout << "src point" << std::endl;
    for (cv::Point p: points)
    {
        std::cout << "[" << p.x << ", " << p.y << "]" << std::endl;
    }

    std::vector< cv::Point2f > dst_points;
    int width = ((points[1].x + points[3].x) / 2) - ((points[0].x + points[2].x) / 2);
    int height = ((points[2].y + points[3].y) / 2) - ((points[0].y + points[1].y) / 2);
    dst_points.push_back(Point2f(0, 0));
    dst_points.push_back(Point2f(width, 0));
    dst_points.push_back(Point2f(0, height));
    dst_points.push_back(Point2f(width, height));

    std::cout << "dst point" << std::endl;
    for (cv::Point p: dst_points)
    {
        std::cout << "[" << p.x << ", " << p.y << "]" << std::endl;
    }

    cv::Mat M = cv::getPerspectiveTransform(points, dst_points);
    cv::Mat warp;
    cv::warpPerspective(org, warp, M, cv::Size(width, height));
    cv::imwrite("wwww.jpg", warp);

    points.clear();
    org.copyTo(img);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        exit(EXIT_FAILURE);
    }

    org = imread(argv[1]);
    if (org.empty())
    {
        printf("decode file failed!!\n");
        exit(EXIT_FAILURE);
    }

    org.copyTo(img);  
    org.copyTo(tmp);

    namedWindow("img", WINDOW_KEEPRATIO);
    setMouseCallback("img",on_mouse,0);
    while (true)
    {
        imshow("img",img);
        int key = cv::waitKey(0);
        if (key == 27 || key == 'q' || key == 'Q') {
            break;
        }
        else if (key == 'c') {
            points.clear();
            org.copyTo(img);
        }
        else if (key == 's') {
            std::cout << "ajustment " << std::endl;
            image_ajustment();
        }
    }
    
    return 0;
}  
