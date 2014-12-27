#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>

typedef struct Literal
{
	int num;
	int valeurDeVerite;
	char purte;
}Literal;

typedef struct Clause
{
	Literal **teteLits;
	int nbLits;
}Clause;


#endif


