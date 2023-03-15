#ifndef CORE_H
#define CORE_H

// This enum serves as our tokens
enum core {
    // Keywords
    AND, //0
    BEGIN, //1
    DO, //2
    ELSE,//3
    END,//4
    IF,//5
    IN,//6
	INTEGER,//7
    IS,//8
    NEW,//9
    NOT,//10
    OR,//11
    OUT,//12
    PROCEDURE,//13
    RECORD,//14
    THEN,//15
    WHILE,//16
    // Symbols
    ADD,//17
    SUBTRACT,//18
    MULTIPLY,//19
    DIVIDE,//20
    ASSIGN,//21
    EQUAL,//22
    LESS,//23
    COLON,//24
    SEMICOLON,//25
    PERIOD,//26
	COMMA,//27
    LPAREN,//28
    RPAREN,//29
    LBRACE,//30
    RBRACE,//31
    // Others
    CONST,//32
    ID,//33
    EOS,//34
    ERROR//35
};

#endif