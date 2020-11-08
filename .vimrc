"
" vim-plug
"
set nocompatible
filetype plugin on
syntax on
set encoding=utf8

" Download vim-plug if missing
if empty(glob('~/.vim/autoload/plug.vim'))
  silent! execute '!curl --create-dirs -fsSLo ~/.vim/autoload/plug.vim https://raw.github.com/junegunn/vim-plug/master/plug.vim'
  autocmd VimEnter * silent! PlugInstall
endif

call plug#begin('~/.vim/plugged')

" Gruvbox
Plug 'morhetz/gruvbox'

call plug#end()

"
" Settings
"

" Lines
set number
set ruler

" Text wrap
set wrap
set linebreak
set breakindent
set breakindentopt=shift:2,min:40,sbr
set showbreak=⤥

" Tabulation
filetype plugin indent on
set tabstop=4
set shiftwidth=4
set softtabstop=4
set smarttab
set expandtab

" Search
set incsearch
set hlsearch
set ignorecase
set smartcase

" Status line
set showcmd
set ch=1
set wildmenu
set wcm=<TAB>

" Mouse
set mousehide
set mouse=a

" Buffers
set hidden
set autoread

" Make backspace work like in most other apps
set backspace=2

" Paste toggle
set pastetoggle=<F2>

" Use system clipboard
set clipboard=unnamedplus

" Russian keymap
if has('mac')
  set keymap=russian-jcukenmac
else
  set keymap=russian-jcukenwin
endif
set iminsert=0
set imsearch=0

" Colorscheme
set background=dark
let g:gruvbox_italic=0
colorscheme gruvbox

" Update time
set updatetime=300

" Always show sign column
set signcolumn=yes

" Disable 'Pattern not found' messages
set shortmess+=c

" Render tabs and spaces
set listchars=space:•,tab:-->
set list

"
" Plugin Settings
"
" Jump visual lines, not physical
nnoremap k gk
nnoremap j gj
nnoremap gk k
nnoremap gj j
nnoremap 0 g0
nnoremap $ g$

" Disable arrow movement, resize splits instead.
nnoremap <silent> <M-Up> :resize +2<CR>
nnoremap <silent> <M-Down> :resize -2<CR>
nnoremap <silent> <M-Left> :vertical resize +2<CR>
nnoremap <silent> <M-Right> :vertical resize -2<CR>

" Remove trailing whitespace
nnoremap <silent> <Leader>w :let _save_pos=getpos('.') <Bar>
    \ :let _s=@/ <Bar>
    \ :%s/\s\+$//e <Bar>
    \ :let @/=_s <Bar>
    \ :nohl <Bar>
    \ :unlet _s<Bar>
    \ :call setpos('.', _save_pos)<Bar>
    \ :unlet _save_pos<CR><CR>

"
" Commands
"

" Saving files with root priveledges without opening vim as root.
command! W :execute ':silent w !sudo tee % > /dev/null' | :edit!
