@echo off
call E:\VS2019\VC\Auxiliary\Build\vcvarsall x64

mkdir build
pushd  build
set include=../include
cl ../samples/example1.cpp /link ../bin64/nanogui.lib
popd
pause