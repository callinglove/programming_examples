## vim插件目录简介

- ~/.vim/colors/是用来存放vim配色方案的。

- ~/.vim/plugin/存放的是每次启动vim都会被运行一次的插件，也就是说只要你想在vim启动时就运行的插件就放在这个目录下。

- ~/.vim/ftdetect/中的文件同样也会在vim启动时就运行。有些时候可能没有这个目录。ftdetect代表的是“filetype detection（文件类型检测）”。此目录中的文件应该用自动命令（autocommands）来检测和设置文件的类型，除此之外并无其他。也就是说，它们只该有一两行而已。

- ~/.vim/ftplugin/此目录中的文件有些不同。当vim给缓冲区的filetype设置一个值时，vim将会在~/.vim/ftplugin/ 目录下来查找和filetype相同名字的文件。例如你运行set filetype=derp这条命令后，vim将查找~/.vim/ftplugin/derp.vim此文件，如果存在就运行它。不仅如此，它还会运行ftplugin下相同名字的子目录中的所有文件，如~/.vim/ftplugin/derp/这个文件夹下的文件都会被运行。每次启用时，应该为不同的文件类型设置局部缓冲选项，如果设置为全局缓冲选项的话，将会覆盖所有打开的缓冲区。

- ~/.vim/indent/这里面的文件和ftplugin中的很像，它们也是根据它们的名字来加载的。它放置了相关文件类型的缩进。例如python应该怎么缩进，java应该怎么缩进等等。其实放在ftplugin中也可以，但单独列出来只是为了方便文件管理和理解。

- ~/.vim/compiler/和indent很像，它放的是相应文件类型应该如何编译的选项。

- ~/.vim/after/这里面的文件也会在vim每次启动的时候加载，不过是等待~/.vim/plugin/加载完成之后才加载after里的内容，所以叫做after。

- ~/.vim/autoload/它是一个非常重要的目录，尽管听起来比实际复杂。简而言之，它里面放置的是当你真正需要的时候才被自动加载运行的文件，而不是在vim启动时就加载。

- ~/.vim/doc/为插件放置文档的地方。例如:help的时候可以用到。

- ~/.vim/spell/拼写检查脚本。

- ~/.vim/syntax/语法描述脚本。


## Vundle

https://github.com/VundleVim/Vundle.vim

vim插件管理工具

### 安装配置使用

`git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim`

.vimrc文件配置
```
set nocompatible              " 去除VI一致性,必须
filetype off                  " 必须

" 设置包括vundle和初始化相关的runtime path
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" 另一种选择, 指定一个vundle安装插件的路径
"call vundle#begin('~/some/path/here')

" 让vundle管理插件版本,必须
Plugin 'VundleVim/Vundle.vim'

" 以下范例用来支持不同格式的插件安装.
" 请将安装插件的命令放在vundle#begin和vundle#end之间.
" Github上的插件
" 格式为 Plugin '用户名/插件仓库名'
Plugin 'tpope/vim-fugitive'
" 来自 http://vim-scripts.org/vim/scripts.html 的插件
" Plugin '插件名称' 实际上是 Plugin 'vim-scripts/插件仓库名' 只是此处的用户名可以省略
Plugin 'L9'
" 由Git支持但不再github上的插件仓库 Plugin 'git clone 后面的地址'
Plugin 'git://git.wincent.com/command-t.git'
" 本地的Git仓库(例如自己的插件) Plugin 'file:///+本地插件仓库绝对路径'
Plugin 'file:///home/gmarik/path/to/plugin'
" 插件在仓库的子目录中.
" 正确指定路径用以设置runtimepath. 以下范例插件在sparkup/vim目录下
Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
" 安装L9，如果已经安装过这个插件，可利用以下格式避免命名冲突
Plugin 'ascenator/L9', {'name': 'newL9'}

" 你的所有插件需要在下面这行之前
call vundle#end()            " 必须
filetype plugin indent on    " 必须 加载vim自带和插件相应的语法和文件类型相关脚本
" 忽视插件改变缩进,可以使用以下替代:
"filetype plugin on
"
" 简要帮助文档
" :PluginList       - 列出所有已配置的插件
" :PluginInstall    - 安装插件,追加 `!` 用以更新或使用 :PluginUpdate
" :PluginSearch foo - 搜索 foo ; 追加 `!` 清除本地缓存
" :PluginClean      - 清除未使用插件,需要确认; 追加 `!` 自动批准移除未使用插件
"
" 查阅 :h vundle 获取更多细节和wiki以及FAQ
" 将你自己对非插件片段放在这行之后
```

