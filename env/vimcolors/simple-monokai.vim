" vi:syntax=vim

" simple-monokai
" by Davide Stasio, based on base16-monokai
" NOTE: gui_cyan and gui_yellow used for unset values
hi clear
syntax reset
let g:colors_name = "simple-monokai"

" https://colorschemedesigner.com/csd-3.5/#4262ysKqWIIBX1BGDt
" GUI colors
let g:shi_bg       = "272822"     " base16_00
let g:shi_bg_alt   = "383830"     " base16_01
let g:shi_fg       = "f8f8f2"     " base16_05
let g:shi_fg_alt   = "a59f85"     " base16_04
let g:shi_accent   = "49483e"     " base16_02
let g:shi_comment  = "66d9ef"     " base16_0D
let g:shi_keyword  = "ae81ff"     " base16_0E
let g:shi_str      = "a6e22e"     " base16_0B
let g:shi_str_alt  = "a1efe4"     " base16_0C
let g:shi_number   = "fd971f"     " base16_09
let g:shi_preproc  = "f92672"     " base16_08
let g:shi_cursor   = g:shi_accent
let g:shi_error    = g:shi_preproc

let g:shi_err_yellow   = "FFFF00"
let g:shi_err_cyan     = "00FFFF"
let g:shi_err_magenta  = "FF00FF"
let g:shi_err_red      = "FF0000"
let g:shi_err_green    = "00FF00"
let g:shi_err_blue     = "0000FF"

"func highlight()
ru colors/simple-template.vim

" Remove color variables
unlet g:shi_bg g:shi_bg_alt g:shi_fg g:shi_fg_alt g:shi_accent g:shi_comment g:shi_keyword g:shi_str g:shi_str_alt g:shi_number g:shi_preproc g:shi_cursor g:shi_error
unlet g:shi_err_yellow g:shi_err_cyan g:shi_err_magenta g:shi_err_red g:shi_err_green g:shi_err_blue
