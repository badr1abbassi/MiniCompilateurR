#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "Analyseur_lexical.h"
#include "Analyseur_semantique.h"
#include "Analyseur_syntaxique.h"

int nbrpar;

extern char *token;
extern int position;
extern char **tabMots;
extern variable* tabID;

int isMotCle_Syn(){
    obtenir_NextMot();
    return isMotCle(token);
}

int isSymb_Syn(){
    obtenir_NextMot();
    return isSymb(token);
}

int isIdent_Syn(){
    obtenir_NextMot();
    return isIdent(token);
}

int isNum(){
    obtenir_NextMot();
    return isNumber(token);
}

//--------------------------------------------------------->epslon
int isInstructions(){
    int pos=position;
    if(isInstruction()==0){
        if (isII()==0){
            return 0;//succes
        }else{
        }
    }else{
        position=pos;
        obtenir_NextMot();
        if(strcmp(token,"\n")==0) {
            if(isInstructions()==0)
                return 0;
        }
        else {
            position=pos;
            return 0;
        }
    }
    //------------------------------> le cs epsilon
    return -1;
}
//--------------------------------------------------------->epslon
int isII(){
    int pos=position;
    if(isEnd()==0){
        if(isInstructions()==0){
            return 0;
        }
    }else{
    position=pos;
    return 0;
    }
return -1;
}


int isInstruction(){
    int pos=position;
    if(isExpression()==0){
        return 0;//success
    }else{
        position=pos;
        if(isSI()==0){
            return 0;//success
        }else{
            position=pos;
            if(isBoucle()==0){
                return 0;//success
            }else{
                position=pos;
                if(isFonc()==0){
                    return 0;//success
                }
            }

    }

}
return -1;
}

int isEnd(){
    obtenir_NextMot();
    if(strcmp(token,"\n")==0 || strcmp(token,";")==0 )//!!!!!!!!!!!!!!!!!!!!
        return 0;
    return -1;
}
char* id ;

int isExpression(){
    int pos=position;
    if(isIdent_Syn()==0){
        id= malloc(50*sizeof(char));
        strcpy(id,token);
        if(isAff()==0){
            return 0;
        }
    }else{
        position=pos;
        if(isNum()==0){
                if(isOper()==0){
                    return 0;
                }
        }else{
            position=pos;
            obtenir_NextMot();
            if(strcmp(token,"(")==0){
                if(isExpression()==0){
                     obtenir_NextMot();
                    if(strcmp(token,")")==0){
                       return 0;
                    }
                }
            }
        }
    }
    return -1;
}

//--------------------------------------------------------->epslon
int isOper(){
    int pos=position;
    if(isOp()==0){
        if(isExpression()==0){
            return 0;
        }
    }else{
      if(strcmp(token,":")==0) {
                if(isExpression()==0) {
                    return 0;
                }
            }else {
                position=pos;
                return 0;
            }
    }
    return -1;
}

int isOp(){
    obtenir_NextMot();
    if(strcmp(token,"+")==0 ||strcmp(token,"*")==0 || strcmp(token,"-")==0 || strcmp(token,"/")==0){
        return 0;
    }
    return -1;
}

int isAff(){
    int pos=position;
    if(isOppAff()==0){
            int pp=position;
        if(isExpressionAff()==0){
                if(isNumber(tabMots[position])==0)
                putTabID(tabMots[pos],"NUMBER",pos);
            return 0;
        }else{
            position=pp;
            if(isExpressionAff()==2){
                putTabID(tabMots[pos],"TEXT",pos);
                return 0;
            }else{
                position=pp;
                if(isExpressionAff()==1){
                putTabID(tabMots[pos],"function",pos);
                return 0;
                }
            }
        }
    }else{
        position=pos;
        if(isOp()==0){
            if(isExpression()==0){
                return 0;
            }
        }else{
            if(strcmp(token,":")==0) {
                if(isExpression()==0) {
                    return 0;
                }
            }else {
                position=pos;
                obtenir_NextMot();
                if(strcmp(token,"(")==0){
                        nbrpar=0;
                    if(isParams()==0){
                        obtenir_NextMot();
                        if(strcmp(token,")")==0){
                                putTabFonc(tabMots[pos],nbrpar,pos);
                            return 0;
                        }
                    }
                }else{
                    position=pos;
                    return 0;
                }
            }
        }
    }
    return -1;
}

