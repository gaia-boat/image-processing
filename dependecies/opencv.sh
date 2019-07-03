#!/bin/bash

set -e

if [ "$EUID" -ne 0 ] 
then
    echo "Please run as root"
    exit
fi

DIR=$HOME
OPENCV_DIR=$DIR/opencv/opencv
OPENCV_CONTRIB_DIR=$DIR/opencv/opencv_contrib
OPENCV_BUILD_DIR=$OPENCV_DIR/build
OPENCV_VERSION=4.1.0

PYTHON3_EXEC_DIR=/usr/bin/python3
PYTHON3_INCLUDE_DIR=/usr/include/python3.6
PYTHON3_LIB_DIR=/usr/lib/x86_64-linux-gnu/libpython3.6m.so

INSTALL_PREFIX_DIR=/usr/local

echo "Installing required packages"
apt-get install -y build-essential \
                cmake git libgtk2.0-dev \
                pkg-config libavcodec-dev \
                libavformat-dev libswscale-dev

apt-get install -y python-dev python-numpy \
                libtbb2 libtbb-dev libjpeg-dev \
                libpng-dev libtiff-dev \
                libjasper-dev libdc1394-22-dev

cmake --version

echo "Clonning opencv core repository"
git clone https://github.com/opencv/opencv.git $OPENCV_DIR

echo "Clonning opencv contrib core repository"
git clone https://github.com/opencv/opencv_contrib.git $OPENCV_CONTRIB_DIR

echo "Selecting Version $OPENCV_VERSION"
git -C $OPENCV_DIR checkout tags/$OPENCV_VERSION -b $OPENCV_VERSION
git -C $OPENCV_CONTRIB_DIR checkout tags/$OPENCV_VERSION -b $OPENCV_VERSION

echo "Creating build dir"
mkdir -p $OPENCV_BUILD_DIR

echo "Building Opencv..."
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=$INSTALL_PREFIX_DIR \
      -D OPENCV_EXTRA_MODULES_PATH=$OPENCV_CONTRIB_DIR/modules \
      -D PYTHON3_EXECUTABLE=$PYTHON3_EXEC_DIR \
      -D PYTHON_INLCUDE_DIR=$PYTHON3_INCLUDE_DIR \
      -D PYTHON_LIBRARY=$PYTHON3_LIB_DIR \
      -D OPENCV_GENERATE_PKGCONFIG=ON -B$OPENCV_BUILD_DIR -H$OPENCV_DIR

echo "Running make..."
make -j7 -C $OPENCV_BUILD_DIR

echo "Installing OpenCV"
make install -C $OPENCV_BUILD_DIR 
