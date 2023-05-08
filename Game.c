#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#include "Game.h"
#include "Actions.h"
#include "Gotoxy.h"

//variable stockant les points des joueurs
static int PlayersPoint[2] = {0, 0};

//FONCTION ACTIVANT LE JEU
void game(int modeChoice, char PlayersNames[2][30], int numPart, int couleur[2], int partSelect, int totalTour)
{
    system("cls");

    //Creation des joueurs
    int Players[2][7];

    //choix nombre de pions
    int choicePion;
    printf("\n\tVoulez-vous choisir le nombre pions ou le laisser a 4?\n\n");
    printf("1. Choisir.. \n2. Laisser a 4\n\n");
    do
    {
        printf("Faites le choix (1 - 2): ");
        scanf("%d", &choicePion);
    }while(choicePion<1 || choicePion>2);

    if(choicePion == 2)
    {
        initPlayers(Players, 4);
        system("cls");
    }

    else
    {
        int n;
        printf("\n\nEntrer le nombre de pions: ");
        scanf("%d", &n);
        initPlayers(Players, n);
        system("cls");
    }

    int i, j, Case=0;

    //AFFICHAGE DE LA TABLE DE JEU
    printf("Partie %d\n\n", numPart);
    printTable(Players[0], Players[1], 0, Case, couleur[0]); //fonction se trouvant dans "Actions.h"

    int choice, run=1, replay=0;
    int win1, win2;

    //DEBUT DU JEU
    while(run)
    {
        j=0; //Variable designant l'indice du joueur

        //Boucle permettant de switcher entre le Joueur 1 et le Joueur 2
        for(j=0; j<2; j++)
        {
            do //boucle permettant de rejouer si le dernier pion tombe dans le grenier
            {

                //On verifie si toutes les cases d'un joueurs sont vides
                win1 = verifWin(Players[0]);
                win2 = verifWin(Players[1]);

                //verifWin() est une fonction de la bibliothèque Actions.h

                if(win1 || win2) //si l'un des joueurs n'a plus de pions dans ses cases
                {
                    if(win1)
                        Players[0][6] += somme(Players[1]); //Players[0][6] designe le grenier du joueur 1
                    else if(win2)
                        Players[1][6] += somme(Players[0]); //Players[0][6] designe le grenier du joueur 2

                    system("cls");
                    Case = 0;
                    printf("Partie %d\n\n", numPart);
                    printTable(Players[0], Players[1], 0, Case, couleur[0]); //on refait un affichage en tenant compte des modifs

                    run =  0; //on arrette le jeu
                    break;
                }

                if(modeChoice == 2 && j==1)//si on joue contre l'ia et que c'est a son tour
                {

                    do
                    {
                        choice = aleat(1, 6);
                    }while(Players[j][choice-1] == 0); //l'ia ne choisira donc jamais de case vide

                    printf("\n\n\n\nL'Intelligence Artificielle a choisi sa case %d \n", choice);

                    system("pause");
                    choice--;

                }

                else //sinon on demande au joueur de jouer
                {
                    if(j==0)
                        choice = selectCasePlayer1(Players, PlayersNames[0], numPart, couleur[0]);
                    else
                        choice = selectCasePlayer2(Players, PlayersNames[1], numPart, couleur[1]);

                    //selectCasePlayer sont des fonctions de la bibliotheque "Actions.h"

                    //if(choice != 6)
                    while(Players[j][choice] == 0)
                    {
                        printf("\n\n\n\nErreur, vous ne pouvez pas choisir une case vide ");
                        if(j==0)
                            choice = selectCasePlayer1(Players, PlayersNames[0], numPart, couleur[0]);
                        else
                            choice = selectCasePlayer1(Players, PlayersNames[0], numPart, couleur[1]);
                    }

                }


                //on fait les ajouts grace a la fonction parcours() se trouvant dans "Actions.h"
                //cette fonction retourne 1 si dernier pion depose se trouve dans le grenier du joueur actif
                //on recupere donc cette valeur dans la variable replay
                replay = parcours(j, choice, Players);

                system("cls");
                Case = 0;
                printf("Partie %d\n\n", numPart);

                if(replay)
                    printTable(Players[0], Players[1], j, Case, couleur[j]);
                else
                    switch(j)
                    {
                        case 0: printTable(Players[0], Players[1], 1, Case, couleur[1]); break;
                        case 1: printTable(Players[0], Players[1], 0, Case, couleur[0]); break;
                    }

            }while(replay); //tant que le dernier pion tombe dans le grenier du joueur actif

        }

        if(partSelect == 3)
        {
                gotoxy(17, 17);
                printf("\nIl vous reste %d tours\n", totalTour-1);
                totalTour--;
                if(totalTour<=0)
                    run =0;
        }
    }

    //DETERMINATION DU GAGNANT
    if(Players[0][6] > Players[1][6]) //si joueur 1 a plus de pions dans son grenier que joueur 2
    {
        printf("\n\n\n\n%s a gagne la partie\n\n", PlayersNames[0]);
        PlayersPoint[0]++;
    }

    else if(Players[0][6] == Players[1][6])
    {
        printf("\n\n\n\nVous etes a egaliter\n\n");
        PlayersPoint[0]++;
        PlayersPoint[1]++;
    }

    else
    {
        switch(modeChoice)
        {
            case 1: printf("\n\n\n\n%s a gagne la partie\n\n", PlayersNames[1]); break;
            case 2: printf("\n\n\n\nL'Intelligence artificielle a gagne la partie\n\n"); break;
        }
        PlayersPoint[1]++;
    }

    system("pause");

}

