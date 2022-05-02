#!/bin/bash

WASMCC=/opt/wasi-sdk/bin/clang

opt -load ./$2.so -$2 $1 -S -o out.ll
opt -load ./dyn_inst_cnt.so -dyn-inst-cnt out.ll -S -o opt_prof.ll

$WASMCC -Wl,--export=runtime_ctr -O3 opt_prof.ll -o opt_prof.wasm

