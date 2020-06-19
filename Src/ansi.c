#define ESC 0x1B

#include "ansi.h"

void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr() {
// move cursor to beginning and clear
    printf("%c[0;0H", ESC);
    printf("%c[2J",ESC);
}

void clreol() {
// clear rest of current line
    printf("%c[K", ESC);
}

void hideCursor(){
    printf("%c[?25l",ESC);
}


void gotoxy(uint8_t x, uint8_t y) {
// move cursor to x,y
    printf("%c[%d;%dH", ESC,y,x);
}

void moveDown(uint8_t y){
    printf("%c[%dB", ESC,y);
}

void moveUp(uint8_t y){
    printf("%c[%dA", ESC,y);
}

void moveForward(uint8_t x){
    printf("%c[%dC", ESC,x);
}

void moveBack(uint8_t x){
    printf("%c[%dD", ESC,x);
}

void underline(uint8_t on) {
// underline on/off
    uint8_t n = 24;
    if (on == 1) {
        n = 4;
    }
    printf("%c[%dm", ESC,n);
}

void blink(uint8_t on) {
// blinking text on/off
    uint8_t n = 25;
    if (on == 1) {
        n = 5;
    }
    printf("%c[%dm", ESC,n);
}

void inverse(uint8_t on) {
// inverse colors on/off
    uint8_t n = 27;
    if (on == 1) {
        n = 7;
    }
    printf("%c[%dm", ESC,n);
}

void box(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t style){

    int cornertl;
    int cornertr;
    int cornerbl;
    int cornerbr;

    int lineh;
    int linev;

    int width;
    int height;

    if(style>0){
        cornertl=201;
        cornertr=187;
        cornerbl=200;
        cornerbr=188;

        linev = 186;
        lineh = 205;
    }else{
        cornertl=218;
        cornertr=191;
        cornerbl=192;
        cornerbr=217;

        linev = 179;
        lineh = 196;
    }

    if(x1<1||x2<1||y1<1||y2<1){
        x1=1;
        x2=1;
        y1=1;
        y2=1;
    }

    if(x1>x2){
        int dummy=x1;
        x1=x2;
        x2=dummy;
    }
    if(y1>y2){
        int dummy=y1;
        y1=y2;
        y2=dummy;
    }

    width  = x2-x1;
    height = y2-y1;


    //topline print
    gotoxy(x1,y1);
    printf("%c", cornertl);
    for(int i=0; i<=width-2;i++){
        printf("%c",lineh);
    }
    printf("%c",cornertr);

    //bottomline print
    gotoxy(x1,y2);
        printf("%c",cornerbl);
    for(int i=0; i<=width-2;i++)
        printf("%c",lineh);
        printf("%c",cornerbr);

    //side print
    for(int i=1;i<height;i++){
        gotoxy(x1,y1+i);
        printf("%c",linev);
        gotoxy(x2,y1+i);
        printf("%c",linev);
    }


}

void boxWithText(uint8_t x, uint8_t y, char* s, uint16_t style){

    uint8_t wordLength=strlen(s);
    box(x, y, x + (wordLength * 8) + 4, y + 8, style );
    gotoxy(x + 3, y + 2);
    renderWord(s);
}

void boxWithTextInTheMiddleOfTheScreen(uint8_t middlex, uint8_t y, char* s, uint16_t style){

    uint8_t wordLength=strlen(s);

    boxWithText(middlex - 1 - wordLength*4,y,s, style);
}

void arrowpointer();


void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char* s, uint8_t style) {
    uint8_t length = strlen(s), sizex = x2 - x1, sizey = y2 - y1, i;
    gotoxy(x1,y1);
    if (style == 0) {
        printf("%c", 218);
        printf("%c", 180);
        inverse(1);
        printf("  ");
        printf("%s", s);
        for (i = 0; i < sizex - length - 5; i++) {
        printf(" ");
        }
        inverse(0);
        printf("%c", 195);
        printf("%c", 191);
        for (i = 0; i < sizey - 1; i++) {
            printf("%c[1B", ESC);
            printf("%c[%dD", ESC,sizex + 1);
            printf("%c", 179);
            printf("%c[%dC", ESC,sizex - 1);
            printf("%c", 179);
        }
        printf("%c[1B", ESC);
        printf("%c[%dD", ESC,sizex + 1);
        printf("%c", 192);
        for (i = 0; i < sizex - 1; i++) {
        printf("%c", 196);
        }
        printf("%c", 217);
    } else if(style == 1) {
        printf("%c", 201);
        printf("%c", 185);
        inverse(1);
        printf("  ");
        printf("%s", s);
        printf("  ");
        inverse(0);
        printf("%c", 204);
        for (i = 0; i < sizex - length - 7; i++) {
        printf("%c", 205);
        }
        printf("%c", 187);
        for (i = 0; i < sizey - 1; i++) {
            printf("%c[1B", ESC);
            printf("%c[%dD", ESC,sizex + 1);
            printf("%c", 186);
            printf("%c[%dC", ESC,sizex - 1);
            printf("%c", 186);
        }
        printf("%c[1B", ESC);
        printf("%c[%dD", ESC,sizex + 1);
        printf("%c", 200);
        for (i = 0; i < sizex - 1; i++) {
        printf("%c", 205);
        }
        printf("%c", 188);
        }
}

