@echo off

mkdir ..\build
pushd ..\build
cl -FC -Zi ..\code\example.cpp
popd