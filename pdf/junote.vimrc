
syntax enable

" setup vim-plug first
"curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
"    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim

"leader
let mapleader = ','
let g:mapleader = ','

call plug#begin()
"  Plug 'Shougo/deoplete.nvim'
"  Plug 'roxma/nvim-yarp'
"  Plug 'roxma/vim-hug-neovim-rpc'

"view
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'tomasr/molokai'

"nav
Plug 'scrooloose/nerdtree'
Plug 'bling/vim-bufferline'
Plug 'majutsushi/tagbar'


"autocomplete
Plug  'Raimondi/delimitMate'

"commenter
Plug 'scrooloose/nerdcommenter'

"easymotion
Plug 'Lokaltog/vim-easymotion'

"tmux
Plug 'edkolev/tmuxline.vim'

"gtags
Plug 'aceofall/gtags.vim'


call plug#end()

"deoplete
"let g:deoplete#enable_at_startup = 1



" airline
let g:airline_theme = 'molokai'
let g:airline_powerline_fonts=1
if !exists('g:airline_symbols')
        let g:airline_symbols = {}
endif
let g:airline_left_sep = '▶'
let g:airline_left_alt_sep = '❯'
let g:airline_right_sep = '◀'
let g:airline_right_alt_sep = '❮'
let g:airline_symbols.linenr = '¶'
let g:airline_symbols.branch = '⎇'
" tabline?
let g:airline#extensions#tabline#enabled = 1

"molokai
let g:molokai_original = 1
let g:rehash256 = 1

"tmux

"clang lib, setup libclang-dev clang,clang-complete
let g:clang_library_path='/usr/lib/llvm-3.8/lib'

"nerdtree
nmap <leader>n :NERDTreeToggle<CR>

"tagbar
nmap <leader>t :Tagbar<CR>

"gtags
nmap <leader>gd :GtagsCursor<CR>
nmap <leader>gu :GtagsUpdate<CR>




" ensure ftdetect et al work by including this after the bundle stuff
filetype plugin indent on

set background=dark
set t_Co=256



filetype on
filetype indent on
filetype plugin on
filetype plugin indent on

set autoread
set wildignore=*.swp,*.bak,*.pyc,*.class,.svn
"set cursorcolumn
set cursorline

set scrolloff=7
set number
set nowrap
set showmatch
set matchtime=2

set hlsearch
set incsearch
set ignorecase
set smartcase

set smartindent
set autoindent

set tabstop=4
set shiftwidth=4
set softtabstop=4
set smarttab
set expandtab
set shiftround

map <C-j> <C-W>j
map <C-k> <C-W>k
map <C-h> <C-W>h
map <C-l> <C-W>l

"remove highlignt
noremap <silent><leader>/ :nohls<CR>

"tab
map <leader>tn :tabnext<cr>
map <leader>tp :tabprev<cr>
nnoremap <C-t>     :tabnew<CR>
inoremap <C-t>     <Esc>:tabnew<CR>

"buffer
map <leader>bn :bn<cr>
map <leader>bp :bp<cr>

"copy to clip
vnoremap <leader>y "+y
nmap <Leader>p "+p


"tags
"set tags=./tags;

"quickfix
nmap <Leader>qo :copen<CR>
nmap <Leader>qc :cclose<CR>

