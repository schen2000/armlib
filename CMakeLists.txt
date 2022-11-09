project(armlib)
cmake_minimum_required(VERSION 3.4)

SET(CMAKE_CXX_STANDARD 14)

find_package (jsoncpp REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

#--- Hack for Mac brew
link_directories(/opt/dep/local/lib)

#---- 
message(STATUS "vsnLb_DIR=$ENV{vsnLib_DIR}")

add_subdirectory(dep/z1_sdk)

include_directories(
    inc 
    dep/z1_sdk/include
    ${EIGEN3_INCLUDE_DIR}
    $ENV{vsnLib_DIR}/inc
    ${JsonCpp_INCLUDE_DIR}
    /opt/dep/local/include
    /usr/include/jsoncpp

    )

link_directories(dep/z1_sdk/lib)

FILE(GLOB  SRC_CORE src/*.cpp)
add_library(armLib ${SRC_CORE} )
target_link_libraries(armLib   
    vsnLib 
    Z1_SDK_Linux64
    -fPIC
    pthread
    ${OpenCV_LIBRARIES}
    ${Eigen3_LIBRARY}    
    )

FILE(GLOB  SRC_TEST test/*.cpp)
add_executable(armTest ${SRC_TEST})
target_link_libraries(armTest armLib)

