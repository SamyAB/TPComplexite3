#include "main.h"
#include "gestionLitterauxEtClauses.h"

Formule* simplifier(Formule *f,int litteral)
{
	//Déclaration de variables
	Litteral *tmpLitteral=NULL;
	elemListe *tmpElemClause=NULL,*tmpElemLitteral=NULL;
	Clause *tmpClause=NULL;
	int positionDansClause,suppressionClause;
	
	//Récupération du littéral dont l'ID est les valeure absolue de litteral
	tmpLitteral=getLitteral(f,abs(litteral));
	tmpElemClause=tmpLitteral->teteListeClauses;
	
	//Parcourt de la liste d'ID de clauses contenant le litteral
	while(tmpElemClause!=NULL)
	{
		//Récupérer la clause d'ID tmpElemClause->ID
		tmpClause=getClause(f,tmpElemClause->ID);
		
		//Initialiser le booléen suppression clause a faux
		suppressionClause=0;
		
		//Recherche dans la clause le litteral dont l'ID est litteral
		tmpElemLitteral=tmpClause->teteListeLitteraux;
		positionDansClause=0;
		while(tmpElemLitteral!=NULL) //Parcour tout les litteraux pour gerer le cas de précence du même littéral plusieurs fois dans la clause
		{
			if(tmpElemLitteral->ID==litteral) //Si la clause contient litteral
			{
				tmpElemClause=tmpElemClause->suivant;
				/* Faire ce passage avant de supprimer la clause car à la suppression
				 * de la clause les information dans tmpElemClause seront effacés et le suivant le sera aussi
				 */
				
				suppressionClause=1;
				f=supprimerClause(f,tmpClause);
				break; //La clause supprimée on ne va pas chercher plus loin dans cette même clause
			}
			else if(tmpElemLitteral->ID==(-1)*litteral) //Si la clause contient l'inverse de litteral
			{
				tmpElemLitteral=tmpElemLitteral->suivant;
				f=supprimerLitteralDeClause(f,tmpClause,positionDansClause);
				continue; //Élément de la clause supprimé passage au suivant effectué avant sa suppression et la position reste la même
			}
			
			tmpElemLitteral=tmpElemLitteral->suivant;
			positionDansClause++;
		}
		if(!suppressionClause) //Si la clause a été supprimée ce passage a déjà été effectué 
		{
			tmpElemClause=tmpElemClause->suivant;
		}
	}
	return f;
}

Formule* propagationUnitaire(Formule *f)
{
	//Déclaration de variables
	Clause *tmpClause;
	int i;
	
	//Pacourt de la table des clause a la recherche d'une clause vide ou de clause unitaire
	for(i=0;i<f->tailleTabClauses;i++)
	{
		tmpClause=f->tabClauses[i];
		
		//Gestion de collisions
		while(tmpClause!=NULL)
		{
			if(!tmpClause->nbLitteraux) //Clause vide 
			{
				return f;
			}
			else if(tmpClause->nbLitteraux==1) //Clause unitaire, donc a simplifier
			{
				f=simplifier(f,tmpClause->teteListeLitteraux->ID);
			}
			tmpClause=tmpClause->suivant;
		}
	}
	return f;
}

Formule* litteralPur(Formule *f)
{
	//Déclaration de variables
	Litteral *tmpLitteral=NULL;
	int i;
	
	//Parcourt de la table des littéraux à la recherche de littéraux purs
	for(i=0;i<f->tailleTabLitteraux;i++)
	{
		tmpLitteral=f->tabLitteraux[i];
		
		//Gestion de collision
		while(tmpLitteral!=NULL)
		{
			if(tmpLitteral->purete!='i') //Le littéral est pur
			{
				f=supprimerLitteralPur(f,tmpLitteral);
			}
		}
	}
	
	return f;
}

Formule* genererFormule(Formule *f,int valeurDeVerite)
{
	/* IMPORTANT:
	 * Mettre la pureté des littéraux a jour !
	 */
	  
	return f;
}

int DPLL(Formule **f)
{	
	//Déclaration de variables
	Formule *f1=NULL,*f2=NULL;
	
	if (!(*f)->nbClauses) //Si il y a 0 Clause, la formule est SAT
	{
		return 1;
	}
	
	//Propagation unitaire
	*f=propagationUnitaire(*f);
	
	//Si il existe une clause vide la formule est UNSAT	
	if(existeClauseVide(*f)) 
	{
		free(*f);
		return 0;
	}
	//Mettre a jour littéraux pures
	*f=litteralPur(*f);
	
	//On génére une copie de la formule f avec affectation d'un littéral a vrai dans f1 
	f1=genererFormule(*f,1);
	//Puis on génére une copie de f avec affectation du même litéral précedent a faux dans f2
	f2=genererFormule(*f,0);
	
	//Libération des recources mémoire consommée par la variable contenant formule f 
	free(*f);
	
	//Spliting rule (règle de séparation)
	if(DPLL(&f1)) 
	{
		//La formule initiale est SAT avec ces définitions
		return 1;
	}
	else
	{
		return(DPLL(&f2));
	}
}
