cmake_minimum_required(VERSION 2.8)
PROJECT(cujak)

find_package(CUDA REQUIRED)

cuda_add_library(cujak STATIC
  ./exception.cpp
)
target_link_libraries(cujak ${CUDA_cufft_LIBRARY})

add_subdirectory(test EXCLUDE_FROM_ALL)
