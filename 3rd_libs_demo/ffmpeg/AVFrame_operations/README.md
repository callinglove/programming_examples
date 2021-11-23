## ffmpeg中支持的像素格式以及其存储方式

一般的视频采集芯片输出的码流一般都是 YUV 格式数据流，后续视频处理也是对 YUV 数据流进行编码和解析。所以，了解 YUV 数据流对做视频领域的人而言，至关重要。

### 格式分量简介

#### RGB

RGB 分别表示红（R）、绿（G）、蓝（B），也就是三原色，将它们以不同的比例叠加，可以产生不同的颜色。

比如一张 1920 * 1280 的图片，代表着有 1920 * 1280 个像素点。如果采用 RGB 编码方式，每个像素点都有红、绿、蓝三个原色，其中每个原色占用 8 个字节，每个像素占用 24 个字节。

那么，一张 1920 * 1280 大小的图片，就占用 `1920 * 1280 * 3 / 1024 / 1024 = 7.03125MB` 存储空间。

#### YUV

YUV 编码采用了明亮度和色度表示每个像素的颜色。

其中 Y 表示明亮度（Luminance、Luma），也就是灰阶值。

U、V 表示色度（Chrominance 或 Chroma），描述的是色调和饱和度。

YCbCr 其实是 YUV 经过缩放和偏移的翻版。其中 Y 与 YUV 中的 Y 含义一致,Cb,Cr 同样都指色彩，只是在表示方法上不同而已。YCbCr 其中 Y 是指亮度分量，Cb 指蓝色色度分量，而 Cr 指红色色度分量。

#### YUV 优点

对于 YUV 所表示的图像，Y 和 UV 分量是分离的。如果只有 Y 分量而没有 UV 分离，那么图像表示的就是黑白图像。彩色电视机采用的就是 YUV 图像，解决与和黑白电视机的兼容问题，使黑白电视机也能接受彩色电视信号。

人眼对色度的敏感程度低于对亮度的敏感程度。主要原因是视网膜杆细胞多于视网膜锥细胞，其中视网膜杆细胞的作用就是识别亮度，视网膜锥细胞的作用就是识别色度。所以，眼睛对于亮度的分辨要比对颜色的分辨精细一些。

利用这个原理，可以把色度信息减少一点，人眼也无法查觉这一点。

所以，并不是每个像素点都需要包含了 Y、U、V 三个分量，根据不同的采样格式，可以每个 Y 分量都对应自己的 UV 分量，也可以几个 Y 分量共用 UV 分量。相比 RGB，能够节约不少存储空间。

#### YUV采样格式

YUV主流采样格式，保留Y完整信息，对UV分量进行下采样

- 4:4:4 表示 Y、U、V 三分量采样率相同，即每个像素的三分量信息完整，都是 8bit，每个像素占用3个字节。
    - 四个像素为： [Y0 U0 V0] [Y1 U1 V1] [Y2 U2 V2] [Y3 U3 V3]
    - 采样的码流为： Y0 U0 V0 Y1 U1 V1 Y2 U2 V2 Y3 U3 V3
    - 映射出的像素点为：[Y0 U0 V0] [Y1 U1 V1] [Y2 U2 V2] [Y3 U3 V3]
    - 空间占用 `1920 * 1280 * 3 / 1024 / 1024 = 7.03125MB` 跟BGR占用的空间一样
- 4:2:2 表示 2:1 的水平下采样，没有垂直下采样。对每两个Y共用一组UV分量
    - 四个像素为： [Y0 U0 V0] [Y1 U1 V1] [Y2 U2 V2] [Y3 U3 V3]
    - 采样的码流为： Y0 U0 Y1 V1 Y2 U2 Y3 U3
    - 映射出的像素点为：[Y0 U0 V1]、[Y1 U0 V1]、[Y2 U2 V3]、[Y3 U2 V3]
    - 空间占用 `(1920 * 1280 + 1920 * 1080 * 0.5 * 2) / 1024 / 1024 = 4.6875M`
