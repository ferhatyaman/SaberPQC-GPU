//
// Created by phicoder on 14.12.2020.
//

#include "pack_unpack.h"
#include "pack_unpack.h"
#include <string.h>

void POLT2BS(uint8_t bytes[SABER_SCALEBYTES_KEM], const uint16_t data[N])
{
    size_t j, offset_byte, offset_data;
#if SABER_ET == 3
    for (j = 0; j < N / 8; j++)
	{
		offset_byte = 3 * j;
		offset_data = 8 * j;
		bytes[offset_byte + 0] = (data[offset_data + 0] & 0x7) | ((data[offset_data + 1] & 0x7) << 3) | ((data[offset_data + 2] & 0x3) << 6);
		bytes[offset_byte + 1] = ((data[offset_data + 2] >> 2) & 0x01) | ((data[offset_data + 3] & 0x7) << 1) | ((data[offset_data + 4] & 0x7) << 4) | (((data[offset_data + 5]) & 0x01) << 7);
		bytes[offset_byte + 2] = ((data[offset_data + 5] >> 1) & 0x03) | ((data[offset_data + 6] & 0x7) << 2) | ((data[offset_data + 7] & 0x7) << 5);
	}
#elif SABER_ET == 4
    for (j = 0; j < N / 2; j++)
	{
		offset_byte = j;
		offset_data = 2 * j;
		bytes[offset_byte] = (data[offset_data] & 0x0f) | ((data[offset_data + 1] & 0x0f) << 4);
	}
#elif SABER_ET == 6
    for (j = 0; j < N / 4; j++)
	{
		offset_byte = 3 * j;
		offset_data = 4 * j;
		bytes[offset_byte + 0] = (data[offset_data + 0] & 0x3f) | ((data[offset_data + 1] & 0x03) << 6);
		bytes[offset_byte + 1] = ((data[offset_data + 1] >> 2) & 0x0f) | ((data[offset_data + 2] & 0x0f) << 4);
		bytes[offset_byte + 2] = ((data[offset_data + 2] >> 4) & 0x03) | ((data[offset_data + 3] & 0x3f) << 2);
	}
#else
//#error "Unsupported SABER parameter."
#endif
}

void BS2POLT(const uint8_t bytes[SABER_SCALEBYTES_KEM], uint16_t data[N])
{
    size_t j, offset_byte, offset_data;
#if ET == 3
    for (j = 0; j < N / 8; j++)
	{
		offset_byte = 3 * j;
		offset_data = 8 * j;
		data[offset_data + 0] = (bytes[offset_byte + 0]) & 0x07;
		data[offset_data + 1] = ((bytes[offset_byte + 0]) >> 3) & 0x07;
		data[offset_data + 2] = (((bytes[offset_byte + 0]) >> 6) & 0x03) | (((bytes[offset_byte + 1]) & 0x01) << 2);
		data[offset_data + 3] = ((bytes[offset_byte + 1]) >> 1) & 0x07;
		data[offset_data + 4] = ((bytes[offset_byte + 1]) >> 4) & 0x07;
		data[offset_data + 5] = (((bytes[offset_byte + 1]) >> 7) & 0x01) | (((bytes[offset_byte + 2]) & 0x03) << 1);
		data[offset_data + 6] = ((bytes[offset_byte + 2] >> 2) & 0x07);
		data[offset_data + 7] = ((bytes[offset_byte + 2] >> 5) & 0x07);
	}
#elif ET == 4
    for (j = 0; j < N / 2; j++)
	{
		offset_byte = j;
		offset_data = 2 * j;
		data[offset_data] = bytes[offset_byte] & 0x0f;
		data[offset_data + 1] = (bytes[offset_byte] >> 4) & 0x0f;
	}
#elif ET == 6
    for (j = 0; j < N / 4; j++)
	{
		offset_byte = 3 * j;
		offset_data = 4 * j;
		data[offset_data + 0] = bytes[offset_byte + 0] & 0x3f;
		data[offset_data + 1] = ((bytes[offset_byte + 0] >> 6) & 0x03) | ((bytes[offset_byte + 1] & 0x0f) << 2);
		data[offset_data + 2] = ((bytes[offset_byte + 1] & 0xff) >> 4) | ((bytes[offset_byte + 2] & 0x03) << 4);
		data[offset_data + 3] = ((bytes[offset_byte + 2] & 0xff) >> 2);
	}
#else
#error "Unsupported SABER parameter."
#endif
}

