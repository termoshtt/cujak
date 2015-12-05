cmake_minimum_required(VERSION 2.8)

add_definitions("-fopenmp")
macro(cujak_fft2d_executable name)
    set(exec_name cujak_fft2d_${name})
    add_executable(${exec_name} ${name}.cpp)
    target_link_libraries(${exec_name} cujak_fft2d ${ARGN})
    install(PROGRAMS ${exec_name} DESTINATION bin)
endmacro(cujak_fft2d_executable)

cujak_fft2d_executable(c2r)
