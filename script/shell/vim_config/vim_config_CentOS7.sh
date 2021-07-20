#!/bin/bash

###################################################
#
# @email        444541307@qq.com
# @blog         https://blog.csdn.net/callinglove
# @github       https://github.com/callinglove
#
# 本脚本用于CentOS7环境下vim配置,实现一个命令完成配置
#
# wget https://raw.githubusercontent.com/callinglove/programming_examples/master/shell/vim_config/vim_config_CentOS7.sh -O - | bash
#
###################################################

vundle_git_url="https://github.com/VundleVim/Vundle.vim.git"
gf_repo_rpm_url="http://mirror.ghettoforge.org/distributions/gf/gf-release-latest.gf.el7.noarch.rpm"


function pre_install_Vundle() {

    ## 安装git
    command git --help &>/dev/null || yum install -y git

    ## vim插件管理Vundle
    git clone ${vundle_git_url} ~/.vim/bundle/Vundle.vim
}

function pre_install_taglist() {
    # taglist依赖ctags
    ## 安装git
    if ! command ctags --help &>/dev/null
    then
        yum install -y ctags
    fi
}

# YouCompleteMe的安装对vim与cmake版本有要求
function pre_install_YouCompleteMe() {

    # 通过gf升级vim与cmake

    ## 配置gf源
    rpm -Uvh ${gf_repo_rpm_url}
    rpm --import http://mirror.ghettoforge.org/distributions/gf/RPM-GPG-KEY-gf.el7
    ## 卸载原有的vim
    yum remove -y vim-minimal vim-common vim-enhanced
    ## 使用gf源安装最新版vim
    yum install -y --enablerepo=gf-plus vim-enhanced

    ## 升级cmake
    ### 添加epel-release源，安装jsoncpp
    yum install -y epel-release
    ### 安装jsoncpp，cmake依赖
    yum install jsoncpp
    ### fg源安装最新版本cmake
    yum install -y --enablerepo=gf-plus cmake

    yum install python-devel
}

function main() {
    pre_install_Vundle
    pre_install_taglist
    pre_install_YouCompleteMe

    # 备份~/.vimrc
    [[ -z "~/.vimrc" ]] && mv ~/.vimrc{,_bk}
    wget https://raw.githubusercontent.com/callinglove/programming_examples/master/shell/vim_config/.vimrc -O ~/.vimrc
    
    # 安装插件
    vim +PluginInstall +qall

    # compile YCM
    cd ~/.vim/bundle/YouCompleteMe
    ./install.py --clang-completer
}

main

