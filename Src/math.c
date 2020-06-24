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
	// Returns sin(n) in FIX14 where n is a full circle in 512 steps
    return SIN[n & 0x1FF];
}

int32_t calccos(int32_t n) {
	// Returns cos(n) in FIX14 where n is a full circle in 512 steps
    return calcsin(n+128);
}

void vector_angle(vector_t *v, int32_t a){
	// Assigns a vector a given angle a (length of vector is always 1)
    v->x=calccos(a);
    v->y=calcsin(a);
}

void vector_init(vector_t *v){
	// Initializes a vector to 0
    v->x=0;
    v->y=0;
}

void rotate_vector(vector_t *vec, int32_t a) {
	// Rotates an already existing vector a given angle a
    int32_t tempx;
    tempx = FIX14_MULT(vec->x, calccos(a)) - FIX14_MULT(vec->y, calcsin(a));
    vec->y = FIX14_MULT(vec->x, calcsin(a)) + FIX14_MULT(vec->y, calccos(a));
    vec->x = tempx;
}

vector_t rotate_vector2(vector_t vec, int32_t a) {
	// Returns a vector rotated with angle a without modifying the original vector
    vector_t temp;
    temp.x = FIX14_MULT(vec.x, calccos(a)) - FIX14_MULT(vec.x, calcsin(a));
    temp.y = FIX14_MULT(vec.x, calcsin(a)) + FIX14_MULT(vec.y, calccos(a));
    return temp;
}

int32_t lengthOfVector(vector_t v) {
	// Takes a vector in fixed point 18.14 and returns
	// the length of the vector in fixed point 18.14
	int32_t x2, y2;
	x2 = FIX8_MULT(v.x >> 6, v.x >> 6); // To avoid overflow, the calculations
	y2 = FIX8_MULT(v.y >> 6, v.y >> 6); // use FIX8 at the cost of less precision
	return sqrtF2F((x2 + y2) << 6);
}

vector_t coordsToVector(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
	// Takes two coordinates and creates a vector between them from (x1, y1) to (x2,y2)
	vector_t v;
	v.x = (x2 - x1);
	v.y = (y2 - y1);
	return v;
}

/*
 * fixed sqrtF2F( fixed X );
 *
 * Fixed to fixed point square roots.
 * RETURNS the fixed point square root of X (fixed).
 * REQUIRES X is positive.
 *
 * Christophe MEESSEN, 1993.
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
  q = q >> 9;     /* shift right 8 bits CHANGED TO 9 for FIX14 */

  return( q );
}
