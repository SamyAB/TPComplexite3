#include "main.h"

int ajouterLitteral(Clause *clause,int valeurLitteral)
{
	elemListeLitteraux *tmp=NULL;
	if(clause->tete==NULL)//Pas encore d'élément dans la liste de litteraux de cette clause
	{
		if(clause->nbLitteraux)
		{
			fprintf(stderr,"Erreur: la tête de la liste des litteraux est NULL alors que le nombre de litteraux est différent de 0\n");
			return -1;
		}
		clause->tete=(elemListeLitteraux*)malloc(sizeof(elemListeLitteraux));
		if(clause->tete==NULL)
		{
			fprintf(stderr,"Erreur : impossible d'allouer la tête de la liste des littéraux de la clause\n");
			return -1;
		}
		clause->tete->litteral=valeurLitteral;
		clause->tete->suivant=NULL;
	}
	else //Il y a au moins un élément dans liste des littéraux de la clause
	{
		tmp=clause->tete;
		while(tmp->suivant!=NULL)// Avancer jusqu'au dernier élément de la liste
		{
			tmp=tmp->suivant;
		}
		tmp->suivant=(elemListeLitteraux*)malloc(sizeof(elemListeLitteraux));
		if(tmp->suivant==NULL)
		{
			fprintf(stderr,"Erreur : impossible d'allouer un élément de la liste des littéraux de la clause\n");
			return -1;
		}
		tmp->suivant->litteral=valeurLitteral;
		tmp->suivant->suivant=NULL;
	}
	clause->nbLitteraux++;
	return 0;
}

void affichageClauses(Clause *tabClauses,int nbClauses)
{
	int i;
	elemListeLitteraux *tmp;
	printf("nombre de clauses : %d\n",nbClauses);
	for(i=0;i<nbClauses;i++)
	{
		tmp=tabClauses[i].tete;
		printf("clause %d : ",i);
		while(tmp!=NULL)
		{
			printf("%d ",tmp->litteral);
			tmp=tmp->suivant;
		}
		printf("\n");
	}
}	
