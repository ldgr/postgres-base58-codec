syntax on
set t_Co=256
set number
set tabstop=2
set shiftwidth=2
set expandtab
set cindent

set hlsearch

:nnoremap <C-n> :tabnext<CR>
:nnoremap <C-p> :tabprev<CR>

map <leader>t :tabnew 

autocmd FileType make setlocal noexpandtab

set noswapfile
