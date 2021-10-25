" vi:syntax=vim

" simple-orange
" by Davide Stasio
" NOTE: gui_cyan and gui_yellow used for unset values
hi clear
syntax reset
let g:colors_name = "simple-orange"

" https://colorschemedesigner.com/csd-3.5/#4262ysKqWIIBX1BGDt
" GUI colors
let g:shi_bg       = "372918"
let g:shi_bg_alt   = "553D1F"
let g:shi_fg       = "E9DAC8"
let g:shi_fg_alt   = "ABA8A5"
let g:shi_accent   = "745D30"
let g:shi_comment  = "7ED7B7"
let g:shi_keyword  = "7ED781"
let g:shi_str      = "AADC2D"
let g:shi_str_alt  = "FFFF00"
let g:shi_number   = "C9C14A"
let g:shi_preproc  = "E460A7"
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
