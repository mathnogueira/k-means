## Download all dependencies and build them

mkdir -p .dependencies
mkdir -p libs

## GTest v1.8
mkdir -p .dependencies/gtest
mkdir -p libs/gtest
cd .dependencies/gtest

## Only downloads if file is not found
if [ ! -f release-1.8.0.tar.gz ]; then
	wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz
fi
## Extract it
tar -xvf release-1.8.0.tar.gz
cd googletest-release-1.8.0/googletest

## Build it
mkdir build
cd build
cmake .. && make

## Copy important files
cp libgtest.a ../../../../../libs/gtest/
cp libgtest_main.a ../../../../../libs/gtest/
cp -r ../include ../../../../../libs/gtest/