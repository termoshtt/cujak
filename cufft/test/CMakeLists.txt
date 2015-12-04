cmake_minimum_required(VERSION 2.8)
cujak_add_test(cufft_convert convert.cu cujak_cufft)
cujak_add_test(cufft_pb pb.cu cujak_cufft)
cujak_add_test(cufft_algorithm algorithm.cu cujak_cufft)
