cmake_minimum_required(VERSION 3.27)

project( RayTracing )

set ( CMAKE_CXX_STANDARD 20 )

set ( 
    SOURCES
    source/main.cpp
)

include_directories( source )

add_executable( raytracing ${SOURCES} )