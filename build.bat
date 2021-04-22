@echo off
call E:\VS2019\VC\Auxiliary\Build\vcvarsall x64

mkdir build
pushd  build

DLL_SRC = ../src/commom.cpp
DLL_LDFLAGS = nanogui.obj glad.obj common.obj FormHelper.obj layout.obj object.obj popup.obj theme.obj widget.obj window.obj
DLL_INCLUDE = /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include /I ../ext/Eigen /I ../ext/nanovg/src 


cl /c ../src/nanovg.c /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include /I ../ext/eigen /I ../ext/nanovg/src 
cl /c ../src/glad.c /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include /I ../ext/eigen /I ../ext/nanovg/src 
cl /c ../src/common.cpp /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include /I ../ext/eigen /I ../ext/nanovg/src 
cl /c ../src/FormHelper.cpp /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include /I ../ext/eigen /I ../ext/nanovg/src 
cl /c ../src/layout.cpp /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include /I ../ext/eigen /I ../ext/nanovg/src 
cl /c ../src/object.cpp /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include /I ../ext/eigen /I ../ext/nanovg/src 
cl /c ../src/popup.cpp /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include /I ../ext/eigen /I ../ext/nanovg/src 
cl /c ../src/screen.cpp /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include /I ../ext/eigen /I ../ext/nanovg/src 
cl /c ../src/theme.cpp /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include /I ../ext/eigen /I ../ext/nanovg/src 
cl /c ../src/widget.cpp /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include /I ../ext/eigen /I ../ext/nanovg/src 
cl /c ../src/window.cpp /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include /I ../ext/eigen /I ../ext/nanovg/src 


link /OUT:"nanogui.dll" /DLL /SUBSYSTEM:WINDOWS common.obj FormHelper.obj glad.obj layout.obj nanovg.obj object.obj popup.obj 
screen.obj theme.obj widget.obj window.obj  ../libs/glfw3.lib opengl32.lib User32.lib kernel32.lib gdi32.lib winmm.lib Shell32.lib

cl ../samples/example1.cpp /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include /I ../ext/eigen /I ../ext/nanovg/src  /link nanogui.lib
popd

pause
