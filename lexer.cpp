#include "lexer.h"
#include <iostream>
#include <vector>
#include <string>

class Tokenizer{
    private:
    bool errorStatus = false;
    int tokenStart;
    int tokenEnd;
    int count;
    public:
    std::string input;
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
        
        if (isCom(input[count]) || isWhite(input[count])){
            std::cout << "ignored whitespace" <<"\n";
            count += 1;
        }
    }

    Token getToken(){
        //initializes a token every time that the function is run
        Token token;
        std::cout<< input[count];
        std::cout << "goin through" <<"\n";
        char currentChar = input[count];
        IgnoreCandW();
        switch(currentChar){

            case '\0': count += 1; token.type = END; break;

            case '(': count += 1; token.type = LPAR; break;
            case ')': count += 1; token.type = RPAR; break;
            case '[': count += 1; token.type = LBRACK; break;
            case ']': count += 1; token.type = RBRACK; break;
            case '{': count += 1; token.type = LBRACE; break;
            case '}': count += 1; token.type = RBRACE; break;

            case '+': count += 1; token.type = PLUS; break;
            case '-': count += 1; token.type = MINUS; break;
            case '*': count += 1; token.type = TIMES; break;
            case '/': count += 1; token.type = SLASH; break;
            case '.': count += 1; token.type = PERIOD; break;

            case '=': count += 1; token.type = EQL; break;
            case '>': count += 1; token.type = GTT; break;
            case '<': count += 1; token.type = LST; break;
            case '!': count += 1; token.type = NOT; break;

            case '"':
            {
                //increases the count by one so that it ignores the quote
                std::cout << "string"<<"\n";
                count += 1;
                token.type = STRING;
                tokenStart = count;
                while (input[count] != '"' && count < input.size()){
                    std::cout << input[count] << "\n";
                    count += 1;
                    if (currentChar == '\0') {
                        std::cout << "ERROR, MISSING QUOTE";
                        errorStatus = true;
                        break;}
                }
                //decreases the count by one to not include the quote
                
                tokenEnd = count - 1;
                count += 1;
                token.contents = input.substr(tokenStart, tokenEnd);
                std::cout << token.contents << "\n";
                //increases the count by 2 to skip over
                break;
            }
            default:
                if (isLetter(input[count])){
                    std::cout << "identifyer"<<"\n";
                    tokenStart = count;
                    token.type = IDENTIFIER;
                    while (isLetter(input[count]) || isNum(input[count]) || input[count] == ':'){
                        count += 1;
                    }
                    tokenEnd = count - 1;
                    token.contents = input[tokenStart,tokenEnd];
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
                        errorStatus = true;
                        break;
                    }

                }
                else if (isNum(input[count])){
                    std::cout<< "number";
                    bool floatstatus = false;
                    tokenStart = count;
                    token.type = INT;
                    while (isNum(input[count] && count < input.size())){
                        count += 1;
                        std::cout << input[count] <<"\n";
                        if (input[count] == '.'){
                            if (floatstatus) {
                                token.type = FLOAT;
                            count += 1;
                            }
                            else{
                                std::cout << "Error, more than two decimals";
                                errorStatus = true;
                                break;
                            }
                        }
                    }
                    tokenEnd = count;
                    token.contents = input.substr(tokenStart, tokenEnd);;
                    std::cout << token.contents << "\n";
                }

        }
    }

    std::vector<Token> lexInput(){
        std::cout << input<<"\n";
        std::vector<Token> lexvec;
        count = 0;
        tokenStart = 0;
        bool islexing = true;
        while (islexing){
            std::cout << count<<"\n";
            if (count >= input.size()) islexing = false;
            else if (errorStatus) islexing = false;
            else{
                lexvec.push_back(getToken());
                if (count >= input.size()) islexing = false;
            }
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
    Tokenizer tokenizer;
    std::string userinput;
    std::cout << "user>";
    getline(std::cin, userinput);
    tokenizer.input = userinput;
    tokenizer.lexInput();
}
