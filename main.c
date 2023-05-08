/*
Game: MANCALA

Authors:
    1. ADJAGBONI Celsin
    2. HOUNDONOUGBO Bill

CPPA
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "Game.h"

int main()
{
    //On change la couleur de l'arrière en blanc(7) et celle du
    //texte en noir (0)
    system("color  70");

    welcome();

    int run = 1;
    while(run)
    {
        //on debute le jeu grace a notre fonction play() qui se trouve
        //dans la bibliothèque Game.h
        play();

        do
        {
            printf("\n\nVoulez-vous rejouer? (0:Non / 1:Oui): ");
            scanf("%d", &run);
        }while(run<0 || run>1);
    }

    return 0;
}
