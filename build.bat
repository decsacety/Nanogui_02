@echo off
call E:\VS2019\VC\Auxiliary\Build\vcvarsall x64

mkdir build
pushd  build

cl /c ../src/common.cpp /MDd /I ../include /I ../ext/glfw/include /FO"nanogui.obj"
cl /c ../src/screen.cpp /MDd /I ../include /I ../ext/glfw/include /I ../ext/glad/include
cl /c ../src/glad.c /MDd /I ../ext/glad/include
link -lib nanogui.obj screen.obj glad.obj ../libs/glfw3.lib opengl32.lib User32.lib kernel32.lib gdi32.lib winmm.lib Shell32.lib
cl ../samples/example1.cpp /MDd /I ../include  /I ../ext/glad/include /link nanogui.lib
popd

pause