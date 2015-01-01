#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>

#define NB_MAX_LITTS_PER_CLAUSE 3

typedef struct elemListe
{
	int ID;
	struct elemListe *suivant;
}elemListe;

typedef struct Litteral
{
	int IDLitteral;
	char purete;
	elemListe *teteListeClauses;
	struct Litteral *suivant;
}Litteral;

typedef struct Clause
{
	int IDClause; //Qui sera son indice initial et vaut -1 si clause est supprimée
	elemListe *teteListeLitteraux;
	int nbLitteraux;
	struct Clause *suivant; //Pour la gestion de collision avec un chainage
}Clause;

typedef struct Formule
{
	int nbClauses;
	int nbLitteraux;
	int tailleTabClauses;
	int tailleTabLitteraux;
	Clause **tabClauses;
	Litteral **tabLitteraux;
}Formule;

typedef struct Pile
{
	int litteral;
	int valeurDeVertier;
}Pile;

#endif


