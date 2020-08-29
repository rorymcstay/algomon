rm -r build

mkdir build

cd build && cmake \
    -DCMAKE_INSTALL_PREFIX=$INSTALL ../

