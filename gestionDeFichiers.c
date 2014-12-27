#include "main.h"

int lecture(char* cheminFichier,Clause **tabClause,Litteral **tabLitteraux,int *nbClauses,int *nbLitteraux)
{
	//Déclaration de variables
	FILE *=NULL;
	int i;
	char ligne[256],nombre[10],nombre2[10];
	
	//Ouverture du fichier en mode lecture
	fichier=fopen(cheminFichier,"r");
	if(fichier==NULL)
	{
		fprintf(stderr,"fichier %s non lu\n",cheminFichier);
		return -1;
	}
	
	//Ignorer les 7 première lignes des fichiers
	for(i=0;i<7;i++) fgets(ligne,255,fichier);
	
	//Lecture de la ligne du nombre de littéraux et du nombre de clauses
	fgets(ligne,255,fichier);
	
	//Test que la ligne commence bien par un p dans le cas inverse le fichier a un fomat non supporté
	if(ligne[0]!='p')
	{
		fprintf(stderr,"le format du fichier %s est erroné\n",cheminFichier);
		return -1;
	}
	
	//Saut des caractères jusqu'au premier chiffre (sauf 0)
	i=1;
	while(ligne[i]<49 && ligne[i]>57) i++;
	
	//Lecture du nombre de littéraux
	j=0;
	while(ligne[i]!=' ')
	{
		nombre[j]=ligne[i];
		i++;
		j++;
	}
	nombre[j]='\0';
	*nbLitteraux=atoi(nombre);
	
	//Saut des caractères jusqu'au premier chiffre (sauf 0)
	while(ligne[i]<49 && ligne[i]>57) i++;
	
	//Lecture du nombre de clauses
	j=0;
	while(ligne[i]!=' ')
	{
		nombre2[j]=ligne[i];
		i++;
		j++;
	}
	nombre2[j]='\0';
	*nbClauses=atoi(nombre2);
	
	
	 
	return 0;
}
