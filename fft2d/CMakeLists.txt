cmake_minimum_required(VERSION 2.8)

add_custom_command(
  OUTPUT fft2d.pb.cc fft2d.pb.h
  DEPENDS fft2d.proto
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND "protoc" "fft2d.proto" "--cpp_out=${CMAKE_CURRENT_SOURCE_DIR}" "--python_out=${CMAKE_CURRENT_SOURCE_DIR}"
  COMMAND "protoc" "fft2d.proto" "--cpp_out=${CMAKE_CURRENT_BINARY_DIR}"
)
cuda_add_library(cujak_cufft STATIC
  Converter.cu
  fft2d.pb.cc
)
target_link_libraries(cujak_cufft cujak protobuf)

add_subdirectory(test)
