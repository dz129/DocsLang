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
        std::cout<< input[count] << "\n";
        std::cout << "goin through" <<"\n";
        IgnoreCandW();
        switch(input[count]){

            case '\0': count += 1; token.type = END; return token;

            case '(': count += 1; token.type = LPAR; return token;
            case ')': count += 1; token.type = RPAR; return token;
            case '[': count += 1; token.type = LBRACK; return token;
            case ']': count += 1; token.type = RBRACK; return token;
            case '{': count += 1; token.type = LBRACE; return token;
            case '}': count += 1; token.type = RBRACE; return token;

            case '+': count += 1; token.type = PLUS; return token;
            case '-': count += 1; token.type = MINUS; return token;
            case '*': count += 1; token.type = TIMES; return token;
            case '/': count += 1; token.type = SLASH; return token;
            case '.': count += 1; token.type = PERIOD; return token;

            case '=': count += 1; token.type = EQL; return token;
            case '>': count += 1; token.type = GTT; return token;
            case '<': count += 1; token.type = LST; return token;
            case '!': count += 1; token.type = NOT; return token;

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
                    if (input[count] == '\0') {
                        std::cout << "ERROR, MISSING QUOTE" << "\n";
                        errorStatus = true;
                        break;
                        }
                }
                //decreases the count by one to not include the quote
                
                tokenEnd = count - 1;
                count += 1;
                token.contents = input.substr(tokenStart, tokenEnd);
                std::cout << token.contents << "\n";
                //increases the count by 2 to skip over
                return token;
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
                        return token;
                    }
                    else if (token.contents == "print::"){
                        token.type = PRINT;
                        return token;
                    }
                    else if (token.contents == "if"){
                        token.type = IF;
                        return token;
                    }
                    else if (token.contents == "while"){
                        token.type = WHILE;
                        return token;
                    }
                    else if (token.contents == "return"){
                        token.type = RETURN;
                        return token;
                    }
                    else{
                        std::cout << "Syntax Error"<< "\n";
                        errorStatus = true;
                        return token;
                    }

                }
                else if (isNum(input[count])){
                    std::cout<< "number" << "\n";
                    bool floatstatus = false;
                    tokenStart = count;
                    token.type = INT;
                    while (isNum(input[count]) && count < input.size()){
                        count += 1;
                        std::cout << input[count] <<"\n";
                        if (input[count] == '.'){
                            if (floatstatus) {
                                token.type = FLOAT;
                            count += 1;
                            }
                            else{
                                std::cout << "Error, more than two decimals"<< "\n";
                                errorStatus = true;
                                break;
                            }
                        }
                    }
                    tokenEnd = count;
                    token.contents = input.substr(tokenStart, tokenEnd);;
                    std::cout << token.contents << "\n";
                    return token;
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

