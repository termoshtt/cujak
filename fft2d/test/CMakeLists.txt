cmake_minimum_required(VERSION 2.8)

cujak_add_test(cufft_convert convert.cu cujak_fft2d)
cujak_add_test(cufft_pb pb.cu cujak_fft2d)
cujak_add_test(cufft_algorithm algorithm.cu cujak_fft2d)
cujak_add_test(cufft_data data.cu cujak_fft2d)
