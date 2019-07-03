# OpenCV installation

To run the project  OpenCV 4.1.0 must be installed, it can be installed following the [installation tutorial of OpenCV documentation](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html). To make the installation easier the Gaia Team created an installation script for OpenCV, to use it follow the steps:

1. Check the configuration variables to see if the default values can be applied to your OS:
```
# Directory where the source code of OpenCV will be cloned to be built
DIR=$HOME

# Path to the Python3 executable
PYTHON3_EXEC_DIR=/usr/bin/python3

# Path to the Python3 include directory
PYTHON3_INCLUDE_DIR=/usr/include/python3.6

# Path to the Python3 lib directory 
PYTHON3_LIB_DIR=/usr/lib/x86_64-linux-gnu/libpython3.6m.so
```

2. Run the script `opencv.sh` as root:

```bash
$ sudo ./opencv.sh
```