//FONCTION QUI AFFICHE LE MENU PUIS INTRODUIT LE JEU
void play()
{
    int  modeChoice, totalPart, numPart, totalTour;
    char PlayersNames[2][30];

    //printf("\t*MANCALA*\n");

    printf("\n\n\nMODES DE JEU");
    printf("\n\n\t1. Mode 2 Joueurs \n\t2. Mode 1 Joueur VS l'IA");
    do
    {
        printf("\n\nChoisissez votre mode de jeu svp (1 - 2): ");
        scanf("%d", &modeChoice);
    }while(modeChoice<1 || modeChoice>2);

    system("cls");
    printf("\t*MANCALA*\n");

    switch(modeChoice)
    {
        case 1: printf("\n\n***MODE 2 JOUEURS***"); break;
        case 2: printf("\n\n***MODE JOUEUR vs IA***"); break;
    }


    printf("\n\nTYPE DE PARTIE");
    printf("\n\n\t1. Partie Unique \n\t2. Plusieurs Parties \n\t3. Partie Nombre de Tours limite");
    do
    {
        printf("\n\nChoisissez votre type de partie svp (1 - 2): ");
        scanf("%d", &numPart);
    }while(numPart<1 || numPart>3);

    if(numPart == 1)
        totalPart = 1;
    else if(numPart == 2)
    {
        printf("\n\nEntrez le nombre de partie que vous souhaitez jouer: ");
        scanf("%d", &totalPart);
    }
    else
    {
        totalPart = 1;
        printf("\n\nLe nombre de tour designe le nombre de fois ou chaque joueur peut faire un tour. \nLorsqu'un pion tombe dans le grenier, on ne compte pas le tour bonus");
        printf("\n\nEntrez le nombre de tours que vous souhaitez effectuer: ");
        scanf("%d", &totalTour);
    }


    //demande des noms
    printf("\nEntrez le nom du Joueur 1: ");
    scanf("%s", PlayersNames[0]);

    if(modeChoice == 1)
    {
        printf("Entrez le nom du Joueur 2: ");
        scanf("%s", PlayersNames[1]);
    }


    //demande des couleurs
    int couleur[2], numColor;
    system("cls");
    printf("\n\nCHOIX DES COULEURS");
    printf("\n\n\t1. Bleu \n\t2. Vert");
    do
    {
        printf("\n\n%s, choisissez une couleur svp (1 - 2): ", PlayersNames[0]);
        scanf("%d", &numColor);
    }while(numColor<1 || numColor>2);

    if(numColor == 1)
    {
        couleur[0] = 9; //9->bleu
        couleur[1] = 2; //2->vert
    }
    else
    {
        couleur[0] = 2;
        couleur[1] = 9;
    }


    system("cls");
    printf("\n\n%s, vous etes a la ligne 1. \nVotre Grenier se trouve a gauche.\n\n", PlayersNames[0]);

    switch(modeChoice){
        case 1:
            { printf("\n\n%s, vous etes a la ligne 2. \nVotre Grenier se trouve a droite.\n\n", PlayersNames[1]); system("pause"); break;}
        case 2:
            { printf("\n\nL'IA est a la ligne 2. \nSon Grenier se trouve a droite.\n\n"); system("pause"); break; } }

    printf("\n\nNB: Vous n'avez pas le droit de deplacer les pions contenus dans les greniers");
    printf("\n\nVous pouvez enfin jouer!!\n\n\n");
    system("pause");

    for(int i=1; i<=totalPart; i++)
        game(modeChoice, PlayersNames, i, couleur, numPart, totalTour);

    //AFFICHAGE DU NOMBRE DE POINTS
    printf("\n\n%s: %d Points", PlayersNames[0], PlayersPoint[0]);
    switch(modeChoice)
    {
        case 1: printf("\n%s: %d Points", PlayersNames[1], PlayersPoint[1]); break;
        case 2: printf("\nIA: %d Points", PlayersPoint[1]); break;
    }
}


void welcome()
{
    char tab[] = "*****WELCOME TO THE MANCALA*****";
    int taille = strlen(tab);

    for(int i=0; i<taille; i++)
    {
        //system("cls");
        gotoxy(8+i, 1); printf("%c", tab[i]);
        Sleep(150);
    }

}
