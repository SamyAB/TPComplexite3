#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>

typedef struct Litteral
{
	int num;
	int valeurDeVerite;
	char purte;
}Litteral;

typedef struct Clause
{
	Litteral **teteLits;
	int nbLits;
}Clause;


#endif


