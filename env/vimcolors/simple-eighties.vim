" vi:syntax=vim

" simple-eighties
" by Davide Stasio, based on base16-eighties
" NOTE: gui_cyan and gui_yellow used for unset values
hi clear
syntax reset
let g:colors_name = "simple-eighties"

" https://colorschemedesigner.com/csd-3.5/#4262ysKqWIIBX1BGDt
" GUI colors
let g:shi_bg       = "2D2D2D"
let g:shi_bg_alt   = "393939"
let g:shi_fg       = "d3d0c8"
let g:shi_fg_alt   = "a09f93"
let g:shi_accent   = "515151"
let g:shi_comment  = "7c97b2"
let g:shi_keyword  = "f2777a"
let g:shi_str      = "99cc99"
let g:shi_str_alt  = "66cccc"
let g:shi_number   = "f99157"
let g:shi_preproc  = "cc99cc"
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
