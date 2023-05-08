#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "Gotoxy.h"
#include "Actions.h"


#define LEFT 75
#define RIGHT 77
#define ENTER 13


//FONCTION INITIALISANT LES CASES DES JOUEURS
int initPlayers(int Players[2][7], int n)
{
    int i, j;
    for(i=0; i<2; i++)
    {
        for(j=0; j<7; j++)
        {
            if(j == 6)
                Players[i][j] = 0;
            else
                Players[i][j] = n;
        }
    }
}


//FONCTION AFFICHANT LA TABLE CONTENANT LES PIONS
void printTable(int Player1[7], int Player2[7], int who, int Case, int couleur)
{
    int i, j, k;

    /*---------------------------------ETOILES-------------------------------*/

    //LIGNES HORIZONTALES

    i=2; //car la première ligne qu'on veut afficher a pour ordonnee 2
    while(i<=14) //car la derniere ligne qu'on veut afficher a pour ordonnee 14
    {
        gotoxy(16, i);
        for(j=0; j<49; j++) //49=nombre d'etoiles a afficher
            printf("*");

        i+=12;
    }

    i=6; //car la première ligne qu'on veut afficher a pour ordonnee 6
    while(i<=10) //car la derniere ligne qu'on veut afficher a pour ordonnee 10
    {
        gotoxy(8, i);
        for(j=0; j<65; j++) //65=nombre d'etoiles a afficher
            printf("*");

        i+=4;
    }

    //LIGNES VERTICALES

    i=8; //car la première ligne qu'on veut afficher a pour abscisse 8
    while(i<=72) //car la derniere ligne qu'on veut afficher a pour abscisse 72
    {
        gotoxy(i, 6);
        for(j=0; j<5; j++) //5=nombre d'etoiles a afficher
        {
            gotoxy(i, 6+j);
            printf("*");
        }
        i+=64;
    }

    i=24;
    while(i<=56)
    {
        for(j=0; j<5; j++)
        {
            gotoxy(i, 2+j);
            printf("*");
        }

        for(j=0; j<5; j++)
        {
            gotoxy(i, 10+j);
            printf("*");
        }

        i+=8;
    }

    i=16; //car la première ligne qu'on veut afficher a pour abscisse 16
    while(i<=64) //car la derniere ligne qu'on veut afficher a pour abscisse 64
    {
        for(j=0; j<13; j++)
        {
            gotoxy(i, 2+j);
            printf("*");
        }
        i+=48;
    }

    /*-----------------------POSSIBILITY-------------------------*/


    int n, initial;
    //possibility est la variable qui va contenir l'indice de la case finale
    int possibility = Case;

    //initial contient l'indice du joueur actif
    initial = who;

    //j va varier selon le parcours et les ajouts des pions
    j=who;

    //l'objectif etant de faire des verifications sans avoir à modifier la valeur de la variable who.
    //Recuperation du nombre de pions qu'il y a dans la case selectionnee
    if(who==0)
        n = Player1[Case];
    else
        n = Player2[Case];

    //determination de la case finale
    for(i=1; i<=n; i++)
    {
        possibility += 1;

        if(possibility > 6)
        {
            possibility = 0;
            //changement de joueur
            if(j==0)
                j=1;
            else
                j=0;
        }

        if(j != initial && possibility == 6) //si on se retrouve dans le grenier du joueur adverse
        {
            n++;
        }
    }

    /*-----------------------------------PIONS-----------------------------------*/

    //AFFICHAGE DES PIONS

    /*------GRENIER JOUEUR 1------*/
    gotoxy(12, 8); //centre du grenier du joueur 1
    if(j == 0 && possibility == 6) //si la case finale est le grenier du joueur 1, on colorie en vert
        { color(2,7); printf("%d", Player1[6]); color(0,7); }

    else
        { color(0,7); printf("%d", Player1[6]); }


    /*------AFFICHAGE DE LA LIGNE DU JOUEUR 1------*/
    k=5;
    for(i=20; i<=60; i+=8)
    {
        gotoxy(i, 4);
        if(who == 0 && Case == k) //si la case choisie est k, on colorie en "couleur"
        {
            color(0,couleur);
            printf("%d", Player1[k]);
            color(0,7);
        }

        else if(j==0 && initial==0 && possibility == k && Player1[possibility] == 0) //si possibility se trouve toujours sur la ligne du joueur 1
        { //et s'il ne reste plus aucun pion dans cette case
            color(2,7); //on l'affiche en vert
            printf("%d", Player1[k]);
            color(0,7);
        }

        else if(j == 0 && possibility == k) //si la case finale est k, on colorie en rouge
        {
            color(4,7);
            printf("%d", Player1[k]);
            color(0,7);
        }

        else //sinon on affiche toutes les autres cases normalement
        {
            color(0,7);
            printf("%d", Player1[k]);
        }

        k--;
    }

    /*------GRENIER JOUEUR 2------*/
    gotoxy(68, 8);
    if(j == 1 && possibility == 6) //si la case finale est le grenier du joueur 2, on colorie en vert
    {
        color(2,7);
        printf("%d", Player2[6]);
        color(0,7);
    }
    else
    {
        color(0,7);
        printf("%d", Player2[6]);
    }


    /*------AFFICHAGE DE LA LIGNE DU JOUEUR 2------*/
    k=0;
    for(i=20; i<=60; i+=8) //affichage de la ligne du Joueur 2
    {
        gotoxy(i, 12);
        if(who == 1 && Case == k) //si la case choisie est k, on colorie en "couleur"
        {
            color(0,couleur);
            printf("%d", Player2[k]);
            color(0,7);
        }

        else if(j==1 && initial==1 && possibility == k && Player2[possibility] == 0) //si possibility se trouve toujours sur la ligne du joueur 1
        { //et s'il ne reste plus aucun pion dans cette case
            color(2,7); //on l'affiche en vert
            printf("%d", Player2[k]);
            color(0,7);
        }

        else if(j == 1 && possibility == k) //si la case finale est k, on colorie en rouge
        {
            color(4,7);
            printf("%d", Player2[k]);
            color(0,7);
        }

        else //sinon on affiche toutes les autres cases normalement
        {
            color(0,7);
            printf("%d", Player2[k]);
        }
        k++;
    }

}