- 4:2:0 表示 2:1 的水平下采样，2:1 的垂直下采样。每四个Y共用一组UV分量。对每条扫描线来说，只有一种色度分量以 2:1 的采样率存储，相邻的扫描行存储不同的色度分量。也就是说，如果第一行是 4:2:0，下一行就是 4:0:2，在下一行就是 4:2:0，以此类推
    - 图像像素为:

        ```
        [Y0 U0 V0]、[Y1 U1 V1]、 [Y2 U2 V2]、 [Y3 U3 V3]
        [Y5 U5 V5]、[Y6 U6 V6]、 [Y7 U7 V7] 、[Y8 U8 V8]
        ```
​    - 采样的码流为：

        ```
        Y0 U0 Y1 Y2 U2 Y3 
        Y5 V5 Y6 Y7 V7 Y8
        ```
​    - 映射出的像素点为：

        ```
        [Y0 U0 V5]、[Y1 U0 V5]、[Y2 U2 V7]、[Y3 U2 V7]
        [Y5 U0 V5]、[Y6 U0 V5]、[Y7 U2 V7]、[Y8 U2 V7]
        ```
    - 空间占用 `(1920 * 1280 + 1920 * 1080 * 0.25 * 2) / 1024 / 1024 = 3.515625M`
- 4:1:1 表示 4:1 的水平下采样，没有垂直下采样。每四个Y共用一组UV分量。
    - 图像像素 [Y0 U0 V0]、[Y1 U1 V1]、 [Y2 U2 V2]、 [Y3 U3 V3]
    - 采样码流 Y0 U0 Y1 Y2 V2 Y3
    - 映射出的像素点 [Y0 U0 V2]、[Y1 U0 V2]、 [Y2 U0 V2]、 [Y3 U0 V2]

#### YUV存储格式

YUV格式有两大类：packed和planar。注：planar还分平面存储和平面打包格式。

- 对于packed的YUV格式，每个像素点的Y,U,V是连续交错存储的。
- 对于planar的YUV格式，先连续存储所有像素点的Y，紧接着存储所有像素点的U，然后是所有像素点的V（平面存储格式），或者 紧接着UV交错存储（平面打包格式）。


### 像素格式定义以及描述

- libavutil/pixfmt.h定义像素格式enum AVPixelFormat
- libavutil/pixdesc.h定义`struct AVPixFmtDescriptor`数据结构用以描述像素格式
- libavutil/pixdesc.c中`static const AVPixFmtDescriptor av_pix_fmt_descriptors[AV_PIX_FMT_NB]`用以描述各像素格式

```
// 像素名
name            : yuv420p
// comp成员所有的像素个数, (1-4)
nb_components   : 3
// 仅对有亮度的像素组成的像素格式有效,表示右移多少位 亮度的宽 来得到 色度的宽 | 如 yuv420 1920x1080 : Y 宽 ：1920  则 UV 色度的宽 ： 1920 >> 1 : 960
log2_chroma_w   : 1
// 同上 表示右移多少位 亮度的高来得到 色度的高.
log2_chroma_h   : 1
// AV_PIX_FMT_FLAG_ 标志的组合
flags           : 16
// 以逗号分隔的替代像素名，大部分为空.
alias           : (null)
// comp[4] 描述像素如何包装的参数, 大小 nb_components 指定.
// 如果该像素格式包含1或2个分量，则luma(亮度分量)为0平面。
// 如果该像素格式包含3或4个分量组成：
//     如果设置了RGB标志，则0为红色，1为绿色，2为蓝色；
//     否则0为亮度，1为色度U，2为色度V。
// 如果存在Alpha(透明通道)，则Alpha通道始终是最后一个分量(4), 如 YUVA420

// plane  ：四个平面中的第几平面, 对应存储在frame->data[plane]中.
// step   ：2个水平连续像素之间的元素数,或者可理解为步长,偏移。step和offset 可以对比下 nv12 和 yuyv 422 的存储理解下, 下面有栗子
// offset ：第一个像素分量之前的元素数。
// shift  ：必须移走的最低有效位数。
// depth  ：常见的位深, bit/pix
comp[0]         :   
plane : 0, step : 1, offset : 0, shift : 0, depth : 8
comp[1]         :   
plane : 1, step : 1, offset : 0, shift : 0, depth : 8
comp[2]         :   
plane : 2, step : 1, offset : 0, shift : 0, depth : 8
```

