#include "main.h"

int lecture(char* cheminFichier,Clause **tabClause,Literal **tabLitteraux,int *nbClause,int *nbLitteraux)
{
	FILE *=NULL;
	fichier=fopen(cheminFichier,"r");
	if(fichier==NULL)
	{
		fprintf(stderr,"fichier %s non lu\n",cheminFichier);
		return -1;
	}
	
	return 0;
}
