#!/bin/sh

rm -rf tmp

mkdir tmp
cd tmp

git clone -b 'v3.6.0' --single-branch --depth 1 --recurse-submodules https://github.com/ARMmbed/mbedtls

cd mbedtls
mkdir build && cd build

cmake -DCMAKE_INSTALL_PREFIX:PATH=../../mbedtls-build ..
make
make test
make install

cd ../../../