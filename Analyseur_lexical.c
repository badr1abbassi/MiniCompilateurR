#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "Analyseur_lexical.h"
#include "Analyseur_semantique.h"
#include "Analyseur_syntaxique.h"

int position=-1;
char *token;

symb s1;
symb s2;
symb  tabSymb[50];
int tailleMotCle = 21;

char tabMotCle[21][50]={"break","if","else","while","for","return","print","cos","function","max","min","rep","list","plot","mean","length","matrix","help","in","readline","sqrt"};

char** tabMots;
int taille=0;

int tailleTabSymb;

void obtenir_NextMot(){
    if(position<taille){
     do{
        position++;
     }while(strcmp(tabMots[position]," ")==0 || strcmp(tabMots[position],"\t")==0 );

   token=malloc(strlen((tabMots[position])+1)*sizeof(char));
   strcpy(token,tabMots[position]);
   }
}

void initData(){
strcpy(tabSymb[0].symbole,";");
strcpy(tabSymb[0].signification,"PV_TOKEN");
strcpy(tabSymb[1].symbole,"+");
strcpy(tabSymb[1].signification,"PLUS_TOKEN");
strcpy(tabSymb[2].symbole,"*");
strcpy(tabSymb[2].signification,"MULT_TOKEN");
strcpy(tabSymb[3].symbole,"!");
strcpy(tabSymb[3].signification,"NOT_TOKEN");
strcpy(tabSymb[4].symbole,"-");
strcpy(tabSymb[4].signification,"MOINS_TOKEN");
strcpy(tabSymb[5].symbole,"(");
strcpy(tabSymb[5].signification,"PO_TOKEN");
strcpy(tabSymb[6].symbole,")");
strcpy(tabSymb[6].signification,"PF_TOKEN");
strcpy(tabSymb[7].symbole,"<-");
strcpy(tabSymb[7].signification,"AFF_TOKEN");
strcpy(tabSymb[8].symbole,"/");
strcpy(tabSymb[8].signification,"DIV_TOKEN");
strcpy(tabSymb[9].symbole,",");
strcpy(tabSymb[9].signification,"VIR_TOKEN");
strcpy(tabSymb[10].symbole,"=");
strcpy(tabSymb[10].signification,"AFF_TOKEN");
strcpy(tabSymb[11].symbole,"<");
strcpy(tabSymb[11].signification,"INF_TOKEN");
strcpy(tabSymb[12].symbole,"<=");
strcpy(tabSymb[12].signification,"INFEG_TOKEN");
strcpy(tabSymb[13].symbole,">");
strcpy(tabSymb[13].signification,"SUP_TOKEN");
strcpy(tabSymb[14].symbole,">=");
strcpy(tabSymb[14].signification,"SUPEG_TOKEN");
strcpy(tabSymb[15].symbole,"==");
strcpy(tabSymb[15].signification,"EQ_TOKEN");
strcpy(tabSymb[16].symbole,"&");
strcpy(tabSymb[16].signification,"AND_TOKEN");
strcpy(tabSymb[17].symbole,"|");
strcpy(tabSymb[17].signification,"OR_TOKEN");
strcpy(tabSymb[18].symbole,"{");
strcpy(tabSymb[18].signification,"AO_TOKEN");
strcpy(tabSymb[19].symbole,"}");
strcpy(tabSymb[19].signification,"AF_TOKEN");
strcpy(tabSymb[20].symbole,"\n");
strcpy(tabSymb[20].signification,"RET_TOKEN");
strcpy(tabSymb[21].symbole," ");
strcpy(tabSymb[21].signification,"BLANC_TOKEN");
strcpy(tabSymb[22].symbole,":");
strcpy(tabSymb[22].signification,"DPT_TOKEN");
strcpy(tabSymb[23].symbole,"\"");
strcpy(tabSymb[23].signification,"QT_TOKEN");
strcpy(tabSymb[24].symbole,"_FIN_");
strcpy(tabSymb[24].signification,"FIN_TOKEN");
strcpy(tabSymb[25].symbole,"\t");
strcpy(tabSymb[25].signification,"TAB_TOKEN");
tailleTabSymb=26;
}

char *char2string(char c){
   char *str=malloc(2*sizeof(char));
   if(str==NULL)
     return NULL;
   str[0]=c;
   str[1]='\0';
   return str;
}

