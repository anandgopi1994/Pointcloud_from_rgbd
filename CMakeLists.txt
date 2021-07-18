cmake_minimum_required(VERSION 2.8)
 
project(point_cloud)
find_package(OpenCV REQUIRED)
find_package(PCL 1.2 REQUIRED)
 
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
 
add_executable(point_cloud point_cloud.cpp )
target_link_libraries(point_cloud ${OpenCV_LIBS} ${PCL_LIBRARIES})
