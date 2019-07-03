import os
import codecs
from os import path
from setuptools import setup
from setuptools import find_packages
from pip._internal.req import parse_requirements
from distutils.core import setup, Extension


opencv_libs =  ["opencv_stitching", "opencv_aruco", "opencv_bgsegm",
                "opencv_bioinspired", "opencv_ccalib", "opencv_dnn_objdetect",
                "opencv_dpm", "opencv_face", "opencv_freetype", "opencv_fuzzy", "opencv_hfs", "opencv_img_hash", "opencv_line_descriptor",
                "opencv_quality", "opencv_reg", "opencv_rgbd", "opencv_saliency",
                "opencv_stereo", "opencv_structured_light", "opencv_phase_unwrapping",
                "opencv_superres", "opencv_optflow", "opencv_surface_matching",
                "opencv_tracking", "opencv_datasets", "opencv_text", "opencv_dnn",
                "opencv_plot", "opencv_videostab", "opencv_video", "opencv_xfeatures2d",
                "opencv_shape", "opencv_ml", "opencv_ximgproc", "opencv_xobjdetect",
                "opencv_objdetect", "opencv_calib3d", "opencv_features2d", "opencv_highgui",
                "opencv_videoio", "opencv_imgcodecs", "opencv_flann", "opencv_xphoto",
                "opencv_photo", "opencv_imgproc", "opencv_core"]

module = Extension("image_processing",
                   include_dirs=['include/', '/usr/local/include/opencv4/',
                                 '/usr/local/include/opencv4/opencv'],
                   libraries = opencv_libs,
                   library_dirs=['/usr/local/lib'],
                   sources=['src/image_processing.cpp', 'src/morph_transformations.cpp',
                            'src/objects.cpp', 'src/drawing.cpp'])

# parse_requirements() returns generator of pip.req.InstallRequirement objects
INSTALL_REQS = parse_requirements('requirements.txt', session='hack')

# reqs is a list of requirements
REQUIREMENTS = [str(ir.req) for ir in INSTALL_REQS]

CLASSIFIERS = [
    "Development Status :: 5 - Production/Stable",
    "Intended Audience :: Other Audience",
    "Natural Language :: Portuguese",
    "License :: OSI Approved :: GNU General Public License v3 or later (GPLv3+)",
    "Operating System :: OS Independent",
    "Programming Language :: Python",
    "Programming Language :: Python :: 3.6",
    "Programming Language :: Python :: Implementation :: CPython",
    "Programming Language :: Python :: Implementation :: PyPy",
    "Topic :: Software Development :: Libraries :: Python Modules",
]

setup(  # pragma: no cover
    name='gaia-image-processing',
    description="Image processing module for the gaia boat.",  # nopep8
    url='https://github.com/gaia-boat/image-processing',
    long_description=codecs.open('README.md', 'rb', 'utf8').read(),
    long_description_content_type='text/markdown',
    version=codecs.open('VERSION.txt', 'rb', 'utf8').read(),
    keywords=['gaia', 'boat', 'pi2'],
    install_requires=REQUIREMENTS,
    license='GNU',
    classifiers=CLASSIFIERS,
    ext_modules=[module],
)
