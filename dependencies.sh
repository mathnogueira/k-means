## Download all dependencies and compile it
##
rm -rf libs
mkdir -p deps
mkdir -p libs

## CMOCKA
wget https://cmocka.org/files/1.1/cmocka-1.1.0.tar.xz -P deps/
cd deps
tar -xvf cmocka-1.1.0.tar.xz
cd cmocka-1.1.0

## Define static mode on
echo 'option(WITH_STATIC_LIB "Build with a static library" ON)' >> DefineOptions.cmake
mkdir build
cd build
cmake ..
make

cd ../../../libs
mkdir -p cmocka
pwd
cp ../deps/cmocka-1.1.0/build/src/libcmocka.so ./cmocka/libcmocka.so
cp ../deps/cmocka-1.1.0/build/src/libcmocka.so.0 ./cmocka/libcmocka.so.0
cp ../deps/cmocka-1.1.0/build/src/libcmocka.so.0 ./cmocka/libcmocka.so.0.4.0
cp -r ../deps/cmocka-1.1.0/include ./cmocka/include


## Remove deps
rm -r ../deps