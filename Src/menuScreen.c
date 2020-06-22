#include "menuScreen.h"

void gameInit(gameHandler_t *game){
    game->difficulty = 5;
    game->mode = 1;
    game->currentLevel = 0;
    game->currentScore = 0;
    game->status = 0;
}



void loadMenu(){

    //each letter is 7 wide + 1 space, making a 4 letter word 32 wide
    //our longest word is 7 letters so 56
    uint8_t x = 211, y = 56, boxes=0, firstboxY = 20;
    clrscr();
    box(1,1,x,y,1);

    uint8_t middlex = (211 - 1 )/2; //105

    boxWithTextInTheMiddleOfTheScreen(middlex, 5,"       ", 1);

    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY,"START",1);
    boxes++;
    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY+boxes*9,"OPTIONS",1);
    boxes++;
    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY+boxes*9,"HOW TO PLAY",1);
    boxes++;
    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY+boxes*9,"CREDITS",1);
    boxes++;
}

void selectInMenu(gameHandler_t *game){
    uint8_t select=0, flagMenu=1;
    uint8_t op0xv = 105-30, op1xv = 105-38, op2xv = 105-38-16, op3xv = 105-38;
    uint8_t op0xh = 105+26, op1xh = 105+34, op2xh = 105+34+16, op3xh = 105+34;
    loadMenu();

while(flagMenu==1){

    if(flagMenu==1){
        switch(select){
            case 0:
                //clear option 1
                gotoxy(op1xv, 22+9);
                renderLetter(' ');
                gotoxy(op1xh, 22+9);
                renderLetter(' ');

                //move to option 0
                gotoxy(op0xv, 22);
                renderLetter('p');
                gotoxy(op0xh, 22);
                renderLetter('q');
                flagMenu--;
            break;

            case 1:
                //clear option 0
                gotoxy(op0xv,22);
                renderLetter(' ');
                gotoxy(op0xh,22);
                renderLetter(' ');

                //clear option 2
                gotoxy(op2xv,22+18);
                renderLetter(' ');
                gotoxy(op2xh,22+18);
                renderLetter(' ');

                //move to option 1
                gotoxy(op1xv,22+9);
                renderLetter('p');
                gotoxy(op1xh,22+9);
                renderLetter('q');
                flagMenu--;
            break;

            case 2:
                //clear option 1
                gotoxy(op1xv,22+9);
                renderLetter(' ');
                gotoxy(op1xh,22+9);
                renderLetter(' ');

                //clear option 3
                gotoxy(op3xv,22+27);
                renderLetter(' ');
                gotoxy(op3xh,22+27);
                renderLetter(' ');

                //move to option 2:
                gotoxy(op2xv,22+18);
                renderLetter('p');
                gotoxy(op2xh,22+18);
                renderLetter('q');
                flagMenu--;
            break;
            case 3:
                //clear option 2
                gotoxy(op2xv,22+18);
                renderLetter(' ');
                gotoxy(op2xh,22+18);
                renderLetter(' ');

                //move to option 3
                gotoxy(op3xv,22+27);
                renderLetter('p');
                gotoxy(op3xh,22+27);
                renderLetter('q');
                flagMenu--;
            break;
        }
    }

        while(flagMenu==0){
            switch(readControls()){
              /*w*/ case 0x01:
                    if(select > 0){
                        select--;
                        flagMenu++;
                    }
                    break;
                case 0x02:
                    if(select < 3){
                        select++;
                        flagMenu++;
                    }

                    break;
                case 0x10:
                    switch(select){
                        case 0:
                            //loadGame();
                            //game->status = 1;
                            clrscr();
                            flagMenu++;
                            break;
                        case 1:
                            loadOptions(game);
                            selectInOptions(game);
                            break;
                        case 2:
                            loadHowToPlay();
                            selectInCreditsAndHowToPlay();
                            loadMenu();
                            break;
                        case 3:
                            loadCredits();
                            selectInCreditsAndHowToPlay();
                            loadMenu();
                            break;
                    }
                    flagMenu++;
                    break;
                default: break;
            }
        }

    }
}

