cmake_minimum_required(VERSION 2.8)

add_custom_command(
  OUTPUT fft2d.pb.cc fft2d.pb.h
  DEPENDS fft2d.proto
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND "protoc" "fft2d.proto" "--cpp_out=${CMAKE_CURRENT_SOURCE_DIR}" "--python_out=${CMAKE_CURRENT_SOURCE_DIR}"
  COMMAND "protoc" "fft2d.proto" "--cpp_out=${CMAKE_CURRENT_BINARY_DIR}"
)
cuda_add_library(cujak_fft2d STATIC
  plan.cu
  pb_convert.cu
  pb_io.cu
  algorithm.cu
  fft2d.pb.cc
)
target_link_libraries(cujak_fft2d cujak protobuf)

add_subdirectory(bin)
add_subdirectory(test)
