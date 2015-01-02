#ifndef GESTIONLITTERAUXETCLAUSES
#define GESTIONLITTERAUXETCLAUSES

int ajouterLitteral(Clause *clause,int valeurLitteral);
void affichageClauses(Clause **tabClauses,int tailleTabClauses);
void affichageLitteraux(Litteral **tabLitteraux,int tailleTabLitteraux);
int existeClauseVide(Formule *f);
int hashage(int ID,int taille);
Litteral* getLitteral(Formule *f,int valeur);
Clause* getClause(Formule *f,int ID);
Formule* supprimerClause(Formule* f,Clause *clause);
Formule* supprimerLitteralDeClause(Formule* f,Clause *clause,int positionDansClause);
Formule* supprimerLitteralPur(Formule *f,Litteral* litteral);


#endif


