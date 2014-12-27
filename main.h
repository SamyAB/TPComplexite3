#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>

#define NB_MAX_LITTS_PER_CLAUSE 3

typedef struct Litteral
{
	int valeurDeVerite;
	char purte;
	//Je pourrais rajouter une ligne de clause a voir...
}Litteral;

typedef struct elemListeLitteraux
{
	int litteral;
	struct elemListeLitteraux *suivant;
}elemListeLitteraux;

typedef struct Clause
{
	elemListeLitteraux *tete;
	int nbLitteraux;
}Clause;




#endif


