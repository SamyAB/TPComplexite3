#include "main.h"

int ajouterLitteral(Clause *clause,int valeurLitteral)
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
	printf("nombre de clauses : %d\n",tailleTabClauses);
	for(i=0;i<tailleTabClauses;i++)
	{
		tmpClause=tabClauses[i];
		while(tmpClause!=NULL)
		{
			tmp=tmpClause->teteListeLitteraux;
			printf("clause %d : ",i);
			while(tmp!=NULL)
			{
				printf("%d ",tmp->ID);
				tmp=tmp->suivant;
			}
			printf("\n");
			tmpClause=tmpClause->suivant;
		}
	}
}

int existeClauseVide(Formule *f)
{
	//Déclaration de variables
	Clause *tmp;
	int i;
	
	//parcourt des clause de f à la recherche de clause vide
	for(i=0;i<f->tailleTabClauses;i++)
	{
		tmp=f->tabClauses[i];
		while(tmp!=NULL)
		{
			if(!tmp->nbLitteraux) //Si il y a une clause vide, on retourne 1
			{
				return 1;
			}
			tmp=tmp->suivant;
		}
	} 
	return 0;
}

Litteral* getLitteral(Formule *f,int ID)
{
	//Déclaration de variables
	Litteral *tmpLitteral=NULL;
	
	return tmpLitteral;
}

Clause* getClause(Formule *f,int ID)
{
	//Déclaration de variables
	Clause *tmpClause=NULL;
	
	return tmpClause;
}

Formule* supprimerClause(Formule* f,Clause *clause)
{
	return f;
}

Formule* supprimerLitteralDeClause(Formule* f,Clause *clause,int positionDansClause)
{
	/* REMARAUE :
	 * Les poistion dans clause commencent a partir de 0*/
	 
	 
	 return f;
}

Formule* supprimerLitteralPur(Formule *f,Litteral* litteral)
{
	/* REMARQUE :
	 * Contient la suppression des clauses conteant ce litteral
	 */
	 
	 return f; 
}


