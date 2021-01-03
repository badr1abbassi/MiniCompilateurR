#ifndef ANALYSEUR_SEMANTIQUE_H_INCLUDED
#define ANALYSEUR_SEMANTIQUE_H_INCLUDED
typedef struct variable{
char * var;
char * type;
int pos;
}variable;
typedef struct fonction{
char * nom;
int nbrParam;
int pos;
}fonct;

int putTabID(char * mot,char * type,int);
int semantiqueVar();

#endif // ANALYSEUR_SEMANTIQUE_H_INCLUDED
