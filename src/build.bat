@echo off

chdir ..\build

set "LLVMPath=C:\Program Files\LLVM"

set "VSPath=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community"
set "VSVersion=14.10.25017"

set "WinSDKVersion=10.0.14393.0"
set "WinSDKPath=C:\Program Files (x86)\Windows Kits\10"
:: Change this to your resulting exe
set "OUTPUT=release/yapt.exe"

:: Setup
set "VSBasePath=%VSPath%\VC\Tools\MSVC\%VSVersion%"
set "PATH=%PATH%;%LLVMPath%\bin;%VSBasePath%\bin\HostX64\x64"

:: Compiler Flags
set CFLAGS= ^
 -std=c++14 ^
 -I "..\lib\sfml\include" ^
 -I "..\lib\imgui" ^
 -I "..\lib\imgui-sfml" ^
 -fopenmp ^
 -xc -O3

set CPPFLAGS= 

:: Linker Libs
set LDFLAGS= ^
 -machine:x64 ^
 -subsystem:console ^
 
set LDLIBS= ^
	-libpath:"%VSBasePath%\lib\x64" ^
	-libpath:"%WinSDKPath%\Lib\%WinSDKVersion%\ucrt\x64" ^
	-libpath:"%WinSDKPath%\Lib\%WinSDKVersion%\um\x64" ^
	-libpath:"C:\Program Files\LLVM\lib" ^
	-libpath:"..\lib\sfml\lib" ^
	libucrt.lib libvcruntime.lib libcmt.lib libcpmt.lib ^
	legacy_stdio_definitions.lib oldnames.lib ^
	legacy_stdio_wide_specifiers.lib  libomp.lib ^
	kernel32.lib User32.lib ^
	sfml-main.lib sfml-graphics.lib sfml-graphics-s.lib opengl32.lib ^
	sfml-window.lib sfml-system.lib sfml-window-s.lib sfml-system-s.lib jpeg.lib vorbis.lib vorbisfile.lib


:: Compiling
@echo on
@for %%f in (..\src\*.cpp) do (
    clang++.exe "%%~f" -o "%%~nf.o" -c %CFLAGS%
)

set "files=main.o imgui-SFML.o imgui_draw.o imgui_demo.o imgui.o window.o surface.o screen.o obj_parser.o mesh.o material.o kd_tree.o hitlist.o engine.o camera.o"
:: Linking
@set "LINK_FILES="
@for %%f in (*.o) do (
    @set "LINK_FILES=%LINK_FILES% %%f"
)

lld-link.exe %files% -out:"%OUTPUT%" %LDFLAGS% %LDLIBS%

chdir release
yapt.exe

PAUSE