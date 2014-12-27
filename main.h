#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>

#define NB_MAX_LITTS_PER_CLAUSE 3

typedef struct Litteral
{
	int valeurDeVerite;
	char purte;
}Litteral;

typedef struct Clause
{
	int valDesLit[NB_MAX_LITTS_PER_CLAUSE];
	int nbLits;
}Clause;


#endif


