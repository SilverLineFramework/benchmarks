for PB_DIR in $(find -maxdepth 1 -name 'pb_*')
do
    cd $PB_DIR
    make clean
    cd ..
done