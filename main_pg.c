#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "Analyseur_lexical.h"
#include "Analyseur_semantique.h"
#include "Analyseur_syntaxique.h"

extern char** tabMots;
extern variable* tabID;
extern char* token;
extern int tailleTabId;
extern fonct * tabFonc;
extern int tailleTabFonc;
int main(){

tabMots=malloc(sizeof(char*));
printf("\n\t--------------------------Analyseur Lexical ----------------------------------------------\n");
listerMot();
printf("\n\t----------------------------Analyseur Syntaxique--------------------------------------------\n");
tabID=malloc(sizeof(char*));
if(isInstructions()==0){
        obtenir_NextMot();
        if(strcmp(token,"_FIN_")==0){
            printf("\nprogramme correcte\n");
        }else{
    printf("programme incorrect\n");
    return 0;
        }

}else{
printf("programme incorrect\n");
return 0;
}

int i,j;
printf("\n\t----------------------------Analyseur Semantique--------------------------------------------\n");
printf("Tab des VARS:\n\n");
for(i=0;i<tailleTabId;i++){
    printf("%s : %s :%d\t",tabID[i].var,tabID[i].type,tabID[i].pos);
}
printf("\nTab des Fonctions:\n\n");
for(i=0;i<tailleTabFonc;i++){
    printf("%s : %d :%d\t",tabFonc[i].nom,tabFonc[i].nbrParam,tabFonc[i].pos);
}
printf("\n\nTester l'utilisation des variables\n");
semantiqueVar();

return 0;
}