static void POLq2BS(uint8_t bytes[SABER_POLYBYTES], const uint16_t data[N])
{
    size_t j, offset_byte, offset_data;
    for (j = 0; j < N / 8; j++)
    {
        offset_byte = 13 * j;
        offset_data = 8 * j;
        bytes[offset_byte + 0] = (data[offset_data + 0] & (0xff));
        bytes[offset_byte + 1] = ((data[offset_data + 0] >> 8) & 0x1f) | ((data[offset_data + 1] & 0x07) << 5);
        bytes[offset_byte + 2] = ((data[offset_data + 1] >> 3) & 0xff);
        bytes[offset_byte + 3] = ((data[offset_data + 1] >> 11) & 0x03) | ((data[offset_data + 2] & 0x3f) << 2);
        bytes[offset_byte + 4] = ((data[offset_data + 2] >> 6) & 0x7f) | ((data[offset_data + 3] & 0x01) << 7);
        bytes[offset_byte + 5] = ((data[offset_data + 3] >> 1) & 0xff);
        bytes[offset_byte + 6] = ((data[offset_data + 3] >> 9) & 0x0f) | ((data[offset_data + 4] & 0x0f) << 4);
        bytes[offset_byte + 7] = ((data[offset_data + 4] >> 4) & 0xff);
        bytes[offset_byte + 8] = ((data[offset_data + 4] >> 12) & 0x01) | ((data[offset_data + 5] & 0x7f) << 1);
        bytes[offset_byte + 9] = ((data[offset_data + 5] >> 7) & 0x3f) | ((data[offset_data + 6] & 0x03) << 6);
        bytes[offset_byte + 10] = ((data[offset_data + 6] >> 2) & 0xff);
        bytes[offset_byte + 11] = ((data[offset_data + 6] >> 10) & 0x07) | ((data[offset_data + 7] & 0x1f) << 3);
        bytes[offset_byte + 12] = ((data[offset_data + 7] >> 5) & 0xff);
    }
}

static void BS2POLq(const uint8_t bytes[SABER_POLYBYTES], uint16_t data[N])
{
    size_t j, offset_byte, offset_data;
    for (j = 0; j < N / 8; j++)
    {
        offset_byte = 13 * j;
        offset_data = 8 * j;
        data[offset_data + 0] = (bytes[offset_byte + 0] & (0xff)) | ((bytes[offset_byte + 1] & 0x1f) << 8);
        data[offset_data + 1] = (bytes[offset_byte + 1] >> 5 & (0x07)) | ((bytes[offset_byte + 2] & 0xff) << 3) | ((bytes[offset_byte + 3] & 0x03) << 11);
        data[offset_data + 2] = (bytes[offset_byte + 3] >> 2 & (0x3f)) | ((bytes[offset_byte + 4] & 0x7f) << 6);
        data[offset_data + 3] = (bytes[offset_byte + 4] >> 7 & (0x01)) | ((bytes[offset_byte + 5] & 0xff) << 1) | ((bytes[offset_byte + 6] & 0x0f) << 9);
        data[offset_data + 4] = (bytes[offset_byte + 6] >> 4 & (0x0f)) | ((bytes[offset_byte + 7] & 0xff) << 4) | ((bytes[offset_byte + 8] & 0x01) << 12);
        data[offset_data + 5] = (bytes[offset_byte + 8] >> 1 & (0x7f)) | ((bytes[offset_byte + 9] & 0x3f) << 7);
        data[offset_data + 6] = (bytes[offset_byte + 9] >> 6 & (0x03)) | ((bytes[offset_byte + 10] & 0xff) << 2) | ((bytes[offset_byte + 11] & 0x07) << 10);
        data[offset_data + 7] = (bytes[offset_byte + 11] >> 3 & (0x1f)) | ((bytes[offset_byte + 12] & 0xff) << 5);
    }
}

