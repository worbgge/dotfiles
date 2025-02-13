"          ██                       ████
"         ░░                       ░██░   █████
" ██    ██ ██ ██████████   █████  ██████ ██░░░██
"░██   ░██░██░░██░░██░░██ ██░░░██░░░██░ ░██  ░██
"░░██ ░██ ░██ ░██ ░██ ░██░██  ░░   ░██  ░░██████
" ░░████  ░██ ░██ ░██ ░██░██   ██  ░██   ░░░░░██
"  ░░██   ░██ ███ ░██ ░██░░█████   ░██    █████
"   ░░    ░░ ░░░  ░░  ░░  ░░░░░    ░░    ░░░░░
"
"  ▓▓▓▓▓▓▓▓▓▓
" ░▓ author ▓ worbgge <me@worbgge.xyz>
" ░▓▓▓▓▓▓▓▓▓▓
"  ░░░░░░░░░░
"
" Install vim-plug if not already installed (Unix/Linux)
if empty(glob('~/.config/nvim/autoload/plug.vim'))
  silent !curl -fLo ~/.config/nvim/autoload/plug.vim --create-dirs
    \ https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
  autocmd VimEnter * PlugInstall --sync | source $MYVIMRC
endif

" Get plugins
call plug#begin('~/.config/nvim/plugged')
    Plug 'morhetz/gruvbox'
    Plug 'vim-airline/vim-airline'
    Plug 'vim-airline/vim-airline-themes'
    Plug 'plasticboy/vim-markdown'
    Plug 'tpope/vim-surround'
    Plug 'ap/vim-css-color'
    Plug 'ryanoasis/vim-devicons'
    Plug 'gregsexton/MatchTag'
    Plug 'Jorengarenar/vim-MvVis'
    Plug 'yggdroot/indentline'
    Plug 'folke/which-key.nvim'
    Plug 'lambdalisue/suda.vim'
    Plug 'mhinz/vim-startify'
call plug#end()

" Enable mouse support
set mouse=a
" Enable clipboard integration
set clipboard=unnamedplus
set clipboard+=unnamed
" Enable line wrapping
set wrap
" Search and Highlighting
set hlsearch
set incsearch
set ignorecase
set smartcase
" Enable smart indentation
set smartindent
set autoindent
set tabstop=4
set shiftwidth=4
set expandtab
" Completion and Suggestions
set completeopt=menuone,noinsert,noselect
set inccommand=nosplit
" Undo and Redo
set undofile
set undolevels=1000
set undoreload=10000
" Mouse and GUI
set termguicolors
" Enable line-relative numbers (Hybrid mode)
set number relativenumber
" Show a status line with current line and column number
set statusline=%l,%c\ %p%%
" Use a dark background theme
colorscheme gruvbox
let g:airline_theme='gruvbox'
let g:airline_right_alt_sep = ''
let g:airline_right_sep = ''
let g:airline_left_alt_sep= ''
let g:airline_left_sep = ''
" Automatically deletes all trailing whitespace and newlines at end of file on save
autocmd BufWritePre * %s/\s\+$//e
autocmd BufWritePre * %s/\n\+\%$//e
autocmd BufWritePre *.[ch] %s/\%$/\r/e
" Save as sudo with w!! (when lacking root)
cmap w!! w !sudo tee % >/dev/null
set shortmess+=I
" Compile document, be it groff/LaTeX/markdown/etc.
map <leader>c :w! \| !compiler "%:p"<CR>
" Miscellaneous
set autoread
set title
set showmode
set linebreak

" Spell check
set spelllang=en_gb
set spell
set complete+=kspell


" Set directory for backup files
set backupdir=~/.local/share/nvim/backups
set undodir=~/.local/share/nvim/undo/
" set backups
set backup
set writebackup
set swapfile

" Buttons for going to previous/next file (buffer)
map <F2> :bprevious<CR>
map <F3> :bd<CR>
map <F4> :bnext<CR>
" open NERDtree
map <F5> :NERDTreeToggle<CR>
nnoremap <F6> z=

" [airline] Always show numbered listed of buffers
let g:airline#extensions#tabline#enabled=1
let g:airline#extensions#tabline#buffer_nr_show=1
" [airline] Show bottom line always, hide vim mode
set laststatus=2
set noshowmode
" [airline] Remove pause after leaving insert mode
set timeoutlen=50

" [indentline] Change character colour
let g:indentLine_color_term = 239

" [startify] start with custom header
let g:startify_custom_header = [
\ '',
\ '                                                    ▟▙            ',
\ '                                                    ▝▘            ',
\ '            ██▃▅▇█▆▖  ▗▟████▙▖   ▄████▄   ██▄  ▄██  ██  ▗▟█▆▄▄▆█▙▖',
\ '            ██▛▔ ▝██  ██▄▄▄▄██  ██▛▔▔▜██  ▝██  ██▘  ██  ██▛▜██▛▜██',
\ '            ██    ██  ██▀▀▀▀▀▘  ██▖  ▗██   ▜█▙▟█▛   ██  ██  ██  ██',
\ '            ██    ██  ▜█▙▄▄▄▟▊  ▀██▙▟██▀   ▝████▘   ██  ██  ██  ██',
\ '            ▀▀    ▀▀   ▝▀▀▀▀▀     ▀▀▀▀       ▀▀     ▀▀  ▀▀  ▀▀  ▀▀',
\ '',
\ '',
\ '',
\]

" [startify] custom menu
let g:startify_lists = [
      \ { 'header': ['   Bookmarks'],       'type': 'bookmarks' },
      \ { 'header': ['   MRU'],            'type': 'files' },
      \ ]

autocmd StdinReadPre * let g:isReadingFromStdin = 1
autocmd VimEnter * nested if !argc() && !exists('g:isReadingFromStdin') | Startify | endif
