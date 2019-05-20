:set number             " 显示行号
:set nolist
":set list               " 显示Tab和换行符^I和$显示
:set cursorline         "设置光标所在行的行识线 boolean (default off)
:set hlsearch           " 启用高亮搜索 boolean (default off)
:syntax on              " 启用语法高亮


" ================================Vundle config===============================
set nocompatible
filetype off

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

" 插件管理工具
Plugin 'VundleVim/Vundle.vim'

" 目录树插件
Plugin 'scrooloose/nerdtree'

" 函数列表插件
Plugin 'taglist.vim'

" 自动补全提示插件
Plugin 'Valloric/YouCompleteMe'

call vundle#end()
filetype plugin indent on


" =============================nerdtree config ===============================
"NERDTree 配置:F2快捷键显示当前目录树
map <F2> :NERDTreeToggle<CR>

let NERDTreeWinSize=25


" =============================taglist config ================================
map <F3> :TlistToggle<CR>

" 如果ctags不在Path路径下,则配置ctags的路径
let Tlist_Ctags_Cmd = '/usr/bin/ctags'


let Tlist_Show_One_File = 1         "不同时显示多个文件的tag，只显示当前文件的
let Tlist_Exit_OnlyWindow = 1       "如果taglist窗口是最后一个窗口，则退出vim
let Tlist_Use_Right_Window = 1      "在右侧窗口中显示taglist窗口
"let Tlist_Sort_Type = "name"        "taglist以tag名字进行排序，缺省是按tag在文件中出现的顺序进行排序
let Tlist_Use_SingleClick = 1       "设置单击tag就跳转到定义处, 缺省双击
"let Tlist_Auto_Open=1               "启动vim自动打开taglist窗口
let Tlist_Close_On_Select=1         "在选择了tag后自动关闭taglist窗口
let Tlist_File_Fold_Auto_Close=1   "当同时显示多个文件中的tag时,可使taglist只显示当前文件tag，其它文件的tag都被折叠起来。
let Tlist_GainFocus_On_ToggleOpen=1 "在使用:TlistToggle打开taglist窗口时,输入焦点在taglist窗口中
let Tlist_Process_File_Always=1     "taglist始终解析文件中的tag，不管taglist窗口有没有打开
let Tlist_Use_Horiz_Window = 1      "设置taglist窗口横向显示
" Tlist_WinHeight和Tlist_WinWidth可以设置taglist窗口的高度和宽度


" ===========================YouCompleteMe config=============================
" 全局配置文件路径
let g:ycm_global_ycm_extra_conf='~/.vim/bundle/YouCompleteMe/third_party/ycmd/.ycm_extra_conf.py'
" 语法关键词补全
let g:ycm_seed_identifiers_with_syntax=1
" 询问是否加载ycm_extra_conf.py配置
let g:ycm_confirm_extra_conf=0
let g:ycm_key_invoke_completion = '<C-Space>'


" ==========================新建文件添加文件标题===============================
autocmd BufNewFile *.sh,*.py,*.c,*.h,*.cpp exec ":call SetFileHeaderComment()"

func s:SetCommentLine(pre, comment)
    normal o
    call setline(line("."), a:pre.a:comment)
endfunc

func s:SetCommonComment(pre)
    call s:SetCommentLine(a:pre, " ")
    call s:SetCommentLine(a:pre, "      FileName: ".expand("%"))
    call s:SetCommentLine(a:pre, " ")
    call s:SetCommentLine(a:pre, "        Author: ")
    call s:SetCommentLine(a:pre, "   Description: ---")
    call s:SetCommentLine(a:pre, "  Created Time: ".strftime("%c"))
    call s:SetCommentLine(a:pre, " Last Modified: ".strftime("%Y-%m-%d %H:%M:%S"))
    call s:SetCommentLine(a:pre, " ")
endfunc

func SetFileHeaderComment()
    if expand("%:e") == "sh"
        call setline(line("."), "\#/bin/bash")
        call s:SetCommonComment("\#")
    elseif expand("%:e") == "py"
        call setline(line("."), "\#!/usr/bin/env python")
        call s:SetCommentLine("\#", " -*- coding: utf-8 -*-")
        call s:SetCommonComment("\#")
    elseif expand("%:e") == "c" || expand("%:e") == "cpp"
        call setline(line("."), "/*")
        call s:SetCommonComment(" *")
        call s:SetCommentLine(" *", "/")
    elseif expand("%:e") == "h"
        let h_macro = "__".toupper(expand("%:r"))."_H_INCLUDED"
        call setline(line("."), "#ifndef ".h_macro)
        call s:SetCommentLine("", "#define ".h_macro)
        call s:SetCommentLine("", "#endif   /* ".h_macro." */")
        call cursor(2, len(getline(2)))
        normal o
        normal O
        normal O
    endif
    normal o
endfunc