int isExpressionAff(){
    int pos=position;
    if(isExpression()==0){
        return 0;//pour dire c'est une affectation ID = EXPRESSION
    }else{
        position=pos;

        if(isFonc()==0){
            return 1;
        }else{
            position=pos;
             obtenir_NextMot();
            if(strcmp(token,"\"")==0){
                do{
                    obtenir_NextMot();
                    if(strcmp(token,"_FIN_")== 0 ){
                        return -1;
                }
            }while(strcmp(token,"\"")!=0);
                return 2;//pour dire c'est une affectation ID = "TEXT"            }
            }
        }
    }
    return -1;
}

int isOppAff(){
    obtenir_NextMot();
    if(strcmp(token,"=")== 0 || strcmp(token,"<-")==0){
        return 0;
    }
    return -1;
}

int isSI(){
    obtenir_NextMot();
    if(strcmp(token,"if")==0){
        obtenir_NextMot();
        if(strcmp(token,"(")==0){
            if(isCnd()==0){
               obtenir_NextMot();
               if(strcmp(token,")")==0){
                    if(isSII()){
                        return 0;
                    }
               }
            }else{
                //printf("pb f cnd %d\n",position);
            }
        }
    }
}

int isSII(){
    int pos=position;
    obtenir_NextMot();
    if(strcmp(token,"{")==0){
        if(isInstructions()==0){
            obtenir_NextMot();
            if(strcmp(token,"}")==0){
                if(isElse()==0){
                    return 0;
                }
            }
        }
    }else{
        position=pos;
        if(isInstructions()==0){
            return 0;
        }
    }
    return -1;
}

//--------------------------------------------------------->epslon
int isElse(){
    int pos=position;
    obtenir_NextMot();
    if(strcmp(token,"else")==0){
        if(isElseI()==0){
            return 0;
        }
    }else{
        position=pos;
        return 0;
        //----------------------------------------->epsilon
    }
    return -1;
}


int isElseI(){
    int pos=position;
    obtenir_NextMot();
    if(strcmp(token,"{")==0){
        if(isInstructions()==0){
            obtenir_NextMot();
            if(strcmp(token,"}")==0){
                return 0;
            }
        }
    }else{
        position=pos;
        if(isInstructions()==0){
            return 0;
        }
    }
    return -1;
}

//--------------------------------------------------------->epslon
int isCnd(){
    int pos=position;
    if(isExpression()==0){
        if(isComp()==0){
                return 0;
        }
    }
    return -1;
}

//--------------------------------------------------------->epslon
int isComp(){
    int pos=position;
    if(isOpComp()==0){
        if(isExpression()==0){
            return 0;
        }
    }else{
        position=pos;
        return 0;
        //--------------------------------------------------------->epslon
    }
    return -1;
}

int isOpComp(){
    int i;
    char  tabOpComp[6][3]={"==","!=","<",">",">=","<="};
    obtenir_NextMot();
    for(i=0;i<6;i++){
        if(strcmp(token,tabOpComp[i])==0){
            return 0;
        }
    }
    return -1;
}

int isBoucle(){
    int pos=position;
    if(isWhile()==0){
        return 0;
    }else{
        position=pos;
        if(isFor()==0){
            return 0;
        }
    }
    return -1;
}

