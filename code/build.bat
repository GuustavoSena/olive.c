@echo off

mkdir ..\build
pushd ..\build
cl -FC -Zi ..\code\example.cpp
popd

clang -Wall -Wextra --target=wasm32 -o triangle.o -c .\examples\traingle.c
wasm-ld -m wasm32 --no-entry --export-all --allow-undefined -o triangle.wasm triangle.o