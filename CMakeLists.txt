cmake_minimum_required( VERSION 3.10 )
project( image_processing )
find_package( OpenCV REQUIRED )
find_package( PythonLibs 3.6 REQUIRED )
include_directories( include ${OpenCV_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin )
set( CMAKE_CXX_STANDARD 11 )
add_executable( image_processing 
                    src/image_processing.cpp 
                    src/morph_transformations.cpp 
                    src/objects.cpp 
                    src/drawing.cpp 
                    src/ssd.cpp
                    
                )
target_link_libraries( image_processing ${OpenCV_LIBS} ${PYTHON_LIBRARIES} )
