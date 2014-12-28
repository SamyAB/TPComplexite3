#ifndef DPLLH
#define DPLLH

Formule* propagationUnitaire(Formule *f);
Formule* litteralPur(Formule *f);
Formule* genererFormule(Formule *f,int valeurDeVerite);
int DPLL(Formule **f);

#endif

