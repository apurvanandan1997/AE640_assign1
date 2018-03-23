cmake_minimum_required(VERSION 2.8)
project(imagepub_170141)

find_package(catkin REQUIRED COMPONENTS roscpp cv_bridge image_transport message_generation sensor_msgs dynamic_reconfigure)

catkin_package(CATKIN_DEPENDS roscpp cv_bridge image_transport message_runtime sensor_msgs dynamic_reconfigure)

find_package(OpenCV)

include_directories(include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

# add the publisher example
add_executable(file_publisher src/file_publisher.cpp)
add_dependencies(file_publisher ${catkin_EXPORTED_TARGETS} ${${PROJECT_NAME}_EXPORTED_TARGETS})
target_link_libraries(file_publisher ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(cb_publisher src/cb_publisher.cpp)
add_dependencies(cb_publisher ${catkin_EXPORTED_TARGETS} ${${PROJECT_NAME}_EXPORTED_TARGETS})
target_link_libraries(cb_publisher ${catkin_LIBRARIES} )

install(TARGETS file_publisher 
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(TARGETS cb_publisher 
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
