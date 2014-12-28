#include "main.h"
#include "gestionLitterauxEtClauses.h"

Formule* simplifier(Formule *f,int litteral)
{
	
	return f;
}

Formule* propagationUnitaire(Formule *f)
{
	//Déclaration de variables
	Clause *tmpClause;
	int i;
	
	for(i=0;i<f->tailleTabClauses && f->tabClauses[i]->nbLitteraux;i++)
	{
		tmpClause=f->tabClauses[i];
		while(tmpClause!=NULL)
		{
			if(!tmpClause->nbLitteraux)
			{
				return f;
			}
			else if(tmpClause->nbLitteraux==1)
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
	return f;
}

Formule* genererFormule(Formule *f,int valeurDeVerite)
{
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
	if(existeClauseVide) return 0;
	
	//Mettre a jour littéraux pures
	*f=litteralPur(*f);
	
	//On génére une copie de la formule f avec affectation d'un littéral a vrai dans f1 
	f1=genererFormule(*f,1);
	//Puis on génére une copie de f avec affectation du même litéral précedent a faux dans f2
	f2=genererFormule(*f,0);
	
	//Libération des recources mémoire consommée par la variable contenant formule f 
	free(*f);
	
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
