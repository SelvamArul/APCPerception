cmake_minimum_required(VERSION 2.8)
project(aisimagecapture)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	std_msgs
	message_generation
	cv_bridge
  	image_transport
)

include_directories(${catkin_INCLUDE_DIRS} include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")


#generate_messages(
#	DEPENDENCIES std_msgs
# )

catkin_package()

add_executable(aic
	src/aic.cpp
)
target_link_libraries(aic
	${catkin_LIBRARIES}
)
