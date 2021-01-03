#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "Analyseur_lexical.h"
#include "Analyseur_semantique.h"
#include "Analyseur_syntaxique.h"


extern int taille;
extern char** tabMots;
variable* tabID;
int tailleTabId=0;
char** tabAff;
int tailleTabAff=0;

fonct* tabFonc;
int tailleTabFonc;

int putTabID(char * mot,char * type,int pos){
        tailleTabId++;
        tabID=realloc(tabID,tailleTabId*sizeof(variable));
        tabID[tailleTabId-1].var=malloc((strlen(mot)+1)*sizeof(char));
        strcpy(tabID[tailleTabId-1].var,mot);
        tabID[tailleTabId-1].type=malloc((strlen(type)+1)*sizeof(char));
        strcpy(tabID[tailleTabId-1].type,type);
        tabID[tailleTabId-1].pos=pos;
        return 0;
}
int putTabFonc(char * mot,int nbrparm,int pos){
        tailleTabFonc++;
        tabFonc=realloc(tabFonc,tailleTabFonc*sizeof(variable));

        tabFonc[tailleTabFonc-1].nom=malloc((strlen(mot)+1)*sizeof(char));
        strcpy(tabFonc[tailleTabFonc-1].nom,mot);
        tabFonc[tailleTabFonc-1].nbrParam=nbrparm;
        tabFonc[tailleTabFonc-1].pos=pos;
        return 0;

}
int isSymbole(char *mot){
    char TabS[2][2] ={"=","<-"};
    int i;
    for(i=0;i<5;i++){
        if(strcmp(mot,TabS[i])==0){
            return 0;
        }
    }
    return -1;
}

int semantiqueVar(){
int i,j,k;
int flag,flagFun;
int err=0;
int cpt=0;

for(i=0;i<taille-1;i++){
     //printf("\i %s\n",tabMots[i]);
     if(strcmp(tabMots[i],"function")==0) {
        //printf("\nfunction\n");
         char varFunc [50][50];
         int tVar=0;
         i++;
         do {
            if(strcmp(tabMots[i],"\"")==0) {
                printf("\quotes\n");
                do {
                    i++;
                } while (strcmp(tabMots[i],"\"")!=0);
            }
         if(strcmp(tabMots[i],"(")==0) {
            do {
                i++;
                if(isIdent(tabMots[i])==0) {
                    strcpy(varFunc[tVar],tabMots[i]);
                    tVar++;
                }
            }while (strcmp(tabMots[i],"{")!=0);
            }
            i++;
            if(strcmp(tabMots[i],"{")==0)
                cpt++;
            if(strcmp(tabMots[i],"}")==0)
                cpt--;
            if(isIdent(tabMots[i])==0) {
                flagFun=0;
                for(k=0;k<tVar;k++){
                    if(strcmp(tabMots[i],varFunc[k])==0) {
                        flagFun=1;
                    }
                }
                for(k=0;k<tailleTabId;k++){
                    if(strcmp(tabMots[i],tabID[k].var)==0) {
                        flagFun=1;
                    }
                }
                if(flagFun==0) {
                     printf("VAR %s not found %d\n",tabMots[i],i);
                     err++;
                }
            }
            } while(cpt>=0);
    }
    if(strcmp(tabMots[i],"\"")==0) {
        do {
            i++;
        } while (strcmp(tabMots[i],"\"")!=0);
    }
    //printf("\mot %s\n",tabMots[i]);
    if(isIdent(tabMots[i])==0){

        int pos=i;
        int cpt=0;

        do{
        cpt++;
        i++;
        }while(tabMots[i]==" " ||tabMots[i]=="_FIN_");
        if(isSymbole(tabMots[i])!=0){
            i-=cpt;
        if(tailleTabId ==0){printf("no variable declared\n");return -1;}
        j=0;
        flag=0;
        while(j<tailleTabId && flag==0){
            if(strcmp(tabMots[i],tabID[j].var)==0){
                if(i<tabID[j].pos){
                        flag=1;
                }else{
                    flag=0;
                    break;
                }
            }
            j++;
        }if(flag==1){
             printf("PB VAR %s NOT FOUND position %d\n",tabMots[i],i);
                err++;
        }
        if(j==tailleTabId){
            printf("VAR %s not found %d\n",tabMots[i],i);
            err++;
        }

    }else{

        i=pos;

    }
    }
}
if(err==0)
printf("\n\tCorrecte semantiquement\n");
else printf("%d ERRR!!!!!!!!\n",err);
return 0;
}
