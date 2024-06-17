cmake_minimum_required(VERSION 3.27)

project( RayTracing )

set ( CMAKE_CXX_STANDARD 20 )

set ( 
    SOURCES
    source/main.cpp
    source/vec3.cpp
)

find_package(SDL2 REQUIRED)

include_directories( source ${SDL2_INCLUDE_DIRS} )

add_executable( raytracing ${SOURCES} )
target_link_libraries( raytracing ${SDL2_LIBRARIES} )