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
			printf("clause %d : ",tmpClause->IDClause);
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

void affichageLitteraux(Litteral **tabLitteraux,int tailleTabLitteraux)
{
	int i;
	elemListe *tmp;
	Litteral *tmpLitteral;
	printf("nombre de litteraux : %d\n",tailleTabLitteraux);
	for(i=0;i<tailleTabLitteraux;i++)
	{
		tmpLitteral=tabLitteraux[i];
		while(tmpLitteral!=NULL)
		{
			tmp=tmpLitteral->teteListeClauses;
			printf("Litteral %d à ",i+1);
			printf("pureté %c : ",tmpLitteral->purete);
			while(tmp!=NULL)
			{
				printf("%d ",tmp->ID);
				tmp=tmp->suivant;
			}
			printf("\n");
			tmpLitteral=tmpLitteral->suivant;
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
			if(!tmp->IDClause)//Clause n'existe plus (sera supprimer a la prochaine générartion de fomrule)
			{
				tmp=tmp->suivant;
				continue;
			}
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

Formule* supprimerLitteralDeClause(Formule* f,Clause *clause,int positionDansClause)
{
	/* REMARAUE :
	 * Les poistion dans clause commencent a partir de 0*/
	//Déclaration de variables
	int i,x,supprime=0;
	elemListe *tmpElemLitteral=NULL,*tmpElemLitteral2=NULL;
	elemListe *tmpElemClause=NULL,*tmpElemClause2=NULL;
	Litteral *tmpLitteral=NULL;
	 
	tmpElemLitteral=clause->teteListeLitteraux;
	 
	if(!positionDansClause)//position 0 : le litéral a supprimer est dans la tête de liste des littéraux dans la clause
	{
		clause->teteListeLitteraux=clause->teteListeLitteraux->suivant;
	}
	else
	{
		tmpElemLitteral2=tmpElemLitteral;
		tmpElemLitteral=tmpElemLitteral->suivant;
		 
		//Avancer jusqu'a le littéral a supprimer
		for(i=1;i<=positionDansClause;i++)
		{
			tmpElemLitteral=tmpElemLitteral->suivant;
			tmpElemLitteral2=tmpElemLitteral2->suivant;
		}
		tmpElemLitteral2->suivant=tmpElemLitteral->suivant;
	}
	 
	//Suppression de la clause dans la liste de clause du litteral
	tmpLitteral=getLitteral(f,abs(tmpElemLitteral->ID));
	tmpElemClause=tmpLitteral->teteListeClauses;
	
	//Si le littéral est négatif la clause dans la liste de clause du littéral est négatif
	if(tmpElemLitteral->ID<0) x=-1;
	else x=1;
	
	if((tmpElemClause->ID*(x))==clause->IDClause)
	{
		tmpLitteral->teteListeClauses=tmpElemClause->suivant; 
	}
	else
	{
		tmpElemClause2=tmpElemClause;
		tmpElemClause=tmpElemClause->suivant;
		while(tmpElemClause!=NULL||tmpElemClause->ID*x==clause->IDClause)
		{
			tmpElemClause=tmpElemClause->suivant;
			tmpElemClause2=tmpElemClause2->suivant;
		}
		tmpElemClause2->suivant=tmpElemClause->suivant;
	}
	free(tmpElemClause);
	free(tmpElemLitteral);
	 
	clause->nbLitteraux--;
	return f;
}


Formule* supprimerClause(Formule* f,Clause *clause)
{
	//Déclaration de variable
	elemListe *tmpElemLitteral=clause->teteListeLitteraux;
	int position=0;
	
	//Parcoure des littéraux de la clause "clause"
	while(tmpElemLitteral!=NULL)
	{
		//Suppression du littéral de la clause "clause" et de "clause" de liste de clause du litéral
		f=supprimerLitteralDeClause(f,clause,position);
		position++;
		tmpElemLitteral=tmpElemLitteral->suivant;
	}
	
	//la clause n'existe plus ! mettre l'ID a -1
	clause->IDClause=0;
	
	return f;
}


Formule* supprimerLitteralPur(Formule *f,Litteral* litteral)
{
	/* REMARQUE :
	 * Contient la suppression des clauses conteant ce litteral
	 */
	 
	 return f; 
}

int empiler(int litteral,int valeurDeVertier)
{
	return 0;
}

int depiler()
{
	return 0;
}	