## NERD tree

https://github.com/scrooloose/nerdtree

- :NERDTree  打开新的目录树。可以提供一个路径参数，那么命令将打开以该路径作为根目录的目录树。如果没有路径参数提供，那么当前目录将作为新的目录树的根目录。
- :NERDTreeToggle 如果当前标签已经存在目录树，该命令会重新刷新目录树显示；如果当前标签不存在目录树，该命令作用效果与:NERDTree命令一致。
- :NERDTreeClose 关闭当前标签的目录树。

F2绑定快捷键，将其映射到:NERDTreeToggle命令：
```
" 绑定F2到NERDTreeToggle
map <F2> :NERDTreeToggle<CR>
```


### 文件节点映射（File node mappings）

- 左键双击 or 回车 or o : 打开指定文件。
- go : 打开指定文件，将光标留在目录树中。
- t  : 在新标签中打开文件。
- T  : 在新标签中打开文件，保持鼠标焦点留在当前标签。
- 鼠标中键 or i : 在水平分屏窗口中打开指定文件。
- gi : 在水平分屏窗口中打开指定文件，将光标留在目录树中。
- s : 在垂直分屏窗口中打开指定文件。
- gs : 在垂直分屏窗口中打开指定文件，将光标留在目录树中。

### 目录节点映射（Directory node mappings）

- 左键双击 or 回车 or o : 打开指定目录。
- O : 递归打开指定目录。
- x : 关闭当前节点的父节点。
- X : 递归关闭当前节点的所有子节点。
- 鼠标中键 or e : 浏览指定目录。

### 书签表映射（Bookmark table mappings）

- 左键双击 or 回车 or o : 打开指定书签。
- t : 在新标签中打开书签。
- T : 在新标签中打开书签，保持鼠标焦点留在当前标签。
- D : 删除指定书签。

### 树形导航映射（Tree navigation mappings）

- p : 跳转到根节点。
- P : 跳转到当前节点的父节点。
- K : 跳转到当前目录的第一个子节点。
- J : 跳转到当前目录的最后一个子节点。
- Ctrl + K : 跳转到当前节点的上一个兄弟节点。
- Ctrl + J : 跳转到当前节点的下一个兄弟节点。

### 文件系统映射（Filesystem mappings）

- C : 将当前选择的目录做为树形目录的根节点，即切换当前根目录节点为选择的目录节点。
- u : 将当前视图中的树根节点上移一层目录，即拿当前树根目录的父目录做为新的根目录。
- U : 将当前视图中的树根节点上移一层目录，即拿当前树根目录的父目录做为新的根目录，并且保持原树目录状态不变。
- r : 递归刷新当前目录。
- R : 递归刷新当前节点。
- m :  显示菜单。
- cd : 将CWD切换到当前选择节点的目录。

### 树形过滤器映射（Tree filtering mappings）

- I : 是否显示隐藏文件开关。
- f : 是否启用文件过滤器开关。
- F : 是否显示文件开关。
- B : 是否显示书签表的开关。

### 树形过滤器映射（Tree filtering mappings）

- q : 关闭树形目录树窗口。
- A : 缩放树形目录树窗口。
- ? : 显示帮助文档的开关。

## taglist 插件

ctags简单应用

- Ctrl + ] 跳转到变量或函数的定义处，或者用命令
- :ta name 而使用快捷组合键
- Ctrl + o/t 返回到跳转前的位置。

## tagbar 插件

- :TagbarToggle 窗口显示
- 跳转
    - <CR>: 回车跳到定义位置
    - p: 跳到定义位置，但光标仍然在tagbar原位置
    - P: 打开一个预览窗口显示标签内容，如果在标签处回车跳到vim编辑页面内定义处，则预览窗口关闭
    - <C-N>: 跳到下一个标签页的顶端
    - <C-P>: 跳到上一个（或当前）标签页的顶端
    - <Space>: 底行显示标签原型

- 折叠: 提供与vim内建映射一样的操作
    - \+ 展开标签内容
    - \-  折叠标签内容
    - \*  展开所有标签
    - \= 折叠所有标签
    - o 在折叠与展开间切换，按o键，折叠标签，再按一次o，则展开标签，如此来回切换
