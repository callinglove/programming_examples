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
my_raw_url="https://raw.staticdn.net/callinglove/programming_examples/master/script/shell/vim_config"

function pre_install_dependencies() {
    # curl raw下载依赖curl
    command curl --version &>/dev/null || yum install -y curl

    # git vim-plug依赖git
    command git --version &>/dev/null || yum install -y git

    # ctags taglist依赖ctags
    command ctags --version &>/dev/null || yum install -y ctags

    # cmake vim-cmake依赖cmake
    command cmake --version &>/dev/null || yum install -y cmake

    # clang vim-clang依赖clang
    command clang --version &>/dev/null || yum install -y clang
}

function install_config() {
    # vimrc配置文件
    curl -kfLo ~/.vim/vimrc --create-dirs "${my_raw_url}/vimrc"
    curl -kfLo ~/.vim/vimrc.plug.cn --create-dirs "${my_raw_url}/vimrc.plug.cn"
    curl -kfLo ~/.vim/vimrc.plug.settings --create-dirs "${my_raw_url}/vimrc.plug.settings"

    # vim-plug插件
    curl -kfLo ~/.vim/autoload/plug.vim --create-dirs https://raw.staticdn.net/junegunn/vim-plug/master/plug.vim
    
    # corporation主题
    curl -kfLo ~/.vim/colors/corporation.vim --create-dirs "${my_raw_url}/colors/corporation.vim"

    # vim-cmake插件
    curl -kfLo ~/.vim/plugged/vim-cmake/plugin/cmake.vim --create-dirs "${my_raw_url}/plugged/vim-cmake/plugin/cmake.vim"
    curl -kfLo ~/.vim/plugged/vim-cmake/doc/cmake.txt --create-dirs "${my_raw_url}/plugged/vim-cmake/doc/cmake.txt"
    curl -kfLo ~/.vim/plugged/vim-cmake/doc/tags --create-dirs "${my_raw_url}/plugged/vim-cmake/doc/tags"
}

function pre_install_Vundle() {
    ## vim插件管理Vundle
    git clone ${vundle_git_url} ~/.vim/bundle/Vundle.vim
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
    # 安装依赖
    pre_install_dependencies
    # 从git上下载配置以及预装插件
    install_config
    # 通过vim-plug下载插件
    vim +PlugInstall +qall
    
    ## 安装插件
    #vim +PluginInstall +qall
    #
    ## compile YCM
    #cd ~/.vim/bundle/YouCompleteMe
    #./install.py --clang-completer
}

main

