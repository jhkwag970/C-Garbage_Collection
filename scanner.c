#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "scanner.h"
#include "core.h"

// Below are the values we want to persist as the scanner runs

// This maintains a pointer to the file
static FILE* fp;

// This is the string making up the current token
static char* tokenString;

// This is the enum value for the current token
static int token;
static int preToken;

// Below are the functions that make up the scanner

//errorChecker():
//Check if the returned tokenString contains any symbol that is not in the core.h
//
//Paramse: 
//  NA
//Returns: 
//  0 if tokenString contains the symbol from the core.h
//  1 if tokenString does not contain the symbol in the core.h
int errorChecker(){
    int idx=0;
    int error=0;
    while(tokenString[idx] != '\0'){
        char ch = tokenString[idx];
        if((ch>=33 && ch <= 39) || (ch >=62 && ch<=64) || (ch==92) || (ch>= 94 && ch <= 96) || (ch >=123 && ch<=126) ){
            error=1;
            break;
        }
        idx++;
    }
    return error;
}

/*errorIndex()
It loops through the tokenString to find the ending index

Params:
    NA
Returns:
    int idx: last index of tokenString
*/
int errorIndex(){
    int idx=0;
    while(tokenString[idx] != '\0'){
        idx++;
    }
    return idx;
}

//symbolChecker():
//Check if the tokenString contains the symbol and (keyword or Constant or ID) at same time. 
//If it does, symbolChecker seperate symbol from tokenString.
//
//Params:
//  tokenSize: size of Current tokenString
//Returns: NA
void symbolChecker(int tokenSize){
    if(tokenSize!=0){    
        tokenString[tokenSize]='\0';
        fseek( fp, -1, SEEK_CUR);
    }
}

//numberChekcer()
//Check if the returned tokenString is the number character.
//
//Params:
//  NA
//Returns:
//  0 if at least one character in the tokenString has the character other than number character
//  1 if all the characters in the tokenString has the number character.
int numberChecker(){
    int idx=0;
    int isNumber=1;
    while(tokenString[idx] != '\0'){
        char ch = tokenString[idx];
        if(!(ch>=48 && ch<=57)){
            isNumber=0;
            break;
        }
        idx++;
    }
    return isNumber;

}

//tokenToEnumber()
//match the number from core.h to the tokenString with the keyword, symbol, and others in the core.h
//
//Params:
//  NA
//Returns:
//  NA
void tokenToEnum(){
    if(!strcmp(tokenString, "and")){ //keyword
        token=0;
        token=AND;
    }else if(!strcmp(tokenString, "begin")){
        token=1;
        token=BEGIN;
    }else if (!strcmp(tokenString, "do")){
        token=2;
        token=DO;
    }else if (!strcmp(tokenString, "else")){
        token=3;
        token=ELSE;
    }else if (!strcmp(tokenString, "end")){
        token=4;
        token=END;
    }else if (!strcmp(tokenString, "if")){
        token=5;
        token=IF;
    }else if (!strcmp(tokenString, "in")){
        token=6;
        token=IN;
    }else if (!strcmp(tokenString, "integer")){
        token=7;
        token=INTEGER;
    }else if (!strcmp(tokenString, "is")){
        token=8;
        token=IS;
    }else if (!strcmp(tokenString, "new")){
        token=9;
        token=NEW;
    }else if (!strcmp(tokenString, "not")){
        token=10;
        token=NOT;
    }else if (!strcmp(tokenString, "or")){
        token=11;
        token=OR;
    }else if (!strcmp(tokenString, "out")){
        token=12;
        token=OUT;
    }else if (!strcmp(tokenString, "procedure")){
        token=13;
        token=PROCEDURE;
    }else if (!strcmp(tokenString, "record")){
        token=14;
        token=RECORD;
    }else if (!strcmp(tokenString, "then")){
        token=15;
        token=THEN;
    }else if (!strcmp(tokenString, "while")){
        token=16;
        token=WHILE;
    }else if (!strcmp(tokenString, "+")){//symbol
        token=17;
        token=ADD;
    }else if (!strcmp(tokenString, "-")){
        token=18;
        token=SUBTRACT;
    }else if (!strcmp(tokenString, "*")){
        token=19;
        token=MULTIPLY;
    }else if (!strcmp(tokenString, "/")){
        token=20;
        token=DIVIDE;
    }else if (!strcmp(tokenString, ":=")){
        token=21;
        token=ASSIGN;
    }else if (!strcmp(tokenString, "=")){
        token=22;
        token=EQUAL;
    }else if (!strcmp(tokenString, "<")){
        token=23;
        token=LESS;
    }else if (!strcmp(tokenString, ":")){
        token=24;
        token=COLON;
    }else if (!strcmp(tokenString, ";")){
        token=25;
        token=SEMICOLON;
    }else if (!strcmp(tokenString, ".")){
        token=26;
        token=PERIOD;
    }else if (!strcmp(tokenString, ",")){
        token=27;
        token=COMMA;
    }else if (!strcmp(tokenString, "(")){
        token=28;
        token=LPAREN;
    }else if (!strcmp(tokenString, ")")){
        token=29;
        token=RPAREN;
    }else if (!strcmp(tokenString, "[")){
        token=30;
        token=LBRACE;
        
    }else if (!strcmp(tokenString, "]")){
        token=31;
        token=RBRACE;
    }else if (tokenString[0] == '\0'){//other
        token=34;
        token=EOS;
    }else{
        if (errorChecker()){
            token=35;
            token=ERROR;
            printf("Scanner Error: %c is causing the error.\n", tokenString[errorIndex()-1]);
            exit(0);
        }else if(numberChecker()){
            int tokenNumber = atoi(tokenString);
            if(tokenNumber >=0 && tokenNumber <= 1009){
                token=32;
                token=CONST;
            }else{
                token =35;
                token=ERROR;
                printf("Scanner Error: %s is too big number\n", tokenString);
                exit(0);
            }
        }else{
            token=33;
            token=ID;
        }
    }
}

