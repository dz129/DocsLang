#include "lexer.h"
#include "parser.h"
#include <vector>
#include <iostream>

class parser{
    //right now we will only support two operations, print and eval
    //first lets build the eval root
    //next we will add if statents
    private:
    public:
    std::vector<Token> tokenvec; // this will be from the tokenizer
    int vecIndex = 1;
    TokenType identifier = tokenvec[0].type;
    identifierRoot* root;
    evalTree* evalRoot;
    printTree* printRoot;
    void scanIdentifier(){
        // if the first token is identifier, that means it hasn't been assinged, so it is a syntax error
        if (identifier == IDENTIFIER) {
            std::cout << "Syntax Error"; 
            return;
            } 
        else{
            if (identifier == EVAL){
                root = new identifierRoot;
                root -> evaluation = new evalTree;
                evalTree* evalRoot = root -> evaluation;
            }
            else if (identifier == PRINT){
                root = new identifierRoot;
                root -> printStatement = new printTree;
                printTree* printRoot = root -> printStatement;
            }
        }
    }

    void fillEval(){

    }

    void fillPrint(int vecIndex, std::vector<Token> tokenvec, printTree* root){
        if (vecIndex >= tokenvec.size()) return;
        printTree* newprint = new printTree;
        tokenvec[vecIndex].contents = 
    }

    std::string evalEval(){

    }

    std::string evalPrint(){

    }
    void print(){

    }
};