- Misc
    - s: 切换排序，一次s，则让标签按字典排序，再一次s，则按照文件内出现顺序排序
    - x: 是否展开tagbar标签栏，x展开，再一次x，则缩小标签栏
    - <F1>: 切换快捷键帮助页面，F1一次出现快捷键帮助页面，在一次F1，快捷键帮助页面隐藏。

## clang_complete

This plugin uses clang for accurately completing C and C++ code

- 依赖
    - vim 7.3+
    - `yum install -y clang`
    - 与OmniCppComplete 冲突
- 安装方式
    - 在[官网插件列表](http://www.vim.org/scripts/script.php?script_id=3302)下载`clang_complete.vmb`文件
    - 在[作者github](https://github.com/xavierd/clang_complete)上clone
        - `make` 生成`clang_complete.vmb`文件
        - `make install` 安装插件，或者直接命令行`vim -c 'RmVimball clang_complete.vmb' -c 'q'`进行安装
- 说明文档 `doc/clang_complete.txt`
- 配置实例
    ```
    " clang complete
    " 自动选择第一个匹配项但不插入到代码中
    let g:clang_auto_select = 1
    " 在->. ., ::后自动补全
    let g:clang_complete_auto = 1
    " 发现错误之后打开QuickFix窗口
    let g:clang_complete_copen = 1
    "高亮警告和错误
    let g:clang_hl_errors = 1
    " 插入第一个补全后关闭预览窗口
    let g:clang_close_preview = 1
    " 开启对C++11的编译支持
    let g:clang_user_options = '-std=c++11'
    " 设定clang库路径
    let g:clang_library_path = '/usr/lib64/llvm/libclang.so'
    " 补全预处理指令，宏和常数，默认为0，不补全
    let g:clang_complete_macros = 1
    " 补全代码模式，比如循环等，默认为0，不补全
    let g:clang_complete_patterns = 1
    " <C-]>跳转到声明
    let g:clang_jumpto_declaration_key = "<C-]>"
    " <C-w>]在预览窗口中打开声明
    let g:clang_jumpto_declaration_in_preview_key = "<C-w>]"
    " <C-t>回跳
    let g:clang_jumpto_back_key = "<C-t>"
    " 使用UltiSnips进行代码片段补全
    let g:clang_snippets = 1
    let g:clang_snippets_engine = 'ultisnips'
    ```
- 编译选项文件`.clang_complete`
    ```
    -DDEBUG
    -include ../config.h
    -I../common
    `pkg-config gtk+-2.0 --cflags`
    ```

## auto-pairs 插件

https://github.com/jiangmiao/auto-pairs

## YouCompleteMe 插件

参考:
- [YouCompleteMe 中容易忽略的配置](https://zhuanlan.zhihu.com/p/33046090)

帮助文档 ~/.vim/bundle/YouCompleteMe/doc/youcompleteme.txt 或者 :help youcompleteme

Bug: 跳转函数不尽如意，决定使用ctags

全局.ycm_extra_conf.py中加入系统头文件路径，如
```
flags = [
    ...
    'isystem', '/usr/include',
    'isystem', '/usr/include/c++/4.8.5',
    ...
]
```
本地.ycm_extra_conf.py中加入工程头文件路径，如
```
flags = [
    ...
    '-I', '/usr/local/opencv3.1.0/include',
    '-I', '/usr/local/mysql/include',
    ...
]
```

YCM提供的跳跃功能采用了vim的jumplist，往前跳和往后跳的快捷键为Ctrl+O以及Ctrl+I


## YCM-Generator 插件

用以生成YCM需要的本地.ycm_extra_conf.py配置文件

~/.vim/bundle/YCM-Generator/config_gen.py --help


buffers操作

- :ls
- :badd file.txt
- :bd 2
- :1b

window操作

- 切换 Ctrl + w + h/j/k/l（向左、下、上、右切换）或者Ctrl + w + w（在窗口间切换）
- 如果是水平分隔可以使用:nwinc +/-把当前激活窗口高度增加、减少n个字符高度，比如:10winc + 
- 如果是垂直分隔可以使用:nwinc >/<把当前激活窗口宽度增加、减少n个字符宽度，比如:5winc >

tab操作

- :tabe file.txt
- :tabs tab列表
- :ngt 切换到对应的tab，n是tab的编号
- gt  后一个tab
- gT  前一个tab
- :tabc