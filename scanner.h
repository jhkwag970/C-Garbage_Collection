#ifndef SCANNER_H
#define SCANNER_H

#include "core.h"


//Check if the returned tokenString contains any symbol that is not in the core.h
int errorChecker();

//It loops through the tokenString to find the ending index
int errorIndex();

//Check if the returned tokenString is the number character.
int numberChecker();

//match the number from core.h to the tokenString with the keyword, symbol, and others in the core.h
void tokenToEnum();

//Check if the tokenString contains the symbol and (keyword or Constant or ID) at same time. 
//If it does, symbolChecker seperate symbol from tokenString.
void symbolChecker(int tokenSize);

// Opens the file, find the first token
int scanner_open(char* filename);

// Frees memory allocated for the scanner
int scanner_close();

// move pointer to previous token
void prevToken();

// Returns the current token (enum value)
int currentToken();

// Finds the next token (or the first token when called by scanner_open)
int nextToken();

// Passes back the string value, so the parse tree (project 2) will be able to store identifiers
void getId(char* identifier);

// Passes back the constant value, so the parse tree (project 2) will be able to store const values
int getConst();

#endif