static void POLp2BS(uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], const uint16_t data[N])
{
    size_t j, offset_byte, offset_data;
    for (j = 0; j < N / 4; j++)
    {
        offset_byte = 5 * j;
        offset_data = 4 * j;
        bytes[offset_byte + 0] = (data[offset_data + 0] & (0xff));
        bytes[offset_byte + 1] = ((data[offset_data + 0] >> 8) & 0x03) | ((data[offset_data + 1] & 0x3f) << 2);
        bytes[offset_byte + 2] = ((data[offset_data + 1] >> 6) & 0x0f) | ((data[offset_data + 2] & 0x0f) << 4);
        bytes[offset_byte + 3] = ((data[offset_data + 2] >> 4) & 0x3f) | ((data[offset_data + 3] & 0x03) << 6);
        bytes[offset_byte + 4] = ((data[offset_data + 3] >> 2) & 0xff);
    }
}

static void BS2POLp(const uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], uint16_t data[N])
{
    size_t j, offset_byte, offset_data;
    for (j = 0; j < N / 4; j++)
    {
        offset_byte = 5 * j;
        offset_data = 4 * j;
        data[offset_data + 0] = (bytes[offset_byte + 0] & (0xff)) | ((bytes[offset_byte + 1] & 0x03) << 8);
        data[offset_data + 1] = ((bytes[offset_byte + 1] >> 2) & (0x3f)) | ((bytes[offset_byte + 2] & 0x0f) << 6);
        data[offset_data + 2] = ((bytes[offset_byte + 2] >> 4) & (0x0f)) | ((bytes[offset_byte + 3] & 0x3f) << 4);
        data[offset_data + 3] = ((bytes[offset_byte + 3] >> 6) & (0x03)) | ((bytes[offset_byte + 4] & 0xff) << 2);
    }
}

void POLVECq2BS(uint8_t bytes[SABER_POLYVECBYTES], const uint16_t data[L][N])
{
    size_t i;
    for (i = 0; i < L; i++)
    {
        POLq2BS(bytes + i * SABER_POLYBYTES, data[i]);
    }
}

void BS2POLVECq(const uint8_t bytes[SABER_POLYVECBYTES], uint16_t data[L][N])
{
    size_t i;
    for (i = 0; i < L; i++)
    {
        BS2POLq(bytes + i * SABER_POLYBYTES, data[i]);
    }
}

void POLVECp2BS(uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], const uint16_t data[L][N])
{
    size_t i;
    for (i = 0; i < L; i++)
    {
        POLp2BS(bytes + i * (EP * N / 8), data[i]);
    }
}

void BS2POLVECp(const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], uint16_t data[L][N])
{
    size_t i;
    for (i = 0; i < L; i++)
    {
        BS2POLp(bytes + i * (EP * N / 8), data[i]);
    }
}

void BS2POLmsg(const uint8_t bytes[SABER_KEYBYTES], uint16_t data[N])
{
    size_t i, j;
    for (j = 0; j < SABER_KEYBYTES; j++)
    {
        for (i = 0; i < 8; i++)
        {
            data[j * 8 + i] = ((bytes[j] >> i) & 0x01);
        }
    }
}

void POLmsg2BS(uint8_t bytes[SABER_KEYBYTES], const uint16_t data[N])
{
    size_t i, j;
    memset(bytes, 0, SABER_KEYBYTES);

    for (j = 0; j < SABER_KEYBYTES; j++)
    {
        for (i = 0; i < 8; i++)
        {
            bytes[j] = bytes[j] | ((data[j * 8 + i] & 0x01) << i);
        }
    }
}

