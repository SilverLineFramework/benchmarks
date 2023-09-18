#!/bin/bash
dn=wasm-wali
on=wasm-wali-instrument

script_dir=$(dirname -- $0)

src_dir=$script_dir/../$dn
dst_dir=$script_dir/../$on

wasmfiles=$(find $src_dir -type f -name "*.wasm")

for instlevel in $(seq 0 5 10); do
  for srcfile in $wasmfiles; do
    instfile=${srcfile//$dn/"$on/$instlevel"}
    mkdir -p $(dirname -- $instfile)
    echo $instfile $srcfile
    $script_dir/../../instrument  --multithread -s memaccess-stochastic --args="30 500" -o $instfile $srcfile
  done
done

