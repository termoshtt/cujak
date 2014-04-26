cmake_minimum_required(VERSION 2.8)
find_package(CUDA REQUIRED)
if(CUDA_FOUND)
    include(cuda_util.cmake)
    add_subdirectory(test EXCLUDE_FROM_ALL)
    cuda_add_library(cujak_util_cuda STATIC
      ./exception.cpp
      ./cufft.cu
    )
    target_link_libraries(cujak_util_cuda ${CUFFT_LIBRARY})
endif(CUDA_FOUND)
