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
	tmpLitteral=getLitteral(f,litteral);
	tmpElemClause=tmpLitteral->teteListeClauses;

	if(tmpElemClause==NULL)
	{
		fprintf(stderr," Erreur litteral inexisant (Fonction simplifier)\n");
		exit(EXIT_FAILURE);
	}
	
	//Parcourt de la liste d'ID de clauses contenant le litteral
	while(tmpElemClause!=NULL)
	{
		//Récupérer la clause d'ID tmpElemClause->ID
		printf(" POp %d	 \n",tmpElemClause->ID);
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
				printf(" 40 \n");
				f=supprimerLitteralDeClause(f,tmpClause,positionDansClause);
				printf(" 44 \n");
				continue; //Élément de la clause supprimé passage au suivant effectué avant sa suppression et la position reste la même
			}
			
			tmpElemLitteral=tmpElemLitteral->suivant;
			positionDansClause++;
		}
			printf(" Hehe sortie de zhile 	 \n");

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
				if(tmpLitteral->purete=='p')
				{
					f=simplifier(f,tmpLitteral->IDLitteral);
				}
				else if(tmpLitteral->purete=='n')
				{
					f=simplifier(f,tmpLitteral->IDLitteral*(-1));
				}
				else
				{
					fprintf(stderr,"Pureter non initialiser (Fonction litteral pure)\n");
					exit(EXIT_FAILURE);
				}
				
			}
			tmpLitteral=tmpLitteral->suivant;
		}
	}
	
	return f;
}