/*---------------------------------------------------------------------
This file has been adapted from the implementation
(available at, Public Domain https://github.com/pq-crystals/kyber)
of "CRYSTALS – Kyber: a CCA-secure module-lattice-based KEM"
by : Joppe Bos, Leo Ducas, Eike Kiltz, Tancrede Lepoint,
Vadim Lyubashevsky, John M. Schanck, Peter Schwabe & Damien stehle
----------------------------------------------------------------------*/


static uint64_t load_littleendian(const uint8_t *x, int bytes)
{
    int i;
    uint64_t r = x[0];
    for (i = 1; i < bytes; i++)
        r |= (uint64_t)x[i] << (8 * i);
    return r;
}

void cbd(uint16_t s[N], const uint8_t buf[SABER_POLYCOINBYTES])
{
#if SABER_MU == 6
    uint32_t t, d, a[4], b[4];
  int i, j;

  for (i = 0; i < SABER_N / 4; i++)
  {
    t = load_littleendian(buf + 3 * i, 3);
    d = 0;
    for (j = 0; j < 3; j++)
      d += (t >> j) & 0x249249;

    a[0] = d & 0x7;
    b[0] = (d >> 3) & 0x7;
    a[1] = (d >> 6) & 0x7;
    b[1] = (d >> 9) & 0x7;
    a[2] = (d >> 12) & 0x7;
    b[2] = (d >> 15) & 0x7;
    a[3] = (d >> 18) & 0x7;
    b[3] = (d >> 21);

    s[4 * i + 0] = (uint16_t)(a[0] - b[0]);
    s[4 * i + 1] = (uint16_t)(a[1] - b[1]);
    s[4 * i + 2] = (uint16_t)(a[2] - b[2]);
    s[4 * i + 3] = (uint16_t)(a[3] - b[3]);
  }
#elif SABER_MU == 8
    uint32_t t, d, a[4], b[4];
  int i, j;

  for (i = 0; i < SABER_N / 4; i++)
  {
    t = load_littleendian(buf + 4 * i, 4);
    d = 0;
    for (j = 0; j < 4; j++)
      d += (t >> j) & 0x11111111;

    a[0] = d & 0xf;
    b[0] = (d >> 4) & 0xf;
    a[1] = (d >> 8) & 0xf;
    b[1] = (d >> 12) & 0xf;
    a[2] = (d >> 16) & 0xf;
    b[2] = (d >> 20) & 0xf;
    a[3] = (d >> 24) & 0xf;
    b[3] = (d >> 28);

    s[4 * i + 0] = (uint16_t)(a[0] - b[0]);
    s[4 * i + 1] = (uint16_t)(a[1] - b[1]);
    s[4 * i + 2] = (uint16_t)(a[2] - b[2]);
    s[4 * i + 3] = (uint16_t)(a[3] - b[3]);
  }
#elif SABER_MU == 10
    uint64_t t, d, a[4], b[4];
  int i, j;

  for (i = 0; i < SABER_N / 4; i++)
  {
    t = load_littleendian(buf + 5 * i, 5);
    d = 0;
    for (j = 0; j < 5; j++)
      d += (t >> j) & 0x0842108421UL;

    a[0] = d & 0x1f;
    b[0] = (d >> 5) & 0x1f;
    a[1] = (d >> 10) & 0x1f;
    b[1] = (d >> 15) & 0x1f;
    a[2] = (d >> 20) & 0x1f;
    b[2] = (d >> 25) & 0x1f;
    a[3] = (d >> 30) & 0x1f;
    b[3] = (d >> 35);

    s[4 * i + 0] = (uint16_t)(a[0] - b[0]);
    s[4 * i + 1] = (uint16_t)(a[1] - b[1]);
    s[4 * i + 2] = (uint16_t)(a[2] - b[2]);
    s[4 * i + 3] = (uint16_t)(a[3] - b[3]);
  }
#else
//#error "Unsupported SABER parameter."
#endif
}