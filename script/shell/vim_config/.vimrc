:set number             " 显示行号
:set nolist
":set list               " 显示Tab和换行符^I和$显示
:set cursorline         "设置光标所在行的行识线 boolean (default off)
:set hlsearch           " 启用高亮搜索 boolean (default off)
:syntax on              " 启用语法高亮

set tabstop=4       " 设定tab长度为4
set softtabstop=4   " 使得按退格键时可以一次删掉 4 个空格
set shiftwidth=4    " 设定 << 和 >> 命令移动时的宽度为 4
set expandtab       " 将tab键替换成空格

" python代码缩进PEP8风格
au BufNewFile,BufRead *.py,*pyw
  \ set tabstop=4 |
  \ set softtabstop=4 |
  \ set shiftwidth=4 |
  \ set textwidth=79 |
  \ set expandtab |
  \ set autoindent |
  \ set fileformat=unix


" ================================Vundle config===============================
set nocompatible
filetype off

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

" 插件管理工具
Plugin 'VundleVim/Vundle.vim'

" 状态行增强插件
Plugin 'vim-airline/vim-airline'

" 目录树插件
Plugin 'scrooloose/nerdtree'

" 函数列表插件 displays the tags of the current file in a sidebar
Plugin 'taglist.vim'
Plugin 'majutsushi/tagbar'

" 自动匹配括号、引号等插件
Plugin 'jiangmiao/auto-pairs'

" 自动补全提示插件
Plugin 'Valloric/YouCompleteMe'
Plugin 'rdnetto/YCM-Generator', { 'branch': 'stable'}

call vundle#end()
filetype plugin indent on


" ===========================vim-airline config ==============================
let g:airline#extensions#tabline#enabled = 1

set laststatus=2 "1为关闭底部状态栏 2为开启"
set t_Co=256     "终端开启256色支持"

if !exists('g:airline_symbols')
    let g:airline_symbols = {}
endif

" powerline symbols
let g:airline_left_sep = ''
let g:airline_left_alt_sep = ''
let g:airline_right_sep = ''
let g:airline_right_alt_sep = ''
let g:airline_symbols.branch = ''
let g:airline_symbols.readonly = ''
let g:airline_symbols.linenr = '☰'
let g:airline_symbols.maxlinenr = ''
let g:airline_symbols.dirty='⚡'


" =============================nerdtree config ===============================
"NERDTree 配置:F2快捷键显示当前目录树
map <F2> :NERDTreeToggle<CR>

let NERDTreeWinSize=25
" ignore files in NERDTree
let NERDTreeIgnore=['\.pyc$', '\~$']


" =============================taglist config ================================
map <F3> :TlistToggle<CR>

" 如果ctags不在Path路径下,则配置ctags的路径
let Tlist_Ctags_Cmd = '/usr/bin/ctags'

let Tlist_Show_One_File = 1         "不同时显示多个文件的tag，只显示当前文件的
let Tlist_Exit_OnlyWindow = 1       "如果taglist窗口是最后一个窗口，则退出vim
let Tlist_Use_Right_Window = 0      "在左侧窗口中显示taglist窗口
"let Tlist_Sort_Type = "name"        "taglist以tag名字进行排序，缺省是按tag在文件中出现的顺序进行排序
let Tlist_Use_SingleClick = 1       "设置单击tag就跳转到定义处, 缺省双击
"let Tlist_Auto_Open=1               "启动vim自动打开taglist窗口
let Tlist_Close_On_Select=1         "在选择了tag后自动关闭taglist窗口
let Tlist_File_Fold_Auto_Close=1   "当同时显示多个文件中的tag时,可使taglist只显示当前文件tag，其它文件的tag都被折叠起来。
let Tlist_GainFocus_On_ToggleOpen=1 "在使用:TlistToggle打开taglist窗口时,输入焦点在taglist窗口中
let Tlist_Process_File_Always=1     "taglist始终解析文件中的tag，不管taglist窗口有没有打开
let Tlist_Use_Horiz_Window = 0      "设置taglist窗口纵向显示
" Tlist_WinHeight和Tlist_WinWidth可以设置taglist窗口的高度和宽度