int isMotCle(char* mot){
int i=0;
while(i<tailleMotCle){
if(strcmp(mot,tabMotCle[i])==0){
return 0;
}
i++;
}
return -1;
}

int isSymb(char* mot){
int i=0;
while(i<tailleTabSymb){
if(strcmp(mot,tabSymb[i].symbole)==0){
return i;
}
i++;
}
return -1;
}

int isIdent(char* mot){
    if(isMotCle(mot)==-1){
    int i=1;
    bool flag=true;
        if((mot[0]<='z' && mot[0]>='a')||(mot[0]<='Z' && mot[0]>='A')){
                while(i<strlen(mot) && flag==true){
                    if(isSymb(char2string(mot[i]))!=-1){
                        flag=false;
                    }
                    i++;
                }
    if(flag==true){
            return 0;//succes
                }
        }
    }
    return -1;//echec
}

int isNumber(char * mot){

int i=0;
while(i<strlen(mot) && (mot[i]<='9' && mot[i]>='0')){
        i++;
}
if (mot[i]=='.'){
        i++;
while(i<strlen(mot) && (mot[i]<='9' && mot[i]>='0')){
        i++;
}
}

if(i==strlen(mot))
    return 0;//succes
else
    return -1;//echec
}

void put(char * mot){
taille++;
tabMots=realloc(tabMots,taille*sizeof(char*));
tabMots[taille-1]=malloc((strlen(mot)+1)*sizeof(char));
strcpy(tabMots[taille-1],mot);

}

void listerMot(){
initData();
FILE *f;
char c;
int i;
int var;
char * mot=malloc(sizeof(char));
int tailleMot=0;
char  m[2];
int flag=0;
f=fopen("C:/Users/XPS/Desktop/compila.R","r");

if(f!=NULL){
        while(!feof(f)) {
        if (flag == 0)
            c=fgetc(f);
        flag =0;
        sprintf(m,"%c",c);
        if (c==EOF) {
            if(tailleMot>0){
                mot[tailleMot]='\0';
                put(mot);
                free(mot);
                mot=(char*)malloc(sizeof(char));
                tailleMot = 0;
            }
        }
        if(isSymb(m)!=-1 ){
            if(tailleMot>0){
                mot[tailleMot]='\0';
                put(mot);
                free(mot);
                mot=(char*)malloc(sizeof(char));
                tailleMot = 0;
            }
            if(strcmp(m,"<")==0){
                c=fgetc(f);
                if(c=='-'|| c=='='){
                    sprintf(m,"<%c",c);
                    put(m);
                    free(m);

                }else{
                    put(m);
                    free(m);
                    flag = 1 ;
                    continue ;
                }

            }else if(strcmp(m,"!")==0 || strcmp(m,">")==0|| strcmp(m,"=")==0){
                c=fgetc(f);
                if(c=='='){
                    sprintf(m,"%s%c",m,c);
                    put(m);
                    free(m);

                }else{
                    put(m);
                    free(m);
                    flag = 1 ;
                    continue ;
                }

            }
            else{
                put(m);
                free(m);
            }


        }
       else{
            tailleMot++;
            mot=realloc(mot,tailleMot*sizeof(char));
            mot[tailleMot-1]=c;
            //printf("\n mot %s %d \n", mot, tailleMot);
        }

    }
    put("_FIN_");//la fin du programme
    fclose(f);
    printf("\n");
    for(i=0;i<taille-1;i++){
         if(isMotCle(tabMots[i])==0){
         printf("%d -> #%s# est un %s_TOKEN\n",i,tabMots[i],tabMots[i]);
    }else if(isIdent(tabMots[i])==0){
         printf("%d -> #%s# est un Identifiant\n",i,tabMots[i]);
    }else if(isNumber(tabMots[i])==0){
         printf("%d -> #%s# est un Nombre\n",i,tabMots[i]);
    }else if((var=isSymb(tabMots[i]))!=-1){
        printf("%d -> #%s# est un %s\n",i,tabMots[i],tabSymb[var].signification);
    }else{
        printf("%d -> #%s# est un ERREUR_TOKEN\n",i,tabMots[i]);
    }
    }

}else{
printf("err d'ouverture");
}

}


