cmake_minimum_required(VERSION 2.8)
project(image_enhancer_170141)

find_package(catkin REQUIRED COMPONENTS roscpp rospy cv_bridge image_transport message_generation sensor_msgs dynamic_reconfigure)

generate_dynamic_reconfigure_options(
  cfg/ImageChanger.cfg
  )

catkin_package(CATKIN_DEPENDS roscpp rospy cv_bridge image_transport message_runtime sensor_msgs dynamic_reconfigure)

#find_package(OpenCV)

include_directories(
    include 
    ${catkin_INCLUDE_DIRS} 
    #${OpenCV_INCLUDE_DIRS}
    )

# add the publisher example
add_executable(image_changer src/image_changer.cpp)
add_dependencies(image_changer ${catkin_EXPORTED_TARGETS} ${${PROJECT_NAME}_EXPORTED_TARGETS})
target_link_libraries(image_changer ${catkin_LIBRARIES}) #${OpenCV_LIBRARIES})

add_executable(image_dynamic_changer src/image_dynamic_changer.cpp)
add_dependencies(image_dynamic_changer ${catkin_EXPORTED_TARGETS} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${PROJECT_NAME}_gencfg)
target_link_libraries(image_dynamic_changer ${catkin_LIBRARIES} )

install(TARGETS image_changer 
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(TARGETS image_dynamic_changer 
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
