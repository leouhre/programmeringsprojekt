#include "math.h"

void printFix(int32_t i) {
    // Prints a signed 16.16 fixed point number
    if ((i & 0x80000000) != 0) {
    // Handle negative numbers
        printf("-");
        i = ~i + 1;
    }
    printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
    // Print a maximum of 4 decimal digits to avoid overflow
}

int32_t expand(int32_t i) {
    // Converts an 18.14 fixed point number to 16.16
    return i << 2;
}

int32_t calcsin(int32_t n) {
    return SIN[n & 0x1FF];
}

int32_t calccos(int32_t n) {
    return calcsin(n+128);
}

void vectorinit(vector_t *v, int32_t a){
    v->x=calccos(a);
    v->y=calcsin(a);
}

void rotateVector(vector_t *vec, int32_t v) {
    int32_t tempx;
    tempx = FIX14_MULT(vec->x, calccos(v)) - FIX14_MULT(vec->y, calcsin(v));
    vec->y = FIX14_MULT(vec->x, calcsin(v)) + FIX14_MULT(vec->y, calccos(v));
    vec->x = tempx;
}

int32_t abs(int32_t n) {
	if (n < 0) FIX14_MULT(n, -1);
	return n;
}

