cmake_minimum_required(VERSION 2.8)
project( ImageProcessing )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set (CMAKE_CXX_STANDARD 11)
add_executable( ImageProcessing image_processing.cpp )
target_link_libraries( ImageProcessing ${OpenCV_LIBS} )

# # Python wrap 
# find_package(PythonLibs REQUIRED)
# include_directories(${PYTHON_INCLUDE_DIR})
 
# find_package(Boost COMPONENTS python REQUIRED)
# include_directories(${Boost_INCLUDE_DIR})
 
# # Build & Link our library
# add_library(image MODULE image_processing.cpp)
# target_link_libraries(image ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
# # don't prepend wrapper library name with lib
# set_target_properties(image PROPERTIES PREFIX "")
