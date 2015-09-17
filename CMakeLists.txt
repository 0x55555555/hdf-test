cmake_minimum_required(VERSION 3.0)

set(HDF_DIR /Volumes/User/hdf5/)
set(HDF_BUILD_DIR ${HDF_DIR}build/)
set(HDF_SUFFIX _debug)

SET(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10.4)

include_directories(
  ${HDF_DIR}/build
  ${HDF_DIR}/c++/src
  ${HDF_DIR}/src)

add_executable(hdf5_test
  main.cpp
)

target_link_libraries(hdf5_test
  ${HDF_BUILD_DIR}/bin/libhdf5_cpp${HDF_SUFFIX}.a
  ${HDF_BUILD_DIR}/bin/libhdf5${HDF_SUFFIX}.a)
