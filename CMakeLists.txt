cmake_minimum_required(VERSION 3.1)
project(tgv_stereo)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14) # C++14...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF)
#set(BOOST_USE_STATIC_LIBS ON)  

#set(CMAKE_CXX_FLAGS "-O2 -std=c++11 -Wall ...")

IF(MSVC_IDE)
  set(OpenCV_STATIC OFF)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-DUSING_CMAKE=1)
ELSE(MSVC_IDE)
  set(CFLAGS_WARN "-Wall -Wextra -Wno-unused-parameter -Wno-strict-aliasing")
  set(CMAKE_CXX_FLAGS "-fPIC -O3 -march=native ${CFLAGS_WARN} ${CMAKE_CXX_FLAGS}")
ENDIF(MSVC_IDE)

if(APPLE)
  set(CUDA_HOST_COMPILER /usr/bin/clang)
endif(APPLE)


find_package(PCL 1.8 REQUIRED)
find_package(Boost COMPONENTS program_options filesystem REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
include_directories(${BOOST_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
include_directories(${BOOST_LIBRAY_DIRS})


add_executable(project_round project_round.cpp)

target_link_libraries(project_round
${Boost_LIBRARIES}
${PCL_LIBRARIES}
boost_program_options
boost_filesystem
)