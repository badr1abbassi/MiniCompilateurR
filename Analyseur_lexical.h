#ifndef ANALYSEUR_LEXICAL_H_INCLUDED
#define ANALYSEUR_LEXICAL_H_INCLUDED
typedef struct symboles{
    char symbole[5];
    char signification[20];
}symb;

typedef struct word{
    char mot[20];
    char symbole[20];
}word;

typedef struct tab{
char** tabMots;
int taille;
}tabM;

void initData();
char *char2string(char c);
int isMotCle(char* mot);
int isSymb(char* mot);
int isIdent(char* mot);
int isNumber(char * mot);
void put(char * mot);
void listerMot();



#endif // ANALYSEUR_LEXICAL_H_INCLUDED
