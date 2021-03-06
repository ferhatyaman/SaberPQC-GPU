#pragma once

#ifndef POLY_ARITHMETIC
#define POLY_ARITHMETIC

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "uint128.h"

__global__ void barrett(unsigned long long a[], const unsigned long long b[], unsigned long long q, unsigned long long mu, int qbit);

__global__ void barrett_int(unsigned long long a[], const unsigned long long b, unsigned long long q, unsigned long long mu, int qbit);

__global__ void mod_t(unsigned long long a[], const unsigned long long b, unsigned long long t);

__global__ void fast_convert_array_kernel_t(unsigned long long* input_poly, unsigned long long* result_poly, unsigned long long t, unsigned long long* base_change_matrix_device, unsigned q_amount, unsigned n);

__global__ void fast_convert_array_kernel_gamma(unsigned long long* input_poly, unsigned long long* result_poly, unsigned long long gamma, unsigned long long* base_change_matrix_device, unsigned q_amount, int gamma_bit_length, unsigned long long mu_gamma, unsigned n);

__host__ void fast_convert_array_kernels(unsigned long long* input_poly, unsigned long long* result_poly, unsigned long long t, unsigned long long* base_change_matrix_device, unsigned q_amount, unsigned long long gamma, int gamma_bit_length, unsigned long long mu_gamma, cudaStream_t& stream1, cudaStream_t& stream2, unsigned n);

__global__ void poly_add(unsigned long long a[], const unsigned long long b[], unsigned long long q);

__global__ void poly_sub(unsigned long long a[], const unsigned long long b[], unsigned long long q);

__host__ void poly_add_device(unsigned long long* device_a, const unsigned long long* device_b, unsigned n, cudaStream_t& stream, unsigned long long q);

__host__ void poly_sub_device(unsigned long long* device_a, const unsigned long long* device_b, unsigned n, cudaStream_t& stream, unsigned long long q);

__host__ void dec_round(unsigned long long* input_poly, unsigned long long* result_poly, unsigned long long t, unsigned long long gamma, unsigned long long gamma_div_2, unsigned n, cudaStream_t& stream);

__global__ void dec_round_kernel(unsigned long long* input_poly, unsigned long long* result_poly, unsigned long long t, unsigned long long gamma, unsigned long long gamma_div_2, unsigned n);

__host__ void poly_negate_device(unsigned long long* device_a, unsigned n, cudaStream_t& stream, unsigned long long q);

__host__ void poly_add_integer_device(unsigned long long* device_a, unsigned long long b, unsigned n, cudaStream_t& stream, unsigned long long q);

__global__ void poly_add_integer(unsigned long long a[], unsigned long long b, unsigned long long q);

__global__ void divide_and_round_q_last_inplace_loop(unsigned long long* input_poly, unsigned long long* rns_poly_minus1, unsigned long long base_q_i,
                                                     unsigned long long half_mod, unsigned long long inv_q_last_mod_q_i, unsigned long long base_q_i_mu, int base_q_i_qbit);

__global__ void weird_m_stuff(unsigned long long* m_poly, unsigned long long* c0, unsigned long long t, unsigned long long* qi_div_t_rns_array_device,
                              unsigned long long* q_array_device, unsigned q_amount, unsigned n);

__host__ void poly_add_integer_device_default(unsigned long long* device_a, unsigned long long b, unsigned n, unsigned long long q);

#endif 