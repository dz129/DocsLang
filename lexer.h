#include <iostream>
enum TokenType{
    //literals
    INT,
    FLOAT,
    STRING,
    BOOL,
    IDENTIFIER,
    //operations
    PLUS,
    MINUS,
    TIMES,
    SLASH,
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

struct Tokenizer{
    //tracks the location of the characters being tracked
    //restarts when letters and numbers finish
    //restarts when operations happen
    //---------
    //if there is a error, turn this to true so that the lexer stops running
    bool errorStatus = false;
    char *input;
    //---------
    //these track the start and end of numbers and strings
    int tokenstart;
    int tokenend;
    //---------
    //tracks the progress of the tokenization
    int count;
};