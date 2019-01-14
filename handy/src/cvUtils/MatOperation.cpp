#include "cvUtils/MatOperation.h"

namespace handy {
	
// https://blog.csdn.net/chenpkai/article/details/52477632?utm_source=blogxgwz2
bool zt(const cv::Mat& src, cv::Mat& dst)
{
    if (src.rows != src.cols && src.type() != CV_32F)
    {
        return false;
    }

    dst.create(1, src.rows * src.cols, CV_32F);

    int rows = src.rows;
    int cols = src.cols;

    int rowIdx = 0, colIdx = 0;
    int cntDiagonalLine = rows + cols - 1;

    float *dstPtr = (float *)dst.data;

    for (int s = 0; s < cntDiagonalLine; ++s)
    {
        if ((rowIdx + colIdx) % 2 == 0)  // 偶数行 
        {
            while (rowIdx >= 0 && colIdx < cols)
            {
                *dstPtr++ = src.at<float>(rowIdx--, colIdx++);
            }

            if (colIdx == cols)     // 向下移动
            {
                colIdx = cols - 1;
                rowIdx += 2;
            }
            else if (rowIdx < 0)
            {
                rowIdx = 0;
            }
        }
        else // 奇数行
        {
            while (rowIdx < rows && colIdx >= 0)
            {
                *dstPtr++ = src.at<float>(rowIdx++, colIdx--);
            }

            if (rowIdx == rows)     // 向右移
            {
                rowIdx = rows - 1;
                colIdx += 2;
            }
            else if (colIdx < 0)
            {
                colIdx = 0;
            }
        }
    }

    return true;
}

bool izt(const cv::Mat& src, cv::Mat& dst, cv::Size& size)
{
    cv::Size srcSize = src.size();
    if ((srcSize.width * srcSize.height) != (size.width * size.height) && src.type() != CV_32F)
    {
        return false;
    }

    dst.create(size, CV_32F);

    int rows = dst.rows;
    int cols = dst.cols;

    int rowIdx = 0, colIdx = 0;
    int cntDiagonalLine = rows + cols - 1;

    float *srcPtr = (float *)src.data;

    for (int s = 0; s < cntDiagonalLine; ++s)
    {
        if ((rowIdx + colIdx) % 2 == 0)  // 偶数行 
        {
            while (rowIdx >= 0 && colIdx < cols)
            {
                dst.at<float>(rowIdx--, colIdx++) = *srcPtr++;
            }

            if (colIdx == cols)     // 向下移动
            {
                colIdx = cols - 1;
                rowIdx += 2;
            }
            else if (rowIdx < 0)
            {
                rowIdx = 0;
            }
        }
        else // 奇数行
        {
            while (rowIdx < rows && colIdx >= 0)
            {
                dst.at<float>(rowIdx++, colIdx--) = *srcPtr++;
            }

            if (rowIdx == rows)     // 向右移
            {
                rowIdx = rows - 1;
                colIdx += 2;
            }
            else if (colIdx < 0)
            {
                colIdx = 0;
            }
        }
    }

    return true;
}
	
}
