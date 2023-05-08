#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

int initPlayers(int Players[2][7], int n);

void printTable(int Player1[7], int Player2[7], int who, int Case, int couleur);

int selectCasePlayer1(int Players[2][7], char PlayerName[30], int numPart, int couleur);

int selectCasePlayer2(int Players[2][7], char PlayerName[30], int numPart, int couleur);

int parcours(int j, int choice, int Players[2][7]);

int verifWin(int Players[7]);

int somme(int Player[7]);

int aleat(int MIN, int MAX);

#endif // ACTIONS_H_INCLUDED
