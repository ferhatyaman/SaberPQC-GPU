#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

#include "helper.h"
#include "parameter.h"
#include "globals.h"

#include "poly_arithmetic.cuh"
#include "fips202.h"
#include "pack_unpack.h"


#include <stdlib.h>
#include <time.h>
//srand ((unsigned int) time (NULL));

void random_bytes(uint8_t  seed[], size_t num_bytes)
{
    size_t i;

    for (i = 0; i < num_bytes; i++)
    {
        seed[i] = rand ();
    }

}


void gen_matrix(uint16_t A[L][L][N], uint8_t seed[SABER_SEEDBYTES]) {
    uint8_t buf[L * L * 32 * EQ];
    int i;
    shake128(buf, sizeof(buf), seed, SABER_SEEDBYTES);
    for (i = 0; i < L; i++)
    {
        BS2POLVECq(buf + i * L * 32 * EQ, A[i]);
    }

}

void gen_secret(uint16_t s[L][N], const uint8_t seed[SABER_NOISE_SEEDBYTES])
{
    uint8_t buf[L * SABER_POLYCOINBYTES];
    size_t i;

    shake128(buf, sizeof(buf), seed, SABER_NOISE_SEEDBYTES);

    for (i = 0; i < L; i++)
    {
        cbd(s[i], buf + i * SABER_POLYCOINBYTES);
    }
}


 __global__ void poly_mul(uint16_t c[], uint16_t a[], uint16_t b[], uint16_t q)
{
    register int i = blockIdx.x * 1 + threadIdx.x;

    uint16_t rc = a[i] * b[i];

    c[i] = rc & (q-1);
}

__global__ void vector_mul(uint16_t **c, uint16_t **a, uint16_t **b, uint16_t q)
{
    register int i = blockIdx.x * 1 + threadIdx.x;


    poly_mul<<<1,N,0,0>>>(c[i],a[i],b[i],q);

}

void matrix_vector_mul(uint16_t **b, uint16_t ***A, uint16_t **s) {

    for (int i = 0; i < L; i++){
        vector_mul<<<1,L,0,0>>>(b, A[i], s, 1<<13);

    }

}

void KeyGen(uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], uint8_t sk[SABER_INDCPA_SECRETKEYBYTES]) {
    uint16_t A[L][L][N];
    uint16_t s[L][N];
    uint16_t b[L][N] = {0};

    uint8_t seed_A[SABER_SEEDBYTES];
    uint8_t seed_s[SABER_NOISE_SEEDBYTES];

    random_bytes(seed_A,SABER_SEEDBYTES);
    random_bytes(seed_s,SABER_NOISE_SEEDBYTES);

    gen_matrix(A, seed_A);
    gen_secret(s, seed_s);

    uint16_t ***A_device = (uint16_t***)malloc(sizeof (uint16_t**) * L);
    for (int i = 0; i<L;i++)
        A_device[i] = (uint16_t**)malloc(sizeof (uint16_t*) * L);

    for (int i = 0; i<L;i++){
        for (int j = 0; j<L;j++)
             cudaMalloc(&A_device[i][j], sizeof (uint16_t) * N);
    }
    cudaMemcpy(A_device,A,sizeof (uint16_t) * N*L*L,cudaMemcpyHostToDevice);

    uint16_t **s_device = (uint16_t**)malloc(sizeof (uint16_t*) * L);
    for (int i = 0; i<L;i++)
        cudaMalloc(&s_device[i], sizeof (uint16_t) * N);

    uint16_t **b_device = (uint16_t**)malloc(sizeof (uint16_t*) * L);
    for (int i = 0; i<L;i++)
        cudaMalloc(&b_device[i], sizeof (uint16_t) * N);

    cudaMemcpy(A_device,A,sizeof (uint16_t) * N*L*L,cudaMemcpyHostToDevice);

    matrix_vector_mul(b_device, A_device, s_device);

    free(A);
    cudaFree(A_device);




}

int main() {
    uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES];
    uint8_t sk[SABER_INDCPA_SECRETKEYBYTES];

    KeyGen(pk,sk);

    return 0;
}
