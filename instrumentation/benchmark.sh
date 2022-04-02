#!/bin/bash

WASMCC=/opt/wasi-sdk/bin/clang

opt -load ./$2.so -$2 $1 -S -o out.ll

opt -load ./dyn_inst_cnt.so -dyn-inst-cnt out.ll -S -o opt_prof.ll
opt -load ./dyn_inst_cnt.so -dyn-inst-cnt $1 -S -o unopt_prof.ll

$WASMCC -Wl,--export=runtime_ctr -O3 opt_prof.ll -o opt_prof.wasm
$WASMCC -O3 unopt_prof.ll -o unopt_prof.wasm

wasm2wat opt_prof.wasm -o opt_prof.wat
wasm2wat unopt_prof.wasm -o unopt_prof.wat

wamrc -o opt_prof.aot opt_prof.wasm
wamrc -o unopt_prof.aot unopt_prof.wasm
