# Gaia Boat - image processing module

## About the Gaia Boat

The Gaia Boat is an autonomous boat designed to collect trash from a lake’s shore. It uses image processing to detect obstacles and trash, an app for tracing routes and a series of other embedded software for controlling the hardware.

## Other Gaia Boat’s software links

- [gaia router](https://github.com/gaia-boat/router)
- [gaia control](https://github.com/gaia-boat/control)
- [gaia app](https://github.com/gaia-boat/app)
- [gaia communication](https://github.com/gaia-boat/communication)
- [gaia image processing](https://github.com/gaia-boat/image-processing)

## Image processing module

### Usage and installation

#### Usage

This module is responsable for the image processing algorithmn of Gaia boat project’s object detection logic. This is used to make evasive manuvers, if needed. 

#### Installation

## Requirements

- OpenCV 4.1.0
- Python 3.6+

## Installation

1. Install OpenCV following [this tutorial](dependencies/README.md)
2. Install the image processing package running:

```
python3 setup.py install --user
```

To install the package you must install if through pip, using the following command:

```shell
pip install gaia-image-processing
```

If you want to upgrade its version you must use:

```shell
pip install --upgrade gaia-image-processing
```


