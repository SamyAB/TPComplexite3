#ifndef GESTIONLITTERAUXETCLAUSES
#define GESTIONLITTERAUXETCLAUSES

int ajouterLitteral(Clause *clause,int valeurLitteral);
void affichageClauses(Clause **tabClauses,int tailleTabClauses);
int existeClauseVide(Formule *f);
Litteral* getLitteral(Formule *f,int valeur);
Clause* getClause(Formule *f,int ID);
Formule* supprimerClause(Formule* f,Clause *clause);
Formule* supprimerLitteralDeClause(Formule* f,Clause *clause,int positionDansClause);

#endif


