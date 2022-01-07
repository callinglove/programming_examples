#include <libavutil/pixfmt.h>
#include <libavutil/frame.h>
#include <stdio.h>
#include <stdlib.h>


int main() {

    for (int i = 0; i < AV_PIX_FMT_NB; ++i) {
        AVFrame *pAVFrame = av_frame_alloc();
        if (NULL == pAVFrame)
        {
            printf("av_frame_alloc failed");
            return -1;
        }

        pAVFrame->format = i;
        pAVFrame->width  = 191;
        pAVFrame->height = 123;
        if (av_frame_get_buffer(pAVFrame, 0) < 0)
        {
            printf("===========\n");
            return -1;
        }
        printf("[%d] %d %d %d %d\n", pAVFrame->format, pAVFrame->linesize[0], pAVFrame->linesize[1], pAVFrame->linesize[2], pAVFrame->linesize[3]);

        av_frame_free(&pAVFrame);
    }

    return 0;
}