//FONCTION PERMETTANT DE SELECTIONNER UNE CASE DU JOUEUR 2
int selectCasePlayer2(int Players[2][7], char PlayerName[30], int numPart, int couleur)
{
    int ch, Case=0;
    printf("\n\n\n\n%s, a vous de jouer... ", PlayerName);
    ch = getch(); //on recupere la touche appuye sur le clavier

    while(ch != ENTER)
    {
        if(ch == RIGHT)
        {
            if(Case<5)
            {
                Case++;
                system("cls");
                printf("Partie %d\n\n", numPart);
                printTable(Players[0], Players[1], 1, Case, couleur);
                printf("\n\n\n\n%s, a vous de jouer... ", PlayerName);
            }
        }

        if(ch == LEFT)
        {
            if(Case>0)
            {
                Case--;
                system("cls");
                printf("Partie %d\n\n", numPart);
                printTable(Players[0], Players[1], 1, Case, couleur);
                printf("\n\n\n\n%s, a vous de jouer... ", PlayerName);
            }
        }

        ch = getch();
    }

    return Case;
}


//FONCTION PERMETTANT DE SELECTIONNER UNE CASE DU JOUEUR 1
int selectCasePlayer1(int Players[2][7], char PlayerName[30], int numPart, int couleur)
{
    int ch, Case=0;
    printf("\n\n\n\n%s, a vous de jouer... ", PlayerName);
    ch = getch(); //on recupere la touche appuye sur le clavier

    while(ch != ENTER)
    {
        if(ch == RIGHT)
        {
            if(Case>0)
            {
                Case--;
                system("cls");
                printf("Partie %d\n\n", numPart);
                printTable(Players[0], Players[1], 0, Case, couleur);
                printf("\n\n\n\n%s, a vous de jouer... ", PlayerName);
            }
        }

        if(ch == LEFT)
        {
            if(Case<5)
            {
                Case++;
                system("cls");
                printf("Partie %d\n\n", numPart);
                printTable(Players[0], Players[1], 0, Case, couleur);
                printf("\n\n\n\n%s, a vous de jouer... ", PlayerName);
            }
        }

        ch = getch();
    }

    return Case;
}



//FONCTION AJOUTANT LES PIONS AUX CASES DURANT LE JEU
int parcours(int j, int choice, int Players[2][7])
{
    int n, k, initial;

    initial = j; //indice du joueur actif
    n = Players[j][choice]; //nombre de pions contenus dans la case selectionnee
    Players[j][choice] = 0; //on met les pions de la case en question a 0

    int i;
    for(i=1; i<=n; i++)
    {
        choice += 1;

        if(choice > 6)
        {
            choice = 0;
            //changement de joueur
            if(j==0)
                j=1;
            else
                j=0;
        }

        if(j != initial && choice == 6) //si on se retrouve dans le grenier du joueur adverse
        {
            n++;
        }
        else
            Players[j][choice]++; //on ajoute 1 pion
    }

    if(j==initial && choice==6)//si le dernier pion tombe dans le grenier du joueur
        return 1;
    else
    {
        if(j==initial) //si l'on se trouve toujours sur la ligne du joueur actif
        {
            if(Players[j][choice] == 1) //s'il ne reste qu'un seul pion dans cette case
            {
                //identification du joueur adverse
                if(j==0)
                    k=1;
                else
                    k=0;

                //collecte des pions de la case opposée
                Players[j][6] += Players[k][5-choice]; //5-choice correspond a l'indice de la case en face
                Players[k][5-choice] = 0;
            }
        }

        return 0;
    }
}


//FONCTION VERIFIANT SI UN JOUEUR NE POSSEDE PLUS DE PIONS DANS SES CASES
int verifWin(int Players[7])
{
    int i, win=1; //on suppose que le joueur a gagne (toutes ses cases sont vides)
    for(i=0; i<6; i++)
    {
        if(Players[i] != 0)
            win = 0; //donc la supposition est fausse
    }

    return win;
}


int somme(int Player[7])
{
    int i, result=0;
    for(i=0; i<6; i++)
    {
        result += Player[i];
        Player[i] = 0;
    }

    return result;
}


//FONCTION RETOURNANT UN NOMBRE AU HASARD COMPRIS ENTRE min et max
int aleat(int MIN, int MAX)
{
    srand(time(NULL));
    int aleatNumber = (rand() % (MAX - MIN +1)) + MIN;

    return aleatNumber;
}
