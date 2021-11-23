#include <libavutil/pixfmt.h>
#include <libavutil/pixdesc.h>
#include <stdio.h>
#include <stdlib.h>


void print_fmt_descs(const AVPixFmtDescriptor *pfd);

void print_fmt_descs(const AVPixFmtDescriptor *pfd) {
    printf("name            : %s\n", pfd->name);
    printf("nb_components   : %d\n", pfd->nb_components);
    printf("log2_chroma_w   : %d\n", pfd->log2_chroma_w);
    printf("log2_chroma_h   : %d\n", pfd->log2_chroma_h);
    printf("flags           : %d\n", pfd->flags);
    printf("alias           : %s\n", pfd->alias);

    int i = 0;
    for (; i < pfd->nb_components; i++) {

        printf("comp[%d]         :   \n", i);

        printf("plane : %d, step : %d, offset : %d, shift : %d, depth : %d\n",
                pfd->comp[i].plane, pfd->comp[i].step, pfd->comp[i].offset, pfd->comp[i].shift, pfd->comp[i].depth);
    }

    printf("-------------------------------------------------------\n");
}

int main() {

    const AVPixFmtDescriptor *pfd = av_pix_fmt_desc_get(AV_PIX_FMT_YUV420P);
    print_fmt_descs(pfd);

    while((pfd = av_pix_fmt_desc_next(pfd))) {
        print_fmt_descs(pfd);
    }

    return 0;
}