void loadOptions(gameHandler_t *game){
    clrscr();
    uint8_t x = 211, y = 56, firstboxY = 20, middlex = (211 - 1 )/2, i;
    box(1,1,x,y,1);

    char strDifficulty[11] = "          ";
    char strMode[7] = "LEVELS";

    for(i = 0; i <game->difficulty; i++)
        strDifficulty[i]='*';

    if(game->mode == 0){
        strMode[0] = 'E';
        strMode[1] = 'N';
        strMode[2] = 'D';
        strMode[3] = 'L';
        strMode[4] = 'E';
        strMode[5] = 'S';
    }

    boxWithTextInTheMiddleOfTheScreen(middlex, 5,"OPTIONS", 1);

    middlex=middlex/2;

    boxWithTextInTheMiddleOfTheScreen(middlex, firstboxY, "DIFFICULTY",1);
    boxWithTextInTheMiddleOfTheScreen(middlex, firstboxY+9, "MODE",1);
    middlex=105;
    boxWithTextInTheMiddleOfTheScreen(middlex, firstboxY+27, "BACK",1);

    middlex=middlex+middlex/2;
    boxWithTextInTheMiddleOfTheScreen(middlex, firstboxY, strDifficulty,1); //10
    boxWithTextInTheMiddleOfTheScreen(middlex, firstboxY+9, strMode,1);
}

void selectInOptions(gameHandler_t *game){
    uint8_t select=0, flagOptions=1 /*difficulty=5, mode=1*/;
    uint8_t op0v = 2, op1v = 105/2-16-10, op2v = 105-30+4;
    uint8_t op0h = 105-7, op1h = 105-16-15, op2h = 105+26-4;
    while(flagOptions == 1){

        if(flagOptions==1){

            //option 0: difficulty
            //option 1: mode
            //option 2: back
            switch(select){
                case 0:
                    //clear option 1
                    gotoxy(op1v,22+9);
                    renderLetter(' ');
                    gotoxy(op1h,22+9);
                    renderLetter(' ');

                    //move to option 0
                    gotoxy(op0v,22);
                    renderLetter('q');
                    gotoxy(op0h,22);
                    renderLetter('p');
                    flagOptions--;
                break;

                case 1:
                    //clear option 0
                    gotoxy(op0v,22);
                    renderLetter(' ');
                    gotoxy(op0h,22);
                    renderLetter(' ');

                    //clear option 2
                    gotoxy(op2v,22+27);
                    renderLetter(' ');
                    gotoxy(op2h,22+27);
                    renderLetter(' ');

                    //move to option 1
                    gotoxy(op1v,22+9);
                    renderLetter('q');
                    gotoxy(op1h,22+9);
                    renderLetter('p');
                    flagOptions--;
                break;

                case 2:
                    //clear option 1
                    gotoxy(op1v,22+9);
                    renderLetter(' ');
                    gotoxy(op1h,22+9);
                    renderLetter(' ');

                    //move to option 2:
                    gotoxy(op2v,22+27);
                    renderLetter('p');
                    gotoxy(op2h,22+27);
                    renderLetter('q');
                    flagOptions--;

                break;
            }
        }
        while(flagOptions==0){

            switch(readControls()){
                case 0x01:                  //w
                    if(select > 0){
                        select--;
                        flagOptions++;
                    }
                    break;

                case 0x02:                  //s
                    if(select < 2){
                        select++;
                        flagOptions++;
                    }
                    break;

                case 0x04:                  //a
                    if(select == 0){

                        if(game->difficulty > 1){
                            gotoxy(111+8*game->difficulty,22);
                            renderLetter(' ');
                            game->difficulty--;

                        }


                    }else if(select == 1){
                        gotoxy(135, 31);
                        if(game->mode == 1){
                            game->mode = 0;
                            renderWord("ENDLES");
                        }else if(game->mode == 0){
                            game->mode = 1;
                            renderWord("LEVELS");
                        }

                    }
                    break;

                case 0x08:                  //d
                    if(select == 0){

                        if(game->difficulty < 10){
                            game->difficulty++;
                            gotoxy(111+8*game->difficulty,22);
                                renderLetter('*');
                        }


                    }else if(select == 1){
                        gotoxy(135, 31);
                        if(game->mode == 1){
                            game->mode = 0;
                            renderWord("ENDLES");
                        }else if(game->mode == 0){
                            game->mode = 1;
                            renderWord("LEVELS");
                        }
                    }
                    break;

                case 0x10:                  //' '
                    if(select == 2){
                        loadMenu();
                        flagOptions+=2;
                    }
                    break;

                default: break;
            }
        }
    }
}

