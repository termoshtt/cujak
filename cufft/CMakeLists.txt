cmake_minimum_required(VERSION 2.8)
cuda_add_library(cujak_cufft STATIC
  Converter.cu
)
target_link_libraries(cujak_cufft cujak)
add_subdirectory(test)
