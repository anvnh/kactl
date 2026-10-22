set cin aw ai is ts=4 sw=4 tm=50 nu noeb bg=dark ru cul
sy on | im jk <esc> | im kj <esc> | no ; :
" Select region and then type :Hash to hash your selection.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \| md5sum \| cut -c-6
nnoremap <F1> :w<CR>:!g++ -Wall -Wconversion -Wfatal-errors -g -std=c++17 -fsanitize=undefined,address % -o %:r && ./%:r<CR>
