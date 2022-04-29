#!/bin/bash
TIMEFORMAT=%3E
N=50
make clean
make -C instrumentation
mkdir -p results

if [[ $1 == "instrument" ]]; then
  rm results/results-t*
  # Run instrumented code
  for thresh in {20..150..40}
  do
    echo "THRESHOLD: $thresh"
    make clean-ll
    make -C polybench-raw instrument=1 threshold=$thresh -j6
    make aot -j6
    filename=results/results-t$thresh
   
    echo "" | tee -a $filename
    for FILE in aot/polybench-raw-inst/medium/*; do
      data_pts=""
      for ((i=0 ; i<$N ; i++))
      do
        exec_time=$({ time iwasm $FILE ; } 2>&1 > /dev/null)
        data_pts+=$(echo "scale=4; $exec_time*1000" | bc -l)
        data_pts+=" "
      done
      median=$(printf '%s\n' $data_pts | datamash mean 1 median 1)
      echo "$(basename $FILE)(INST) : [$median]" | tee -a $filename
    done
  done

else
  ## Run base code
  make -C polybench-raw
  make aot -j6

  filename=results/results-base
  rm $filename

  for FILE in aot/polybench-raw/medium/*; do
    data_pts=""
    for ((i=0 ; i<$N ; i++))
    do
      exec_time=$({ time iwasm $FILE ; } 2>&1 > /dev/null)
      data_pts+=$(echo "scale=4; $exec_time*1000" | bc -l)
      data_pts+=" "
    done
    median=$(printf '%s\n' $data_pts | datamash mean 1 median 1)
    echo "$(basename $FILE)(BASE) : [$median]" | tee -a $filename
  done
fi
