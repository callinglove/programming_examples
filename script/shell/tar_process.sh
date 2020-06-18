#!/bin/bash
#
# 带有进度的解/打包
#
# document: http://www.gnu.org/software/tar/manual/html_section/tar_26.html#checkpoints
#
## gzip -l vopsAll.tar.gz 
#         compressed        uncompressed  ratio uncompressed_name
#         2802583640          2812241920   0.3% vopsAll.tar
#
## xz --robot -l vopsAll.tar.xz
#name	vopsAll.tar.xz
#file	1	1	2679853216	2693939200	0.995	CRC64	0
#totals	1	1	2679853216	2693939200	0.995	CRC64	0
#
#  -b, --blocking-factor=BLOCKS   BLOCKS x 512 bytes per record
#     --checkpoint[=NUMBER]  display progress messages every NUMBERth record
#                            (default 10)
#     --checkpoint-action=ACTION   execute ACTION on each checkpoint


# file to decompress, directory
function tar_decompress() {
    local total_size=51200
    local tar_file=$1
    local tar_dir=./
    if [[ $# -eq 2 ]]; then
        tar_dir=$2
    fi

    if [[ "${tar_file}" == *.tar.gz ]]; then
        total_size=$(gzip -l "${tar_file}" | tail -1 | awk '{print $2}')
    elif [[ "${tar_file}" == *.tar.xz ]]; then
        total_size=$(xz --robot -l "${tar_file}" | tail -1 | awk '{print $5}')
    fi

    local blocking_factor=$((total_size/512/100+1))
    local checkpoint=1

    tar --blocking-factor=$blocking_factor --checkpoint=1 --checkpoint-action="ttyout=unpack ${tar_file##*/} %u%    \r" -xpf $tar_file -C $tar_dir
    echo "decompress ${tar_file##*/} complete"
}

function tar_compress() {
tar -xpf vopsAll.tar.gz --blocking-factor=10 --checkpoint=100 --checkpoint-action=dot --totals
}

tar_decompress vopsAll.tar.gz