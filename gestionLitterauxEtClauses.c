#include "main.h"

int ajouterLitteral(Clause **clause,int valeurLitteral)
{
	elemListe *tmp=NULL;
	if(clause->teteListeLitteraux==NULL)//Pas encore d'élément dans la liste de litteraux de cette clause
	{
		if(clause->nbLitteraux)
		{
			fprintf(stderr,"Erreur: la tête de la liste des litteraux est NULL alors que le nombre de litteraux est différent de 0\n");
			return -1;
		}
		clause->teteListeLitteraux=(elemListe*)malloc(sizeof(elemListe));
		if(clause->teteListeLitteraux==NULL)
		{
			fprintf(stderr,"Erreur : impossible d'allouer la tête de la liste des littéraux de la clause\n");
			return -1;
		}
		clause->teteListeLitteraux->ID=valeurLitteral;
		clause->teteListeLitteraux->suivant=NULL;
	}
	else //Il y a au moins un élément dans liste des littéraux de la clause
	{
		tmp=clause->teteListeLitteraux;
		while(tmp->suivant!=NULL)// Avancer jusqu'au dernier élément de la liste
		{
			tmp=tmp->suivant;
		}
		tmp->suivant=(elemListe*)malloc(sizeof(elemListe));
		if(tmp->suivant==NULL)
		{
			fprintf(stderr,"Erreur : impossible d'allouer un élément de la liste des littéraux de la clause\n");
			return -1;
		}
		tmp->suivant->ID=valeurLitteral;
		tmp->suivant->suivant=NULL;
	}
	clause->nbLitteraux++;
	return 0;
}

void affichageClauses(Clause **tabClauses,int tailleTabClauses)
{
	int i;
	elemListe *tmp;
	Clause *tmpClause;
	printf("nombre de clauses : %d\n",nbClauses);
	for(i=0;i<tailleTabClauses;i++)
	{
		tmpClause=tabClause[i];
		while(tmpClause!=NULL)
		{
			tmp=tmpClause->tete;
			printf("clause %d : ",i);
			while(tmp!=NULL)
			{
				printf("%d ",tmp->litteral);
				tmp=tmp->suivant;
			}
			printf("\n");
			tmpClause=tmpClause->suivant;
		}
	}
}

	
