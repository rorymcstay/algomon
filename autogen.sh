rm -r build

mkdir build

install=`pwd`/install

cd build && cmake \
    -DCMAKE_INSTALL_PREFIX=$install ../

