#!/bin/bash

if [ -z "$3" ]
then
  opt -load ./$2.so -$2 $1 -S -o out.ll
else
  opt -load ./$2.so -$2 $1 -threshold $3 -S -o out.ll
fi

clang --target=wasm32-wasi --sysroot=/opt/wasi-sdk/share/wasi-sysroot -O3 out.ll -o out.wasm
wamrc -o out.aot out.wasm
