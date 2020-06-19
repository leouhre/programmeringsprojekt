#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>
#include "sinus.h"

#ifndef _MATH_H_
#define _MATH_H_

#define FIX14_SHIFT 14
#define FIX8_SHIFT 8

#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b)  ( ((a) << FIX14_SHIFT) / b )
#define FIX8_MULT(a, b) ( (a)*(b) >> FIX8_SHIFT )
#define FIX10_DIV(a, b) ( ((a) << 10) / b )

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)


typedef struct {
    int32_t x, y;
} vector_t;

void printFix(int32_t i);
int32_t expand(int32_t i);
int32_t calcsin(int32_t n);
int32_t calccos(int32_t n);
void rotateVector(vector_t *vec, int32_t v);
void vectorAngle(vector_t *v, int32_t a);
void vector_init(vector_t *v);
int32_t lengthOfVector(vector_t v);
vector_t coordsToVector(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
//int32_t abs(int32_t n);
int32_t sqrtF2F (int32_t x);
//int32_t rand(uint32_t tick);
#endif /* _MATH_H_ */
