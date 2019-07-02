# apt-get install build-essential

# apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev

# apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev

# git clone https://github.com/opencv/opencv.git /tmp/opencv
# git clone https://github.com/opencv/opencv_contrib.git /tmp/opencv_contrib

# git -C /tmp/opencv checkout tags/4.1.0 -b 4.1.0
# git -C /tmp/opencv_contrib checkout tags/4.1.0 -b 4.1.0

mkdir -p /tmp/opencv/build

cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=/tmp/opencv_contrib/modules -D PYTHON3_EXECUTABLE=/usr/bin/python3 -D PYTHON_INLCUDE_DIR=/usr/include/python3.6 -D PYTHON_LIBRARY=/usr/lib/x86_64-linux-gnu/libpython3.6m.so -D OPENCV_GENERATE_PKGCONFIG=ON -B/tmp/opencv/build -H/tmp/opencv

make -j7 -C /tmp/opencv/build

make install -C /tmp/opencv/build
