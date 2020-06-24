#include "menuScreen.h"

#define CLIP_SIZE 5

void gameInit(gameHandler_t *game){
    //resets the games attributes
    game->difficulty = 5;
    game->mode = 1;
    game->currentLevel = 0;
    game->currentScore = 0;
    game->status = 0;
}

void loadMenu(){ //draws the menu

    uint8_t boxes=0;
    clrscr();

    box(1,1,SCREEN_WIDTH,SCREEN_HEIGHT,1);

    boxWithTextCenterAligned(MIDDLE_OF_SCREEN, 5,"RUNAWAY:THE GAME", 1);

    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX,"START",1);
    boxes++;
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX+boxes*9,"OPTIONS",1);
    boxes++;
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX+boxes*9,"HOW TO PLAY",1);
    boxes++;
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX+boxes*9,"CREDITS",1);
    boxes++;
}

void selectInMenu(gameHandler_t *game){
    uint8_t select=0, flagMenu=1;
    uint8_t op0xv = 105-30, op1xv = 105-38, op2xv = 105-38-16, op3xv = 105-38;
    uint8_t op0xh = 105+26, op1xh = 105+34, op2xh = 105+34+16, op3xh = 105+34;
    loadMenu();

while(flagMenu==1){

    if(flagMenu==1){
        switch(select){ //draws arrows pointing at the selected option
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

        while(flagMenu==0){ //loops until it recieves a valid user input
            switch(readControls()){
               case 0x01:   //w
                    if(select > 0){
                        select--;
                        flagMenu++;
                    }
                    break;
                case 0x02:  //s
                    if(select < 3){
                        select++;
                        flagMenu++;
                    }

                    break;
                case 0x10:  //
                    switch(select){
                        case 0:
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

void loadOptions(gameHandler_t *game){ //draws the options
    clrscr();
    uint8_t i;
    box(1,1,SCREEN_WIDTH,SCREEN_HEIGHT,1);

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

    boxWithTextCenterAligned(MIDDLE_OF_SCREEN, 5,"OPTIONS", 1);
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN/2, Y_OF_FIRST_BOX, "DIFFICULTY",1);
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN/2, Y_OF_FIRST_BOX+9, "MODE",1);
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN, Y_OF_FIRST_BOX+27, "BACK",1);
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN+MIDDLE_OF_SCREEN/2, Y_OF_FIRST_BOX, strDifficulty,1); //10
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN+MIDDLE_OF_SCREEN/2, Y_OF_FIRST_BOX+9, strMode,1);
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

                case 0x10:              //' '
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

void loadHowToPlay(){   //draws the how to play section
    uint8_t boxes=-1;
    clrscr();
    box(1,1,SCREEN_WIDTH,SCREEN_HEIGHT,1);
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN, 2,"POTMETERS:NUKE AIM", 1);

    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX+boxes*9,"W:MOVE FORWARD",1);
    boxes++;
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX,"Q AND E:AIM",1);
    boxes++;
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX+boxes*9,"A AND D:TURN",1);
    boxes++;
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX+boxes*9,"SPACE:SHOOT",1);
    boxes++;
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX+boxes*9,"BACK",1);
}

void loadCredits(){     //draws the credits
    uint8_t boxes=0;
    clrscr();
    box(1,1,SCREEN_WIDTH,SCREEN_HEIGHT,1);

    boxWithTextCenterAligned(MIDDLE_OF_SCREEN, 5,"THIS GAME WAS MADE BY", 1);
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX,"THEODOR NORBY-LASSEN",1);
    boxes++;
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX+boxes*9,"LEO UHRE JAKOBSEN",1);
    boxes++;
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX+boxes*9,"JACOB HELLUM",1);
    boxes++;
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX+boxes*9,"BACK",1);
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

void loadPause(){       //draws the pause screen
    clrscr();
    box(1,1,SCREEN_WIDTH,SCREEN_HEIGHT,1);
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN, 5,"GAME PAUSED", 1);
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX,"RESUME GAME",1);
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX+2*9,"MAIN MENU",1);
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
                    box(1,1,SCREEN_WIDTH,SCREEN_HEIGHT,1);
                    break;

                case 0x20:                  //'p'
                    clrscr();
                    flagPause+=2;
                    box(1,1,SCREEN_WIDTH,SCREEN_HEIGHT,1);
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

    boxWithTextCenterAligned(MIDDLE_OF_SCREEN, Y_OF_FIRST_BOX+2, str, 1);
    while(nextLevelFlag == 1){
        if(readControls() == 0x10){
            nextLevelFlag++;
            clrscr();
        }
    }
    box(1,1,SCREEN_WIDTH,SCREEN_HEIGHT,1);
}

void gameOver(gameHandler_t *game){

    uint8_t gameOverFlag = 1;

    clrscr();
    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX,"GAME OVER",1);

    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX+9,"PRESS P TO RETURN TO",1);

    boxWithTextCenterAligned(MIDDLE_OF_SCREEN,Y_OF_FIRST_BOX+2*9,"MAIN MENU",1);

    while(gameOverFlag){
        if(readControls() == 0x20){
            gameOverFlag--;
            clrscr();
        }
    }
    game->status = 0;
    game->currentLevel = 0;
}

void levelInit(gameHandler_t *game, spaceship_t *sh, nuke_t *n, homing_t *h, uint8_t *numEnemies, enemy_t *enemies, powerup_t *powerups, enemyBullet_t *enemyBullets, bullet_t *playerBullet){
    uint8_t i;
    if(game->currentLevel==0){
                spaceship_init(sh, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                gameInit(game);
                selectInMenu(game);
                nextLevel(game);
            }
            sh->bullet_type = 0;
            n->alive = 0;
            h->alive = 0;


            *numEnemies = game->currentLevel + (game->difficulty/2);

	        for (i = 0; i < CLIP_SIZE; i++) {
                playerBullet[i].alive = 0;
            }

            for (i = 0; i < *numEnemies; i++) {
                enemy_init(&enemies[i], 2 + (rand() % SCREEN_WIDTH-10), 2 + (rand() % SCREEN_HEIGHT-10), &enemyBullets[i], 3);
            }


            for (i = 0; i < 5; i++) {
                powerups[i].alive = 0;
            }
}
