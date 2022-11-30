cmake_minimum_required(VERSION 3.0.2)
project(bag_to_img)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  rosbag
  cv_bridge
  sensor_msgs
)
find_package(OpenCV REQUIRED)

catkin_package(
  INCLUDE_DIRS 
)

include_directories(
	include
	${catkin_INCLUDE_DIRS}
)

link_directories(
	include
)


add_executable(bag_to_img src/bag_to_img.cpp)
add_dependencies(bag_to_img ${catkin_EXPORTED_TARGETS})
target_link_libraries(bag_to_img ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
