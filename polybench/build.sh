for PB_DIR in $(find -maxdepth 1 -name 'pb_*')
do
    cp ./common_makefile $PB_DIR/Makefile
    cd $PB_DIR
    make
    cd ..
done