#include<stdio.h>

#ifndef uint32_t
typedef unsigned int uint32_t;
#endif

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif

// rotate left
#define ROTL(num, offset) (((num) << (offset)) | ((num) >> (32 - (offset))))


static void quarterround(uint32_t *y0, uint32_t *y1, uint32_t *y2,uint32_t *y3)
{
	*y1 ^= ROTL((*y0 + *y3), 7);
	*y2 ^= ROTL((*y1 + *y0), 9);
	*y3 ^= ROTL((*y2 + *y1), 13);
	*y0 ^= ROTL((*y3 + *y2), 18);
}


static void rowround(uint32_t y[16])
{
	quarterround(&y[0], &y[1], &y[2], &y[3]);
	quarterround(&y[5], &y[6], &y[7], &y[4]);
	quarterround(&y[10], &y[11], &y[8], &y[9]);
	quarterround(&y[15], &y[12], &y[13], &y[14]);
}


static void columnround(uint32_t x[16])
{
	quarterround(&x[0], &x[4], &x[8], &x[12]);
	quarterround(&x[5], &x[9], &x[13], &x[1]);
	quarterround(&x[10], &x[14], &x[2], &x[6]);
	quarterround(&x[15], &x[3], &x[7], &x[11]);
}


static void doubleround(uint32_t x[16])
{
	columnround(x);
	rowround(x);
}


static uint32_t littleendian(uint8_t *b)
{
	return  (uint32_t)b[0] + 
			((uint32_t)b[1] << 8) +
			((uint32_t)b[2] << 16) + 
			((uint32_t)b[3] << 24);
}


static littleendian_r(uint8_t *b, uint32_t w)
{
	b[0] = w;
	b[1] = w >> 8;
	b[2] = w >> 16;
	b[3] = w >> 24;
}


void salsa20_hash(uint8_t seq[64])
{
	uint8_t i;
	uint32_t x[16], z[16];
	for (i = 0; i < 16; ++i)
	{
		z[i] = x[i] = littleendian(seq + (4 * i));
	}
	for (i = 0; i < 10; ++i)
	{
		doubleround(z);
	}
	for (i = 0; i < 16; ++i)
	{
		littleendian_r(seq + (4 * i), (x[i] + z[i]));
	}
}


void salsa20_exp16(uint8_t k[16], uint8 n[16], uint8_t *key)
{
	
}

void salsa20_encrypt();

int main()
{
	uint8_t seq[64]={211,159, 13,115, 76, 55, 82,183, 3,117,222, 37,191,187,234,136,
49,237,179, 48, 1,106,178,219,175,199,166, 48, 86, 16,179,207,
31,240, 32, 63, 15, 83, 93,161,116,147, 48,113,238, 55,204, 36,
79,201,235, 79, 3, 81,156, 47,203, 26,244,243, 88,118,104, 54};
	int a = 0xc0a8787e;
	int b = 0x9fd1161d;
	int c = a+b;
	salsa20_hash(seq);
	//rowround(test);
	//printf("0x%08x\n0x%08x\n", r1, r);
	return 0;
}
