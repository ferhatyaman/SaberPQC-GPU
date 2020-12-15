#ifndef SABERGPU_GLOBALS_H
#define SABERGPU_GLOBALS_H

#define IMPL 1

#define LightSaber 0
#define Saber 1
#define FireSaber 2

#define Type unsigned int

#define SABER_SEEDBYTES 32
#define SABER_NOISE_SEEDBYTES 32
#define SABER_KEYBYTES 32
#define SABER_HASHBYTES 32

#define N 256
#define EQ 13
#define EP 10

#if IMPL == LightSaber
#define L 2
#define MU 10
#define ET 3
#define SABER_INDCPA_PUBLICKEYBYTES 672
#define SABER_INDCPA_SECRETKEYBYTES 832
#define SABER_PUBLICKEYBYTES 672
#define SABER_SECRETKEYBYTES 1568
#define SABER_BYTES_CCA_DEC 763

#elif IMPL == Saber
#define L 3
#define MU 8
#define ET 4
#define SABER_INDCPA_PUBLICKEYBYTES 992
#define SABER_INDCPA_SECRETKEYBYTES 1248
#define SABER_PUBLICKEYBYTES 992
#define SABER_SECRETKEYBYTES 2304
#define SABER_BYTES_CCA_DEC 1088

#elif IMPL == FireSaber
#define L 4
#define MU 6
#define ET 6
#define SABER_INDCPA_PUBLICKEYBYTES 1312
#define SABER_INDCPA_SECRETKEYBYTES 1664
#define SABER_PUBLICKEYBYTES 1312
#define SABER_SECRETKEYBYTES 3040
#define SABER_BYTES_CCA_DEC 1472
#endif


#define SABER_POLYCOINBYTES (MU * N / 8)

#define SABER_POLYBYTES (EQ * N / 8)
#define SABER_POLYVECBYTES (L * SABER_POLYBYTES)

#define SABER_POLYCOMPRESSEDBYTES (EP * N / 8)
#define SABER_POLYVECCOMPRESSEDBYTES (L * SABER_POLYCOMPRESSEDBYTES)

#define SABER_SCALEBYTES_KEM (ET * N / 8)

#define SABER_INDCPA_PUBLICKEYBYTES (SABER_POLYVECCOMPRESSEDBYTES + SABER_SEEDBYTES)
#define SABER_INDCPA_SECRETKEYBYTES (SABER_POLYVECBYTES)

#define SABER_PUBLICKEYBYTES (SABER_INDCPA_PUBLICKEYBYTES)
#define SABER_SECRETKEYBYTES (SABER_INDCPA_SECRETKEYBYTES + SABER_INDCPA_PUBLICKEYBYTES + SABER_HASHBYTES + SABER_KEYBYTES)

#define SABER_BYTES_CCA_DEC (SABER_POLYVECCOMPRESSEDBYTES + SABER_SCALEBYTES_KEM)

#endif //SABERGPU_GLOBALS_H