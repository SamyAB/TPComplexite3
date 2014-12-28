/*Projet compléxité N3
 * DPLL, soltution au problème SAT
 * Réalisé par SamyAB (samyab2@gmail.com)
 * 			et Mohamed BENCHENNOUF (remplace par ton pseudo et la ton mail)
 */
  	
#include "main.h"
#include "gestionDeFichiers.h"
#include "gestionLitterauxEtClauses.h"

int main(int argc,char **argv)
{
	Clause **tabClauses;
	Litteral **tabLitteraux;
	int nbClauses,nbLitteraux;
	if(!lecture("3amar.cnf",&tabClauses,&tabLitteraux,&nbClauses,&nbLitteraux))
	{
		affichageClauses(tabClauses,nbClauses);
	}
	else printf("erreur\n");
	return 0;
}
