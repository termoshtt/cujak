cmake_minimum_required(VERSION 2.8)
find_package(CUDA REQUIRED)
if(CUDA_FOUND)
    include(cuda_util.cmake)
    add_subdirectory(test EXCLUDE_FROM_ALL)
    cuda_add_library(CujakCUDA STATIC
      ./exception.cpp
    )
    target_link_libraries(CujakCUDA ${CUDA_cufft_LIBRARY})
endif(CUDA_FOUND)
