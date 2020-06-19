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

void vectorAngle(vector_t *v, int32_t a){
    v->x=calccos(a);
    v->y=calcsin(a);
}

void vector_init(vector_t *v){
    v->x=0;
    v->y=0;
}

void rotateVector(vector_t *vec, int32_t v) {
    int32_t tempx;
    tempx = FIX14_MULT(vec->x, calccos(v)) - FIX14_MULT(vec->y, calcsin(v));
    vec->y = FIX14_MULT(vec->x, calcsin(v)) + FIX14_MULT(vec->y, calccos(v));
    vec->x = tempx;
}

vector_t rotateVector2(vector_t vec, int32_t v) {
    vector_t temp;
    temp.x = FIX14_MULT(vec.x, calccos(v)) - FIX14_MULT(vec.x, calcsin(v));
    temp.y = FIX14_MULT(vec.x, calcsin(v)) + FIX14_MULT(vec.y, calccos(v));
    return temp;
}

int32_t lengthOfVector(vector_t v) { //takes and returns in fixed point 18.14
	int32_t x2, y2;
	x2 = FIX8_MULT(v.x >> 6, v.x >> 6);
	y2 = FIX8_MULT(v.y >> 6, v.y >> 6);
	return sqrtF2F((x2 + y2) << 6);
}

vector_t coordsToVector(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
	vector_t v;
	v.x = (x2 - x1);
	v.y = (y2 - y1);
	return v;
}

/*
int32_t abs(int32_t n) {
	if (n < 0) FIX14_MULT(n, -1);
	return n;
}
*/

int32_t sqrtF2F (int32_t x) {

  uint32_t t, q, b, r;

  r = x;
  b = 0x40000000;
  q = 0;

  while( b >= 256 ) {
    t = q + b;
    if( r >= t ) {
      r = r - t;
      q = t + b;
    }
    r = r << 1;     /* shift left  1 bit */
    b = b >> 1;     /* shift right 1 bit */
  }
  q = q >> 9;     /* shift right 8 bits CHANGED TO 9 for FIX14!! */

  return( q );
}

/*
int32_t rand(uint32_t tick)
{
	int32_t next = tick;
	next = next * 1103515245 + 12345;
	return (next * 65536) % 32768;
}
*/
