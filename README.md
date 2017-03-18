# K-Means Clustering

[![Build Status](https://travis-ci.org/mathnogueira/k-means.svg?branch=master)](https://travis-ci.org/mathnogueira/k-means)

## Introduction

Generic euclidean space-based K-means algorithm that can be run as:
* single thread
* multiple processes

## How to build
Clone the repository and download all dependencies using the `dependencies.sh` file to do to. It
will download all dependencies needed by this project.

To download dependencies type:
```bash
chmod +x dependencies.sh
./dependencies.sh
```

To build the library:
```bash
make
```

To build the tests and run it:
```bash
make
make tests
./bin/tests
```