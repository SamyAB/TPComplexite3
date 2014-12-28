#ifndef GESTIONLITTERAUXETCLAUSES
#define GESTIONLITTERAUXETCLAUSES

int ajouterLitteral(Clause *clause,int valeurLitteral);
void affichageClauses(Clause **tabClauses,int tailleTabClauses);
int existeClauseVide(Formule *f);

#endif


