" vi:syntax=vim

" simple-mocha
" by Davide Stasio, based on base16-mocha
" NOTE: gui_cyan and gui_yellow used for unset values
hi clear
syntax reset
let g:colors_name = "simple-mocha"

" https://colorschemedesigner.com/csd-3.5/#4262ysKqWIIBX1BGDt
" GUI colors
let g:shi_bg       = "3B3228"     " base16_00
let g:shi_bg_alt   = "534636"     " base16_01
let g:shi_fg       = "d0c8c6"     " base16_05
let g:shi_fg_alt   = "b8afad"     " base16_04
let g:shi_accent   = "645240"     " base16_02
let g:shi_comment  = "8ab3b5"     " base16_0D
let g:shi_keyword  = "a89bb9"     " base16_0E
let g:shi_str      = "beb55b"     " base16_0B
let g:shi_str_alt  = "7bbda4"     " base16_0C
let g:shi_number   = "d28b71"     " base16_09
let g:shi_preproc  = "cb6077"     " base16_08
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