" ================================tagbar config===============================
" 将开启tagbar的快捷键设置为　<Leader>tb
nmap <Leader>tb :TagbarToggle<CR>
" 这是tagbar一打开，光标即在tagbar页面内，默认在vim打开的文件内
let g:tagbar_autofocus = 1
" 设置标签不排序，默认排序
let g:tagbar_sort = 0

" 设置ctags所在路径
let g:tagbar_ctags_bin='/usr/bin/ctags'
" 让tagbar在页面左侧显示，默认右边
"let g:tagbar_left = 1
" 设置tagbar的宽度
let g:tagbar_width=30
" 在某些情况下自动打开tagbar
"autocmd BufReadPost *.cpp,*.c,*.h,*.hpp,*.cc,*.cxx call tagbar#autoopen()


" ===========================YouCompleteMe config=============================
" Python Semantic Completion
" let g:ycm_python_binary_path = '/usr/bin/python3'

" 全局配置文件路径
let g:ycm_global_ycm_extra_conf='~/.vim/bundle/YouCompleteMe/third_party/ycmd/.ycm_extra_conf.py'
" 询问是否加载当前目录.ycm_extra_conf.py配置
let g:ycm_confirm_extra_conf=0
" 语法关键词补全
let g:ycm_seed_identifiers_with_syntax=1
" 开启 YCM 基于标签引擎
let g:ycm_collect_identifiers_from_tags_files = 1
" 注释和字符串中的文字也会被收入补全
let g:ycm_collect_identifiers_from_comments_and_strings = 0
" 从第2个键入字符就开始罗列匹配项
let g:ycm_min_num_of_chars_for_completion=2
" 在注释输入中也能补全
let g:ycm_complete_in_comments = 1
" 在字符串输入中也能补全
let g:ycm_complete_in_strings = 1
" 弹出列表时选择第1项的快捷键(默认为<TAB>和<Down>)
let g:ycm_key_list_select_completion = ['<C-n>', '<Down>']
" 弹出列表时选择前1项的快捷键(默认为<S-TAB>和<UP>)
let g:ycm_key_list_previous_completion = ['<C-p>', '<Up>']
" 主动补全, 默认为<C-Space>
let g:ycm_key_invoke_completion = '<c-z>'
" 自动补全触发条件
let g:ycm_semantic_triggers =  {
\   'c,cpp,python,java,go,erlang,perl':['re!\w{2}'],
\   'cs,lua,javascript':['re!\w{2}'],
\}
" 停止显示补全列表(防止列表影响视野), 可以按<C-Space>重新弹出
"let g:ycm_key_list_stop_completion = ['<C-y>']

" preview window to auto-close after you select a completion string
"let g:ycm_autoclose_preview_window_after_completion=1
" to close the preview window after leaving insert mode
let g:ycm_autoclose_preview_window_after_insertion=1

" 错误标记
let g:ycm_error_symbol = '✗'
" 警告标记
let g:ycm_warning_symbol = '⚠'
" YcmErrorSign
" YcmWarningSign
" YcmErrorLine
" YcmWarningLine
highlight YcmErrorSection term=italic ctermbg=Grey cterm=bold
highlight YcmWarningSection term=italic ctermbg=Grey cterm=bold

nnoremap <leader>gl :YcmCompleter GoToDeclaration<CR>
nnoremap <leader>gf :YcmCompleter GoToDefinition<CR>
nnoremap <leader>gg :YcmCompleter GoToDefinitionElseDeclaration<CR>
nmap <F4> :YcmDiags<CR>


" ==========================新建文件添加文件标题===============================
autocmd BufNewFile *.sh,*.py,*.c,*.h,*.cpp exec ":call SetFileHeaderComment()"

func s:SetCommentLine(pre, comment)
    normal o
    call setline(line("."), a:pre.a:comment)
endfunc

func s:SetCommonComment(pre)
    call s:SetCommentLine(a:pre, " @file        : ".expand("%"))
    call s:SetCommentLine(a:pre, " @author      : ")
    call s:SetCommentLine(a:pre, " @date        : ".strftime("%c"))
    " call s:SetCommentLine(a:pre, " Last Modified: ".strftime("%Y-%m-%d %H:%M:%S"))
    call s:SetCommentLine(a:pre, " @remark ")
    call s:SetCommentLine(a:pre, " @note ")
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
