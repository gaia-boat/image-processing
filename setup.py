from distutils.core import setup, Extension


opencv_libs =  ["opencv_stitching", "opencv_aruco", "opencv_bgsegm",
                "opencv_bioinspired", "opencv_ccalib", "opencv_dnn_objdetect",
                "opencv_dpm", "opencv_face", "opencv_freetype", "opencv_fuzzy",
                "opencv_hfs", "opencv_img_hash", "opencv_line_descriptor",
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
                   sources=['src/image_processing.cpp', 'src/morph_transformations.cpp', 'src/objects.cpp', 'src/drawing.cpp'])

setup(name='image_processing', ext_modules=[module])
