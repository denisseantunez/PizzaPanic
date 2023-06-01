
#include "Game.h"

/*******************************************************************************************************************************************************************/

void Game::MakeArray() {
    for (int i = 0; i <= 34; ++i){
        if (i/3 == 0) PosicionesItem[1][i] = AlturaInicial;
        else if (i/3 == 1) PosicionesItem[1][i] = AlturaInicial - 385;
        else if (i/3 == 2) PosicionesItem[1][i] = AlturaInicial - (385*2);
        else if (i/3 == 3) PosicionesItem[1][i] = AlturaInicial - (385*3);
        else if (i/13 < 1) PosicionesItem[1][i] = AlturaInicial - (385*3);
        else if (i/18 < 1) PosicionesItem[1][i] = AlturaInicial - (385*4);
        else if (i/25 < 1) PosicionesItem[1][i] = AlturaInicial - (385*5);
        else if (i/35 < 1) PosicionesItem[1][i] = AlturaInicial - (385*6);
    }

    for(int i = 0; i <= 6; i+=3){
        PosicionesItem[0][i] = 1045;
        PosicionesItem[0][i+1] = 660;
        PosicionesItem[0][i+2] = 325;
    }

    PosicionesItem[0][9] = 1380;
    PosicionesItem[0][10] = 1045;
    PosicionesItem[0][11] = 660;
    PosicionesItem[0][12] = 325;
    PosicionesItem[0][13] = 1770;
    PosicionesItem[0][14] = 1380;
    PosicionesItem[0][15] = 1045;
    PosicionesItem[0][16] = 660;
    PosicionesItem[0][17] = 325;
    PosicionesItem[0][18] = 2480;
    PosicionesItem[0][19] = 2150;
    PosicionesItem[0][20] = 1770;
    PosicionesItem[0][21] = 1380;
    PosicionesItem[0][22] = 1045;
    PosicionesItem[0][23] = 660;
    PosicionesItem[0][24] = 325;
    PosicionesItem[0][25] = 3160;
    PosicionesItem[0][26] = 2870;
    PosicionesItem[0][27] = 2480;
    PosicionesItem[0][28] = 2150;
    PosicionesItem[0][29] = 1770;
    PosicionesItem[0][30] = 1380;
    PosicionesItem[0][31] = 1045;
    PosicionesItem[0][32] = 660;
    PosicionesItem[0][33] = 325;
    PosicionesItem[0][34] = 80;
}

/*******************************************************************************************************************************************************************/