/*Projet compléxité N3
 * DPLL, soltution au problème SAT
 * Réalisé par SamyAB (samyab2@gmail.com)
 * 			et Mohamed BENCHENNOUF (remplace par ton pseudo et la ton mail)
 */
  	
#include "main.h"
#include "gestionDeFichiers.h"
#include "gestionLitterauxEtClauses.h"
#include "DPLL.h"

int main(int argc,char **argv)
{
	Clause **tabClauses;
	Litteral **tabLitteraux;
	int nbClauses,nbLitteraux;
	Formule *f=NULL;
	
	f=(Formule*) malloc(sizeof(Formule));
	if(!lecture("3amar.cnf",&(f->tabClauses),&(f->tabLitteraux),&(f->nbClauses),&(f->nbLitteraux)))
	{
		//affichageClauses(f->tabClauses,f->nbClauses);
		f->tailleTabClauses=nbClauses;
		f->tailleTabLitteraux=nbLitteraux;
	}
	else printf("erreur\n");
	return 0;
}