Formule* genererFormule(Formule *f,int l,int valeurDeVerite)
{
	/* IMPORTANT:
	 * ne pas dubliquer les valeur de la table de clause where ID=0
	 * ne pas dupliquer les littéraux qui ont teteListeClause == NULL
	 */
	Formule *tmpFormule=NULL; 
	Litteral *tmpLitteral=NULL,*tmpNewLitteral=NULL;
	Clause *tmpClause=NULL,*tmpNewClause=NULL;
	elemListe *tmpElemClause,*tmpElemNewClause,*tmpElemLitteral,*tmpElemNewLitteral,*tmpElemNewLitteral2,*tmpElemNewClause2;
	int i,supTabClause=0,supTabLit=0;
	
	
	for(i=0;i<f->tailleTabClauses;i++)
	{
		if(f->tabClauses[i]->IDClause==0)supTabClause++;
	}
	for(i=0;i<f->tailleTabLitteraux;i++)
	{
		if(f->tabLitteraux[i]->teteListeClauses==NULL)supTabLit++;
	} 
	tmpFormule=(Formule*)malloc(sizeof(Formule));
	if(tmpFormule==NULL)
	{
		fprintf(stderr,"fonction genererFormule nouvel formule non cree\n");
		exit(EXIT_FAILURE);
	}
	tmpFormule->tailleTabClauses= f->tailleTabClauses- supTabClause;
	tmpFormule->tailleTabLitteraux = f->tailleTabLitteraux-supTabLit ;
	tmpFormule->tabClauses = (Clause**)malloc(tmpFormule->tailleTabClauses*sizeof(Clause*));
	tmpFormule->tabLitteraux =(Litteral**)malloc(tmpFormule->tailleTabLitteraux*sizeof(Litteral*));
	
	for(i=0;i<f->tailleTabClauses;i++)
	{
		tmpClause=f->tabClauses[i];
		while(tmpClause!=NULL)
		{
			if(!tmpClause->IDClause) //la clause n'existe plus 
			{
				tmpClause=tmpClause->suivant;
				continue; 
			}
			tmpNewClause=(Clause*)malloc(sizeof(Clause));
			if(tmpNewClause==NULL)
			{
				fprintf(stderr,"nouvelle clause non alloué (fonction générationDeFormule)\n");
				exit(EXIT_FAILURE);
			}
			
			tmpNewClause->IDClause=tmpClause->IDClause;
			tmpNewClause->nbLitteraux=tmpClause->nbLitteraux;
			tmpElemLitteral=tmpClause->teteListeLitteraux;
			
			tmpElemNewLitteral=(elemListe*)malloc(sizeof(elemListe));
			if(tmpElemNewLitteral==NULL)
			{
				fprintf(stderr,"erreur lors de allocation de la tête de littéraux dans la clause %d (fonctino generationFormule)\n",tmpNewClause->IDClause);
				exit(EXIT_FAILURE);
			}
			tmpElemNewLitteral->ID=tmpElemLitteral->ID;
			tmpElemNewLitteral->suivant=NULL;
			tmpElemNewLitteral2=tmpElemNewLitteral;
			
			while(tmpElemLitteral!=NULL)
			{
				tmpElemNewLitteral=(elemListe*)malloc(sizeof(elemListe));
				if(tmpElemNewLitteral==NULL)
				{
					fprintf(stderr,"erreur lors de l'allocation d'un nouverl ellement dans la liste de littéraux de la clause %d (fonction générationFormule)\n",tmpNewClause->IDClause);
					exit(EXIT_FAILURE);
				}
				tmpElemNewLitteral->ID=tmpElemLitteral->ID;
				tmpElemNewLitteral2->suivant=tmpElemNewLitteral;
				tmpElemLitteral=tmpElemLitteral->suivant;
				tmpElemNewLitteral2=tmpElemNewLitteral2->suivant;
			}
			
			if(tmpFormule->tabClauses[hashage(tmpClause->IDClause,tmpFormule->tailleTabClauses)]==NULL)
			{
				tmpFormule->tabClauses[hashage(tmpClause->IDClause,tmpFormule->tailleTabClauses)]=tmpNewClause;
			}
			else
			{
				tmpNewClause->suivant=tmpFormule->tabClauses[hashage(tmpClause->IDClause,tmpFormule->tailleTabClauses)];
				tmpFormule->tabClauses[hashage(tmpClause->IDClause,tmpFormule->tailleTabClauses)]=tmpNewClause;
			}
		}
	}
	
	for(i=0;i<f->tailleTabLitteraux;i++)
	{
		tmpLitteral=f->tabLitteraux[i];
		while(tmpLitteral!=NULL)
		{
			if(tmpLitteral->teteListeClauses==NULL) //Le littéral n'éxiste plus
			{
				tmpLitteral=tmpLitteral->suivant;
				continue;
			}
			tmpNewLitteral=(Litteral*)malloc(sizeof(Litteral));
			if(tmpNewLitteral==NULL)
			{
				fprintf(stderr,"Nouvelle littéral non alloué (fonction générationDeFormule)\n");
				exit(EXIT_FAILURE);
			}
			
			tmpNewLitteral->IDLitteral=tmpLitteral->IDLitteral;
			tmpElemClause=tmpLitteral->teteListeClauses;
			
			tmpElemNewClause=(elemListe*)malloc(sizeof(elemListe));
			if(tmpElemNewClause==NULL)
			{
				fprintf(stderr,"erreur lors de allocation de la tête de clauses dans le littéral %d (fonctino generationFormule)\n",tmpNewLitteral->IDLitteral);
				exit(EXIT_FAILURE);
			}
			tmpElemNewClause->ID=tmpElemClause->ID;
			tmpElemNewClause->suivant=NULL;
			tmpElemNewClause2=tmpElemNewClause;
			
			while(tmpElemClause!=NULL)
			{
				tmpElemNewClause=(elemListe*)malloc(sizeof(elemListe));
				if(tmpElemNewClause==NULL)
				{
					fprintf(stderr,"erreur lors de l'allocation d'un nouverl ellement dans la liste de clauses de lu littéral %d (fonction générationFormule)\n",tmpNewLitteral->IDLitteral);
					exit(EXIT_FAILURE);
				}
				tmpElemNewClause->ID=tmpElemClause->ID;
				tmpElemNewClause2->suivant=tmpElemNewClause;
				tmpElemClause=tmpElemClause->suivant;
				tmpElemNewClause2=tmpElemNewClause2->suivant;
			}
			
			if(tmpFormule->tabLitteraux[hashage(tmpLitteral->IDLitteral,tmpFormule->tailleTabLitteraux)]==NULL)
			{
				tmpFormule->tabLitteraux[hashage(tmpLitteral->IDLitteral,tmpFormule->tailleTabLitteraux)]=tmpNewLitteral;
			}
			else
			{
				tmpNewLitteral->suivant=tmpFormule->tabLitteraux[hashage(tmpLitteral->IDLitteral,tmpFormule->tailleTabLitteraux)];
				tmpFormule->tabLitteraux[hashage(tmpLitteral->IDLitteral,tmpFormule->tailleTabLitteraux)]=tmpNewLitteral;
			}
		}
	}
	
	tmpFormule=simplifier(tmpFormule,(valeurDeVerite*l)); 
	tmpFormule=majPurete(tmpFormule);
	return tmpFormule;
}

int DPLL(Formule **f)
{	
	//Déclaration de variables
	Formule *f1=NULL,*f2=NULL;
	int l;
	
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
	
	*f=litteralPur(*f);
	
	//On choisi le littéral selon lequel nous allons générer nos formules
	l=choixLitteral(*f);
	//On génére une copie de la formule f avec affectation d'un littéral a vrai dans f1 
	f1=genererFormule(*f,l,1);
	//Puis on génére une copie de f avec affectation du même litéral précedent a faux dans f2
	f2=genererFormule(*f,l,-1);
	
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
