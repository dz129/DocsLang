#include <iostream>
enum TokenType{
    //literals
    INT,
    FLOAT,
    STRING,
    BOOL,
    IDENTIFIER,
    //operations
    PLUS = 50,
    MINUS = 50,
    TIMES = 51,
    SLASH = 51,
    PERIOD,
    EQL,
    GTT,
    LST,
    GTE,
    LTE,
    NOT,
    //seperators
    LPAR,
    RPAR,
    LBRACK,
    RBRACK,
    LBRACE,
    RBRACE,
    SEMI,
    COMMA,
    //keywords
    EVAL,
    PRINT,
    IF,
    WHILE,
    RETURN,
    END,
    //comment 
    COMMENT,
};

class Token{
    //stores all the necessary values for the token
    public:
    TokenType type;
    std::string contents;
};