//letters

void renderLetter(char x){
    char b = 219;
    char letter[7][5];
    int i, j;

    for(j=0; j<5; j++){
        for(i=0; i<7;i++){
            letter[i][j] =' ';
        }
    }

    switch(x){
            case 'p':
                for(j=0; j<5; j++){
                    for (i=0;i<3;i++){
                        letter[i][j]=b;
                    }
                }
                for(j=1; j<4; j++){
                    for (i=3;i<5;i++){
                        letter[i][j]=b;
                    }
                }

                for (i=5;i<7;i++){
                    letter[i][2]=b;
                }

                break;
            case 'q':

                for(j=0; j<5; j++){
                    for (i=4;i<7;i++){
                        letter[i][j]=b;
                    }
                }
                for(j=1; j<4; j++){
                    for (i=2;i<4;i++){
                        letter[i][j]=b;
                    }
                }

                for (i=0;i<2;i++){
                    letter[i][2]=b;
                }

                break;

            case '*':
                for(j=0; j<5; j++)
                    for(i = 0; i < 7; i++)
                        letter[i][j]=b;
                break;
            case ' ':
                break;

            case '-':
                    for(i = 1; i < 6; i++)
                        letter[i][2]=b;
                break;
            case 'A':
                    for(i=1; i<6; i++)
                        letter[i][0]=b;

                    for(j=1; j<5; j++){
                        for(i=0; i<2; i++)
                        letter[i][j]=b;

                        for(i=5; i<7; i++)
                        letter[i][j]=b;
                    }
                    for(i=0; i<7; i++)
                    letter[i][2]=b;
                break;

            case 'B':

                for(j=0; j < 5; j += 2){
                    for(i=0; i<6; i++)
                        letter[i][j]=b;
                }
                for(j=1; j < 4; j += 2){
                    for(i=0; i<2; i++)
                        letter[i][j]=b;
                    for(i=5; i<7; i++)
                        letter[i][j]=b;
                }
                break;
            case 'C':
                for(i=1; i<7; i++)
                    letter[i][0]=b;
                for(i=1; i<7; i++)
                    letter[i][4]=b;
                for(j=1; j<4; j++){
                    letter[0][j]=b;
                    letter[1][j]=b;
                }
                break;

            case 'D':
                for(i=0; i<6; i++)
                    letter[i][0]=b;
                for(i=0; i<6; i++)
                    letter[i][4]=b;

                for(j=1; j<4; j++){
                        for(i=0; i<2; i++)
                        letter[i][j]=b;

                        for(i=5; i<7; i++)
                        letter[i][j]=b;
                }

                break;

            case 'E':
                for(j=0; j<5; j++){
                    for(i=0; i<2; i++)
                    letter[i][j]=b;
                }

                for(j=0; j<5; j+=2){
                    for(i=0; i<7; i++)
                    letter[i][j]=b;
                }
                break;
            case 'F':
                for(j=0; j<5; j++){
                    for(i=0; i<2; i++)
                        letter[i][j]=b;
                }

                for(i=2; i<7; i++)
                        letter[i][0]=b;

                for(i=2; i<5; i++)
                        letter[i][2]=b;
                break;
            case 'G':
                for(j=1; j<4; j++)
                    for(i=0; i<2; i++)
                        letter[i][j]=b;

                for(j=2; j<4; j++)
                    for(i=5; i<7; i++)
                        letter[i][j]=b;

                for(i=1; i<6; i++){
                    letter[i][0]=b;
                    letter[i][4]=b;
                }
                letter[4][2]=b;
                break;

            case 'H':
                for(j=0; j<5; j++){
                    for(i=0; i<2; i++){
                        letter[i][j]=b;
                        letter[i+5][j]=b;
                    }
                }
                for(i=2; i<5; i++)
                    letter[i][2]=b;

                break;
            case 'I':
                for(j=0; j<5; j++){
                    for(i=2; i<4; i++)
                    letter[i][j]=b;
                }
                for(i=1; i<6; i++){
                    letter[i][0]=b;
                    letter[i][4]=b;
                }
                break;
            case 'J':
                for(j=0; j<4; j++){
                    letter[5][j]=b;
                    letter[6][j]=b;
                }
                for(i=1; i<6; i++)
                    letter[i][4]=b;
                letter[0][3]=b;
                letter[1][3]=b;
                break;
            case 'K':
                for(j=0; j<5; j++){
                    for(i=0; i<2; i++)
                        letter[i][j]=b;
                }
                for(i=2; i<5; i++)
                        letter[i][2]=b;

                letter[5][0]=b;
                letter[6][0]=b;
                letter[4][1]=b;
                letter[5][1]=b;
                letter[4][3]=b;
                letter[5][3]=b;
                letter[5][4]=b;
                letter[6][4]=b;

                break;
            case 'L':
                for(j=0; j<5; j++){
                    for(i=0; i<2; i++)
                        letter[i][j]=b;
                }

                for(i=2; i<7; i++)
                        letter[i][4]=b;
                break;
            case 'M':
                for(j=0; j<5; j++){
                    letter[0][j]=b;
                    letter[1][j]=b;
                    letter[5][j]=b;
                    letter[6][j]=b;
                }

                letter[2][1]=b;
                letter[3][2]=b;
                letter[4][1]=b;
                break;
            case 'N':
                for(j=0; j<5; j++){
                    for(i=0; i<2; i++)
                    letter[i][j]=b;
                    for(i=5; i<7; i++)
                    letter[i][j]=b;
                }
                i=0;
                while(i<4){
                    for(j=0; j<3; j++)
                        letter[2+i][j+i]=b;
                    i++;
                }
                break;
            case 'O':
                for(j=1; j<4; j++){
                    for(i=0; i<2; i++)
                    letter[i][j]=b;
                    for(i=5; i<7; i++)
                    letter[i][j]=b;
                }

                for(i=1; i<6; i++){
                    letter[i][0]=b;
                    letter[i][4]=b;
                }
                break;

            case 'P':
                for(j=0; j<5; j++){
                    for(i=0; i<2; i++)
                        letter[i][j]=b;
                }

                for(i=2; i<6; i++){
                    letter[i][0]=b;
                    letter[i][2]=b;
                }

                    letter[5][1]=b;
                    letter[6][1]=b;
                break;
            case 'R':
                for(i=1; i<6; i++) //copy of A
                        letter[i][0]=b;

                    for(j=1; j<5; j++){
                        for(i=0; i<2; i++)
                        letter[i][j]=b;

                        for(i=5; i<7; i++)
                        letter[i][j]=b;
                    }
                    for(i=0; i<7; i++)
                    letter[i][2]=b;

                    letter[6][2]=' ';

                break;

            case 'S':

                for(i=0; i<2; i++){
                letter[i][1]=b;
                letter[i+5][3]=b;
                }

                for(j=0; j<5; j+=2){
                    for(i=0; i<7; i++)
                    letter[i][j]=b;
                }


                break;

            case 'T':
                for(i=0; i<7; i++)
                    letter[i][0]=b;

                 for(j=0; j<5; j++){
                    for(i=2; i<4; i++)
                    letter[i][j]=b;
                }


                break;
            case 'U':
                for(j=0; j<4; j++){
                    letter[0][j]=b;
                    letter[1][j]=b;
                    letter[5][j]=b;
                    letter[6][j]=b;
                }
                for(i=1; i<6; i++)
                    letter[i][4]=b;

                break;
            case 'V':
                for(j=0; j<3; j++){
                    for(i=0; i<2; i++){
                        letter[i][j]=b;
                        letter[i+5][j]=b;
                    }
                }

                    letter[1][3]=b;
                    letter[2][3]=b;
                    letter[4][3]=b;
                    letter[5][3]=b;

                    letter[2][4]=b;
                    letter[3][4]=b;
                    letter[4][4]=b;


                break;

            case 'W':
                for(j=0; j<4; j++){
                    for(i=0; i<2; i++){
                        letter[i][j]=b;
                        letter[i+5][j]=b;
                    }
                }

                    letter[3][3]=b;

                    letter[1][4]=b;
                    letter[2][4]=b;
                    letter[4][4]=b;
                    letter[5][4]=b;

                break;
            case 'Y':

                    letter[0][0]=b;
                    letter[1][0]=b;
                    //letter[5][0]=b;
                    letter[6][0]=b;

                    letter[1][1]=b;
                    letter[2][1]=b;
                    letter[6][1]=b;
                    letter[5][1]=b;

                    letter[2][2]=b;
                    letter[3][2]=b;
                    letter[4][2]=b;
                    letter[5][2]=b;
                for(j=2; j<5; j++){
                    letter[3][j]=b;
                    letter[4][j]=b;
                }



                break;
            default: break;
    }

    for(j=0; j<5; j++){
        for(i=0; i<7;i++)
            printf("%c",letter[i][j]);
        moveDown(1);
        moveBack(7);
    }
    moveForward(8);
    moveUp(5);

}

void renderWord(char *x){
    uint8_t i;

    for(i = 0; i < strlen(x); i++ ){
        renderLetter(x[i]);
        }
}
