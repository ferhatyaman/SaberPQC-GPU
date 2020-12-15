cmake_minimum_required(VERSION 3.15)
project(SaberGPU LANGUAGES CXX CUDA)


set(CMAKE_CUDA_STANDARD 14)
#set(CMAKE_CUDA_FLAGS "-arch=sm_30")

add_library(SaberGPU STATIC
        helper.h
        parameter.h
        salsa_common.h
        uint128.h
        poly_arithmetic.cu
        poly_arithmetic.cuh globals.h fips202.cpp fips202.h pack_unpack.cpp pack_unpack.h)





# Request that particles be built with -std=c++11
# As this is a public compile feature anything that links to particles
# will also build with -std=c++11
target_compile_features(SaberGPU PUBLIC cxx_std_11)

# We need to explicitly state that we need all CUDA files in the particle
# library to be built with -dc as the member functions could be called by
# other libraries and executables
set_target_properties(SaberGPU
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)


add_executable(demo main.cu)

set_target_properties(demo PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
target_link_libraries(demo PRIVATE SaberGPU)