// Opens the file, find the first token
int scanner_open(char* filename) {
    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Error: File %s couldn't be opened!\n", filename);
    }
    tokenString = NULL;
    preToken=-1;
    return nextToken();
}

// Frees memory allocated for the scanner
int scanner_close() {
    fclose(fp);
    free(tokenString);
}

// Returns the current token (enum value)
int currentToken() {
	// You will need to fill this in with appropriate things
    //free(tokenString);
    return token;
}

// move pointer and token to previous token
void prevToken(){
    int cnt = strlen(tokenString) * -1;
    printf("%s :size if %d\n", tokenString, cnt);
    fseek( fp, cnt-1, SEEK_CUR);
}

// Finds the next token (or the first token when called by scanner_open)
int nextToken(){
    int first=1;
    int tokenSize=0;
    int numChecker=0;
    tokenString = calloc(20, sizeof(char));
    while(1){
        char ch = fgetc(fp);

        //If file is End Of File, stop the function
        if(ch == EOF){
            break;
        }
        //If file start with the ' ' or enter or tab or return, file skips the tokenString until find the character.
        //If tokenString is found and tokenString encounters the ' ' or enter or tab or return, stop the function
        if(ch == ' ' || ch =='\n' || ch == '\t' || ch == '\r'){
            if(first){
                continue;
            }else{
                break;
            }
        }
        first=0;
        tokenString[tokenSize]=ch;

        //If tokenString encounters the symbol, stop the function.
        if ((ch>=40 && ch <=47) || (ch>=58 && ch <= 61)|| ch == 91 || ch == 93){
            symbolChecker(tokenSize);
            if(ch==58){
                char next = fgetc(fp);
                if(next == '='){
                    tokenSize++;
                    tokenString[tokenSize]=next;
                }else{
                    fseek( fp, -1, SEEK_CUR);
                }
            }
            break;
        }


        //If the tokenString has number and (keyword or ID), then separte the tokenString        
        if(tokenSize != 0){
            if((numChecker==tokenSize) &&!(tokenString[tokenSize]>=48 && tokenString[tokenSize]<=57)){
                tokenString[tokenSize]='\0';
                fseek( fp, -1, SEEK_CUR);
                break;
            }
        }
        if((tokenString[tokenSize]>=48 && tokenString[tokenSize]<=57)){
            numChecker++;
        }
        tokenSize++;

    } 
    tokenToEnum();
    return token;
}
  
// Passes back the string value, so the parse tree (project 2) will be able to store identifiers
void getId(char* identifier) {
    strcpy(identifier, tokenString);
}

// Passes back the constant value, so the parse tree (project 2) will be able to store const values
int getConst() {
    return atoi(tokenString);
}