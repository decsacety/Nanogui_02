@echo off
call E:\VS2019\VC\Auxiliary\Build\vcvarsall x64

mkdir build
pushd  build

cl -c ../src/common.cpp  /MDd /I ../include  /Fo"nanogui"
link -lib nanogui.obj
cl ../samples/example1.cpp /MDd /I ../include  /link nanogui.lib
popd

pause