void loadHowToPlay(){
    uint8_t x = 211, y = 56, boxes=0, firstboxY = 20;
    clrscr();
    box(1,1,x,y,1);

    uint8_t middlex = (211 - 1 )/2; //105

    boxWithTextInTheMiddleOfTheScreen(middlex, 5,"HOW TO PLAY", 1);

    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY,"W MOVE FORWARD",1);
    boxes++;
    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY+boxes*9,"A AND D TURN",1);
    boxes++;
    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY+boxes*9,"SPACE TO SHOOT",1);
    boxes++;
    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY+boxes*9,"BACK",1);
}

void loadCredits(){
    uint8_t x = 211, y = 56, boxes=0, firstboxY = 20;
    clrscr();
    box(1,1,x,y,1);

    uint8_t middlex = (211 - 1 )/2; //105

    boxWithTextInTheMiddleOfTheScreen(middlex, 5,"THIS GAME WAS MADE BY", 1);

    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY,"THEODOR NORBY-LASSEN",1);
    boxes++;
    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY+boxes*9,"LEO UHRE JAKOBSEN",1);
    boxes++;
    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY+boxes*9,"JACOB HELLUM",1);
    boxes++;
    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY+boxes*9,"BACK",1);
}

void selectInCreditsAndHowToPlay(){
    uint8_t flagCredits =1;
    gotoxy(105-30+4,22+27);
    renderLetter('p');
    gotoxy(105+26-4,22+27);
    renderLetter('q');
    //kan dette gøres med en interrupt?

    while(flagCredits == 1){
        if(readControls() == 0x10)
            flagCredits--;
    }

}

void loadPause(){
    uint8_t x = 211, y = 56, firstboxY = 20;
    clrscr();
    box(1,1,x,y,1);

    uint8_t middlex = (211 - 1 )/2; //105

    boxWithTextInTheMiddleOfTheScreen(middlex, 5,"GAME PAUSED", 1);

    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY,"RESUME GAME",1);
    boxWithTextInTheMiddleOfTheScreen(middlex,firstboxY+2*9,"MAIN MENU",1);
}

void selectInPause(gameHandler_t *game){
    uint8_t select=0, flagPause=1;
    uint8_t op0v = 105-54, op1v = 105-46;
    uint8_t op0h = 105+50, op1h = 105+42;

    loadPause();

    while(flagPause == 1){

        if(flagPause==1){

            //option 0: difficulty
            //option 1: mode
            //option 2: back
            switch(select){
                case 0:
                    //clear option 1
                    gotoxy(op1v,22+18);
                    renderLetter(' ');
                    gotoxy(op1h,22+18);
                    renderLetter(' ');

                    //move to option 0
                    gotoxy(op0v,22);
                    renderLetter('q');
                    gotoxy(op0h,22);
                    renderLetter('p');
                    flagPause--;
                break;

                case 1:
                    //clear option 0
                    gotoxy(op0v,22);
                    renderLetter(' ');
                    gotoxy(op0h,22);
                    renderLetter(' ');

                    //move to option 1
                    gotoxy(op1v,22+18);
                    renderLetter('q');
                    gotoxy(op1h,22+18);
                    renderLetter('p');
                    flagPause--;
                break;
            }
        }
        while(flagPause==0){

            switch(readControls()){
                case 0x01:                  //w
                    if(select == 1){
                        select--;
                        flagPause++;
                    }
                    break;

                case 0x02:                  //s
                    if(select == 0){
                        select++;
                        flagPause++;
                    }
                    break;

                case 0x10:                  //' '
                    if(select == 0){
                        //loadMenu();
                        clrscr();

                    }else if(select == 1){ //go back to main menu
                        game->status = 0;
                        game->currentLevel = 0;
                    }
                    flagPause+=2;
                    break;

                case 0x20:                  //'p'
                    clrscr();
                    flagPause+=2;
                    break;

                default: break;
            }
        }
    }
}

void nextLevel(gameHandler_t *game){
    uint8_t nextLevelFlag = 1;
    clrscr();
    game->currentLevel++;
    game->status = 0;

    char str[] = "YOUR CURRENT LEVEL  ";
    str[19] = 64+game->currentLevel;    //converts 1,2,3... to A,B,C...

    boxWithTextInTheMiddleOfTheScreen(105, 22, str, 1);
    while(nextLevelFlag == 1){
        if(readControls() == 0x10){
            nextLevelFlag++;
            clrscr();
        }
    }

    //gotoxy(1,1);
    //printf("your current level is %d", game->currentLevel);
}

/*
void loadGame(){

    clrscr(); gotoxy(1,1); printf("Hello World");}*/
