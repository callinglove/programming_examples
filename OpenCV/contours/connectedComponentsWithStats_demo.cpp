#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void connectedComponentsWithStatsDemo(cv::Mat& bgrImage)
{
    Mat grayImage;
    cv::cvtColor(bgrImage, grayImage, COLOR_BGR2GRAY);

    cv::Mat  img_edge, labels, img_color, stats,centroids;
    cv::threshold(grayImage, img_edge, 128, 255, cv::THRESH_BINARY);
    bitwise_not(img_edge,img_edge);
    cv::imshow("Image after threshold", img_edge);

    /* stats
    cv::CC_STAT_LEFT = 0, 
    cv::CC_STAT_TOP = 1, 
    cv::CC_STAT_WIDTH = 2, 
    cv::CC_STAT_HEIGHT = 3, 
    cv::CC_STAT_AREA = 4, 
    cv::CC_STAT_MAX = 5 
    */
    int nccomps = cv::connectedComponentsWithStats(
        img_edge, labels,
        stats, centroids
    );
    cout << "Total Connected Components Detected: " << nccomps << endl;

    vector<cv::Vec3b> colors(nccomps+1);
    colors[0] = Vec3b(0,0,0); // background pixels remain black.
    for( int i = 1; i < nccomps; i++ )
    {
        colors[i] = Vec3b(rand()%256, rand()%256, rand()%256);
        if( stats.at<int>(i, cv::CC_STAT_AREA) < 200 )
        {
            colors[i] = Vec3b(0,0,0); // small regions are painted with black too.
        }
    }

    img_color = Mat::zeros(grayImage.size(), CV_8UC3);
    for( int y = 0; y < img_color.rows; y++ )
    {
        for( int x = 0; x < img_color.cols; x++ )
        {
            int label = labels.at<int>(y, x);
            CV_Assert(0 <= label && label <= nccomps);
            img_color.at<cv::Vec3b>(y, x) = colors[label];
        }
    }
    cv::imshow("Labeled map", img_color);
}

int main(int argc, char* argv[])
{
    cv::String pattern = "C:\\Users\\golden\\Desktop\\voc实验局00\\视频遮挡\\*";
    std::vector<cv::String> imageList;
    cv::glob(pattern, imageList, true);

    size_t i = 0;
    size_t imageNum = imageList.size();
    while(i < imageNum)
    {
        // IMREAD_UNCHANGED
        // IMREAD_GRAYSCALE
        cv::Mat bgrImage = cv::imread(imageList[i], IMREAD_COLOR);
        if (bgrImage.empty())
        {
            imageList.erase(imageList.begin() + i);
            --imageNum;
            if (i == imageNum)
            {
                i = 0;
            }
        }
        connectedComponentsWithStatsDemo(bgrImage);

        int key = cv::waitKey();
        if (key == 'q')
        {
            break;
        } else if (key == 'n')
        {
            ++i;
            if (i == imageNum)
            {
                i = 0;
            }
        } else if (key == 'p')
        {
            if (i == 0)
            {
                i = imageNum - 1;
            }
            else
            {
                --i;
            }
        } else if (key == 'd')
        {
            imageList.erase(imageList.begin() + i);
            --imageNum;
            if (i == imageNum)
            {
                i = 0;
            }
        }
    }

    return 0;
}