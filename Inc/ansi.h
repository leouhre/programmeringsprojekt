#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>


#ifndef _ANSI_H_
#define _ANSI_H_
#define SCREEN_HEIGHT 56
#define SCREEN_WIDTH 211

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void resetbgcolor();
void clrscr();
void clreol();
void gotoxy(uint8_t x, uint8_t y);
void hideCursor();
void moveDown(uint8_t y);
void moveUp(uint8_t y);
void moveBack(uint8_t x);
void moveForward(uint8_t x);
void underline(uint8_t on);
void blink(uint8_t on);
void inverse(uint8_t on);
void box(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t style);
void boxWithText(uint8_t x, uint8_t y, char* s, uint16_t style);
void boxWithTextCenterAligned(uint8_t middlex, uint8_t y, char* s, uint16_t style);
void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char* s, uint8_t style);
//letters
void renderLetter(char x);
void renderWord(char *x);


#endif /* _ANSI_H_ */
