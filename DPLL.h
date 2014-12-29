#ifndef DPLLH
#define DPLLH

Formule* simplifier(Formule *f,int litteral);
Formule* propagationUnitaire(Formule *f);
Formule* litteralPur(Formule *f);
Formule* genererFormule(Formule *f,int valeurDeVerite);
int DPLL(Formule **f);

#endif

