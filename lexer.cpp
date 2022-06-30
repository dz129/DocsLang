#include "lexer.h"
#include <iostream>
#include <vector>
#include <string>

class lexer{
    private:
    Tokenizer tokenizer;
    public:
    bool isWhite(char c){
        return (c == ' ') || (c == '\t') || (c == '\f') || (c == '\v');
    }
    bool isEndLine(char c){
        return (c == '\n') || (c == '\r');
    }
    bool isLetter(char c){
        return isalpha(c);
    }
    bool isNum(char c){
        return isdigit(c);
    }
    bool isCom(char c){
        return (c == '#');
    }

    void IgnoreCandW(){
        //if there is a whitespace or comment, we will just move the tokenizer's index forward to keep scanning
        //this needs to eb changed so that comments do nothing
        if (isCom(tokenizer.input[tokenizer.count]) || isWhite(tokenizer.input[tokenizer.count])){
            tokenizer.count += 1;
        }
    }

    Token getToken(){
        //initializes a token every time that the function is run
        Token token;
        std::cout<<tokenizer.input[tokenizer.count];
        std::cout << "goin through";
        char currentChar = tokenizer.input[tokenizer.count];
        IgnoreCandW();
        switch(currentChar){

            case '\0': tokenizer.count += 1; token.type = END; break;

            case '(': tokenizer.count += 1; token.type = LPAR; break;
            case ')': tokenizer.count += 1; token.type = RPAR; break;
            case '[': tokenizer.count += 1; token.type = LBRACK; break;
            case ']': tokenizer.count += 1; token.type = RBRACK; break;
            case '{': tokenizer.count += 1; token.type = LBRACE; break;
            case '}': tokenizer.count += 1; token.type = RBRACE; break;

            case '+': tokenizer.count += 1; token.type = PLUS; break;
            case '-': tokenizer.count += 1; token.type = MINUS; break;
            case '*': tokenizer.count += 1; token.type = TIMES; break;
            case '/': tokenizer.count += 1; token.type = SLASH; break;
            case '.': tokenizer.count += 1; token.type = PERIOD; break;

            case '=': tokenizer.count += 1; token.type = EQL; break;
            case '>': tokenizer.count += 1; token.type = GTT; break;
            case '<': tokenizer.count += 1; token.type = LST; break;
            case '!': tokenizer.count += 1; token.type = NOT; break;

            case '"':
            {
                //increases the count by one so that it ignores the quote
                std::cout << "string";
                tokenizer.count += 1;
                token.type = STRING;
                tokenizer.tokenstart = tokenizer.count;
                while (currentChar != '"'){
                    tokenizer.count += 1;
                    if (currentChar == '\0') {
                        std::cout << "ERROR, MISSING QUOTE";
                        tokenizer.errorStatus = true;
                        break;}
                }
                //decreases the count by one to not include the quote
                tokenizer.tokenend = tokenizer.count - 1;
                token.contents = tokenizer.input[tokenizer.tokenstart,tokenizer.tokenend];
                //increases the count by 2 to skip over
                tokenizer.count += 2;
                break;
            }
            default:
                if (isLetter(tokenizer.input[tokenizer.count])){
                    tokenizer.tokenstart = tokenizer.count;
                    token.type = IDENTIFIER;
                    while (isLetter(tokenizer.input[tokenizer.count]) || isNum(tokenizer.input[tokenizer.count]) || tokenizer.input[tokenizer.count] == ':'){
                        tokenizer.count += 1;
                    }
                    tokenizer.tokenend = tokenizer.count - 1;
                    token.contents = tokenizer.input[tokenizer.tokenstart,tokenizer.tokenend];
                    if (token.contents == "eval::"){
                        token.type = EVAL;
                        break;
                    }
                    else if (token.contents == "print::"){
                        token.type = PRINT;
                        break;
                    }
                    else if (token.contents == "if"){
                        token.type = IF;
                        break;
                    }
                    else if (token.contents == "while"){
                        token.type = WHILE;
                        break;
                    }
                    else if (token.contents == "return"){
                        token.type = RETURN;
                        break;
                    }
                    else{
                        std::cout << "Syntax Error";
                        tokenizer.errorStatus = true;
                        break;
                    }

                }
                else if (isNum(tokenizer.input[tokenizer.count])){
                    bool floatstatus = false;
                    tokenizer.tokenstart = tokenizer.count;
                    token.type = INT;
                    while (isNum(tokenizer.input[tokenizer.count])){
                        tokenizer.count += 1;
                        if (tokenizer.input[tokenizer.count] == '.'){
                            if (floatstatus) {
                                token.type = FLOAT;
                            tokenizer.count += 1;
                            }
                            else{
                                std::cout << "Error, more than two decimals";
                                tokenizer.errorStatus = true;
                                break;
                            }
                        }
                    }
                    tokenizer.tokenend = tokenizer.count;
                    token.contents = tokenizer.input[tokenizer.tokenstart,tokenizer.tokenend];
                }

        }
    }

    std::vector<Token> lexInput(std::string input){
        std::cout << input;
        std::vector<Token> lexvec;
        Tokenizer tokenizer;
        tokenizer.input = input;
        tokenizer.count = 0;
        tokenizer.tokenstart = 0;
        bool islexing = true;
        while (islexing){
            std::cout << tokenizer.count;
            if (tokenizer.count >= input.size()) islexing = false;
            else if (tokenizer.errorStatus) islexing = false;
            else{
                lexvec.push_back(getToken());
            }
            tokenizer.count += 1;
        }
        return lexvec;
    }

    std::string tokenToString(TokenType type){
        switch(type){
            case INT: return "int"; 
            case FLOAT: return "float";
            case STRING: return "string";
            case BOOL: return "bool";
            case IDENTIFIER: return "Identifier";
            case PLUS: return "plus";
            case MINUS: return "minus";
            case TIMES: return "times";
            case SLASH: return "slash";
            case PERIOD: return "period";
            case EQL: return "eql";
            case GTT: return "gtt";
            case LST: return "lst";
            case GTE: return "gte";
            case LTE: return "lte";
            case NOT: return "not";
            case LPAR: return "lpar";
            case RPAR: return "rpar";
            case LBRACE: return "lbrtace";
            case RBRACE: return "rbrace";
            case LBRACK: return "lbrack";
            case RBRACK: return "rbrack";
            case SEMI: return "semi";
            case COMMA: return "comma";
            case EVAL: return "eval";
            case PRINT: return "print";
            case IF: return "if";
            case WHILE: return "while";
            case RETURN: return "return";
            case END: return "end";
            case COMMENT: return "comment";

        }
    }
    void debugger(std::vector<Token> lexvec){
        for (int i; i < lexvec.size(); i++){
            std::cout << tokenToString(lexvec[i].type) << "\n";
        }
    }
};

int main(){
    lexer Lexer;
    std::string input;;
        std::cout << "user>";
        getline(std::cin, input);
        Lexer.lexInput(input);
}
