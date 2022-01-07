#include <SDL2/SDL.h>
#include <libavutil/pixfmt.h>
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    SDL_Window *screen;
    SDL_Renderer * renderer;
    SDL_Texture *texture;
    SDL_Rect rect;
    AVFrame *pFrameYUV;
#if 0
    const int w = 640;
    const int h = 272;
    const char *yuv_file = "640x272_yuv420p.yuv";
#else
    const int w = 639;
    const int h = 271;
    const char *yuv_file = "639x271_yuv420p.yuv";
#endif
    FILE *yuv_fp;

    // SDL2 教程 [TwinklebearDev SDL 2.0 Tutorial Index](https://www.willusher.io/pages/sdl2/)
    // SDL2初始化
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // 创建窗口
    screen = SDL_CreateWindow("display yuv", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        w, h, SDL_WINDOW_OPENGL);
    if (!screen)
    {
        printf("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // 创建渲染器
    renderer = SDL_CreateRenderer(screen, -1, 0);
    if (NULL == renderer)
    {
        printf("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_DestroyWindow(screen);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // 创建纹理，纹理是渲染器的内容
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, w, h);
    if (NULL == texture)
    {
        printf("SDL_CreateTexture Error: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(screen);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // 更新区
    rect.x = 0;
    rect.y = 0;
    rect.w = w;
    rect.h = h;

    // 分配存储yuv的AVFrame
    pFrameYUV=av_frame_alloc();
    pFrameYUV->width = w;
    pFrameYUV->height = h;
    pFrameYUV->format = AV_PIX_FMT_YUV420P;

#ifdef USE_GET_BUFFER
    av_frame_get_buffer(pFrameYUV, 0);
    int y_size = w * h;
    printf("%d %d\n", y_size, y_size / 4);
#else
    /* 
     * 1、这种方式不需要了解YUV元素的个数以及存储方式，只需读取bufsiz字节，即一张YUV所有数据
     * 2、释放的时候需要单独释放申请的buf，buf不在pFrameYUV释放的释放 https://www.cnblogs.com/lidabo/p/15040688.html
     */
    // align取值需要确认，否则取yuv值不对
    int align = 1;
    int bufsiz = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, w, h, align);
    uint8_t *buf = (uint8_t*)av_malloc(bufsiz);
    av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize, buf, AV_PIX_FMT_YUV420P, w, h, align);
    printf("%d [%d][%d][%d]\n", bufsiz, pFrameYUV->linesize[0], pFrameYUV->linesize[1], pFrameYUV->linesize[2]);
    printf("%d %d %%d", pFrameYUV->data[1] - pFrameYUV->data[0], pFrameYUV->data[2] - pFrameYUV->data[1]);
    fflush(stdout);
#endif
    yuv_fp = fopen(yuv_file,"rb");

    while(1)
    {
        if (feof(yuv_fp))
        {
            break;
        }
        // 读取数据

#ifdef USE_GET_BUFFER
        /*
         * 读取的字节数不能以 w*h 为准，
         * 经测试 639X271 data[0]存 639X271字节 data[1]存320X136字节 data[2]存320X136字节
         * 除非非常熟悉数据存储格式
         * 
         * 网上许多保存YUV的写法多数是错误的(当然很多情况下结果是正确的)，包括雷神的文章
         * 
         * AVFrame的linesize保存了行采样的字节数，AVFrame却没有地方列采样的字节数
         * 
         * 大华的PlaySDK中回调 PLAY_SetDecodeCallBack设置的回调函数 
         * void (CALLBACK* fCBDecode)(LONG nPort, FRAME_DECODE_INFO* pFrameDecodeInfo, FRAME_INFO_EX* pFrameInfo, void* pUser);
         *
         *  pAVFrame->format = AV_PIX_FMT_YUV420P;
         *  pAVFrame->width  = pFrameDecodeInfo->nWidth[0];
         *  pAVFrame->height = pFrameDecodeInfo->nHeight[0];
         *  pAVFrame->linesize[0] = pFrameDecodeInfo->nStride[0];
         *  pAVFrame->linesize[1] = pFrameDecodeInfo->nStride[1];
         *  pAVFrame->linesize[2] = pFrameDecodeInfo->nStride[2];
         *  if (av_frame_get_buffer(pAVFrame, 0) < 0)
         *  {
         *      return;
         *  }
         *  
         *  for (int i = 0; i < 3; ++i)
         *  {
         *      memcpy(pAVFrame->data[0], 
         *          pFrameDecodeInfo->pVideoData[0], 
         *          pFrameDecodeInfo->nStride[0] * pFrameDecodeInfo->nHeight[0]);
         *  }
         * 
         *  linesize[0] 每行Y元素字节偏移数，也可以理解为保存一行Y元素占用的空间，
         *  1. 由于字节对齐，linesize[0]一般>=width
         *  2. 由于各库的实现不同，每行Y元素字节偏移数并不相同，经测试大华PlaySDK的偏移要比ffmpeg的大
         *  3. av_frame_get_buffer在linesize[0]为零时，自动填充linesize数组，不为零时，则根据赋值情况来分配空间
         */
        fread(pFrameYUV->data[0], 1, y_size, yuv_fp);
        fread(pFrameYUV->data[1], 1, y_size / 4, yuv_fp);
        fread(pFrameYUV->data[2], 1, y_size / 4, yuv_fp);
#else
        fread(buf, 1, bufsiz, yuv_fp);
#endif

#if 0
        SDL_UpdateTexture(texture, NULL, pFrameYUV->data[0], pFrameYUV->linesize[0]);
#else
        // 给纹理添加数据
        SDL_UpdateYUVTexture(texture, &rect,
            pFrameYUV->data[0], pFrameYUV->linesize[0],
            pFrameYUV->data[1], pFrameYUV->linesize[1],
            pFrameYUV->data[2], pFrameYUV->linesize[2]);
#endif	

        SDL_RenderClear(renderer);
        // 给渲染器添加纹理并指定其更新区域
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        // 渲染器显示纹理
        SDL_RenderPresent(renderer);


        SDL_Delay(40);
    }

    fclose(yuv_fp);

    av_frame_free(&pFrameYUV);
#ifndef USE_GET_BUFFER
    av_free(buf);
    buf = NULL;
#endif

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();

    return 0;
}