int isFor(){
    obtenir_NextMot();
    if(strcmp(token,"for")==0){
        obtenir_NextMot();
        if(strcmp(token,"(")==0){
            if(isIdent_Syn()==0){
                obtenir_NextMot();
                if(strcmp(token,"in")==0){
                    if(isExpression()==0){
                        obtenir_NextMot();
                        if(strcmp(token,")")==0){
                            obtenir_NextMot();
                            if(strcmp(token,"{")==0){
                                if(isInstructions()==0){
                                    obtenir_NextMot();
                                    if(strcmp(token,"}")==0){
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
return -1;
}

int isWhile(){
    obtenir_NextMot();
    if(strcmp(token,"while")==0){
        obtenir_NextMot();
        if(strcmp(token,"(")==0){
            if(isCnd()==0){
                obtenir_NextMot();
                if(strcmp(token,")")==0){
                    obtenir_NextMot();
                    if(strcmp(token,"{")==0){
                        if(isInstructions()==0){
                            obtenir_NextMot();
                            if(strcmp(token,"}")==0){
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return -1;
}

int isFonc(){
    int pos=position;
    if(isRfunction()==0){
        return 0;
    }else{
        position=pos;
        if(isFunctionPara()==0){
            return 0;
        }
        else {
            position=pos;
            if(isFonction1()==0) {
                return 0;
            }
            else {
                position=pos;
                if(isFonctionInf()==0) {
                    return ;
            }
            }
        }
    }
    return -1;
}
int isRfunction(){
    obtenir_NextMot();
    if(strcmp(token,"function")==0){
        obtenir_NextMot();
        if(strcmp(token,"(")==0){
                if(isParams()==0){
                    obtenir_NextMot();
                    if(strcmp(token,")")==0){
                        obtenir_NextMot();
                        if(strcmp(token,"{")==0){
                            if(isInstructions()==0){
                                obtenir_NextMot();
                                if(strcmp(token,"}")==0){
                                    return 0;
                                }
                            }
                        }
                    }
                }

        }
    }
    return -1;
}
int isFonction1(){
    obtenir_NextMot();
    if(strcmp(token,"break")==0)
        return 0;
    if(strcmp(token,"return")==0 || strcmp(token,"cos")==0 || strcmp(token,"sin")==0 || strcmp(token,"mean")==0
       || strcmp(token,"length")==0 || strcmp(token,"help")==0 || strcmp(token,"sqrt")==0){
        obtenir_NextMot();
        if(strcmp(token,"(")==0){
            if(isExpression()==0){
                obtenir_NextMot();
                if(strcmp(token,")")==0){
                    return 0;
                }
            }
        }
    }
return -1;
}

int isFonctionInf(){
    obtenir_NextMot();
    if(strcmp(token,"list")==0 || strcmp(token,"rep")==0 || strcmp(token,"min")==0 || strcmp(token,"max")==0 || strcmp(token,"plot")==0 || strcmp(token,"matrix")==0){
        obtenir_NextMot();
        if(strcmp(token,"(")==0){
            if(isParams()==0){
                obtenir_NextMot();
                if(strcmp(token,")")==0){
                    return 0;
                }
            }
        }
    }
return -1;
}

int isFunctionPara(){
    obtenir_NextMot();
    if(strcmp(token,"print")==0 || strcmp(token,"readline") ==0){
        obtenir_NextMot();
        if(strcmp(token,"(")==0){
            if(isPara()==0){
                obtenir_NextMot();
                if(strcmp(token,")")==0){
                    return 0;
                }
            }
        }
    }
return -1;
}

int isPara(){
    int pos=position;
    if(isIdent_Syn()==0){
        return 0;
    }else{
        position=pos;
        obtenir_NextMot();
        if(strcmp(token,"\"")==0){
            do{
                obtenir_NextMot();
                if(strcmp(token,"_FIN_")== 0 ){
                    return -1;
                }
            }while(strcmp(token,"\"")!=0);
                return 0;
        }
    }
    return -1;
}

int isParams(){
    int pos=position;
    if(isExpression()==0){
        if(isParam()==0){
            return 0;
        }
    }else{
        position=pos;
        return 0;
    }
    return -1;
}
int isParam(){
    int pos=position;
    obtenir_NextMot();
    nbrpar++;
    if(strcmp(token,",")==0){
        if(isExpression()==0){
            if(isParam()==0){
                return 0;
            }
        }
    }else{
        position=pos;
        return 0;
    }
    return -1;
}

