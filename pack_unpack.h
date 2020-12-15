#ifndef SABERGPU_PACK_UNPACK_H
#define SABERGPU_PACK_UNPACK_H

#include <stdio.h>
#include <stdint.h>
#include "globals.h"

void POLT2BS(uint8_t bytes[SABER_SCALEBYTES_KEM], const uint16_t data[N]);
void BS2POLT(const uint8_t bytes[SABER_SCALEBYTES_KEM], uint16_t data[N]);

void POLVECq2BS(uint8_t bytes[SABER_POLYVECBYTES], const uint16_t data[L][N]);
void POLVECp2BS(uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], const uint16_t data[L][N]);

void BS2POLVECq(const uint8_t bytes[SABER_POLYVECBYTES], uint16_t data[L][N]);
void BS2POLVECp(const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], uint16_t data[L][N]);

void BS2POLmsg(const uint8_t bytes[SABER_KEYBYTES], uint16_t data[N]);
void POLmsg2BS(uint8_t bytes[SABER_KEYBYTES], const uint16_t data[N]);

void cbd(uint16_t s[N], const uint8_t buf[SABER_POLYCOINBYTES]);

#endif //SABERGPU_PACK_UNPACK_H