### 像素格式描述理解对比

YUV 数据有两种存储格式：平面格式（planar format）和打包格式（packed format）。

- planar format：先连续存储所有像素点的 Y，紧接着存储所有像素点的 U，随后是所有像素点的 V。
- packed format：每个像素点的 Y、U、V 是连续交错存储的。

nv12是一种two-plane模式，即分Y和UV两个plane，但UV为交错存储，V跟在U后面
```
///< planar YUV 4:2:0, 12bpp, 1 plane for Y and 1 plane for the UV components, which are interleaved (first byte U and the following byte V)
[AV_PIX_FMT_NV12] = {
    .name = "nv12",     // 像素格式名称
    .nb_components = 3, // 3 组像素分量组成
    .log2_chroma_w = 1, // 色宽 为 亮宽 >> 1
    .log2_chroma_h = 1, // 色高 为 亮高 >> 1
    .comp = {
        { 0, 1, 0, 0, 8, 0, 7, 1 },  /* Y */  // 存储在第0平面, Y是连续的 第一个Y前面的像素数为0个偏移也即0, 必须移走0位, 位深 8
        { 1, 2, 0, 0, 8, 1, 7, 1 },  /* U */  // 存储在第1平面, 连续两个U之间偏移为2 第一个U前面的像素数为0个偏移也即0, 必须移走0位, 位深 8
        { 1, 2, 1, 0, 8, 1, 7, 2 },  /* V */  // 存储在第1平面, 连续两个V之间偏移为2 V前面的像素数为1个偏移也即1, 必须移走0位, 位深 8
    },
    .flags = AV_PIX_FMT_FLAG_PLANAR,    // flag plane
}

采样如下图示
Y   Y   Y   Y
 UV       UV
Y   Y   Y   Y
Y   Y   Y   Y
 UV       UV
Y   Y   Y   Y
存储如下图示
YYYYYYYYYYYYYYYY
UVUVUVUV
```

```
///< packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
[AV_PIX_FMT_YUYV422] = {
    .name = "yuyv422",
    .nb_components = 3, // 3组像素分量组成
    .log2_chroma_w = 1, // 水平2:1下采样，色宽 为 亮宽 >> 1
    .log2_chroma_h = 0, // 不垂直下采样，色高 为 亮高 >> 1
    .comp = {
        { 0, 2, 0, 0, 8, 1, 7, 1 },  /* Y */  // 存储在第0平面 连续两个的Y之间偏移为2 第一个像素偏移为0(第一个就是它) 必须移走0位 位深 8
        { 0, 4, 1, 0, 8, 3, 7, 2 },  /* U */  // 存储在第0平面 连续两个的U之间偏移为4 第一个像素偏移为1(第2个就是它) 必须移走0位 位深 8
        { 0, 4, 3, 0, 8, 3, 7, 4 },  /* V */  // 存储在第0平面 连续两个的V之间偏移为4 第一个像素偏移为3(第4个就是它) 必须移走0位 位深 8
    },
},

采样存储如下
Y0 U0 Y1 V0 Y2 U2 Y3 V2
```

- 各像素格式描述输出参见 pix_fmt_dsc.c
- `ffmpeg -pix_fmts` 显示像素格式

### AVFrame使用

在ffmpeg中，解码后的像素元素存储在AVFrame中，这里介绍AVFrame的操作

参考
- [FFMPEG结构体分析：AVFrame](https://blog.csdn.net/leixiaohua1020/article/details/14214577)
- [FFMPEG 实现 YUV，RGB各种图像原始数据之间的转换（swscale）](https://blog.csdn.net/leixiaohua1020/article/details/14215391)

#### 生成YUV文件并播放

- `ffmpeg -i input.mp4 -s 640x272 -pix_fmt yuv420p 640x272_yuv420p.yuv` 生成宽640长272的yuv420p格式的yuv文件
- `ffplay -f rawvideo -video_size 640X272 -pix_fmt yuv420p -i 640x272_yuv420p.yuv` 播放yuv文件，必须指定视频长宽以及yuv格式

#### AVFrame保存YUV


