@echo off
REM TODO - can we just build both with one exe?

set CommonCompilerFlags=-diagnostics:column -DLP_DEBUG=1 -DLP_INTERNAL=1 -MTd -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4456 -wd4505 -FAsc -Z7
set CommonLinkerFlags=-incremental:no -opt:ref user32.lib
REM user32.lib gdi32.lib winmm.lib

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

REM 32-bit build
REM cl %CommonCompilerFlags% ..\code\win32_handmade.cpp /link -subsystem:windows,5.1 %CommonLinkerFlags%

REM 64-bit build
del *.pdb > NUL 2> NUL
cl %CommonCompilerFlags% ..\code\win32_d3d11.cpp -I..\code\imgui -Fmwin32_d3d9.map /link %CommonLinkerFlags% d3d11.lib
popd
