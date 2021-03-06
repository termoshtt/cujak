cmake_minimum_required(VERSION 2.8)
PROJECT(cujak)

find_package(CUDA REQUIRED)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

cuda_add_library(cujak STATIC
  ./exception.cpp
)
target_link_libraries(cujak ${CUDA_cufft_LIBRARY} ${CUDA_curand_LIBRARY})

enable_testing()
add_custom_target(cujak_test COMMAND "ctest")
macro(cujak_add_test name src)
    set(test_name TEST_cujak_${name})
    cuda_add_executable(${test_name} ${src})
    target_link_libraries(${test_name}
      ${GTEST_BOTH_LIBRARIES}
      ${ARGN})
    add_test(${test_name} ${CMAKE_CURRENT_BINARY_DIR}/${test_name})
    add_dependencies(cujak_test ${test_name})
    unset(test_name)
endmacro(cujak_add_test)

add_subdirectory(fft2d)
add_subdirectory(test)
