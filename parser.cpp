#include "lexer.h"
#include "parser.h"
#include <vector>
#include <stack>
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
        std::stack<std::string> stringstack;
        std::stack<std::string> opstack;
        if (tokenvec.size() <= 2){
            printRoot -> print = tokenvec[1].contents;
            return;
            }
        else{
            printRoot -> print = tokenvec[1].contents;
            printRoot -> next = new printTree;
            printTree* temp = printRoot -> next;
            for (int i = 2; i < tokenvec.size(); i++) {
                if (tokenvec[i].type == STRING){
                    temp -> print = tokenvec[i].contents;
                    temp -> next = new printTree;
                    temp = temp -> next;
                }
                else if (tokenvec[i].type == PLUS){
                    temp -> operation = tokenvec[i].type;
                    temp -> next = new printTree;
                    temp = temp -> next;
                }
                else{
                    printRoot -> syntaxError = true;
                }
            }
            return;
        }
    }


    std::string evalEval(){

    }

    std::string evalPrint(){
        std::string returnValue;
        std::stack<std::string> stringFinal;
        std::stack<TokenType> operations;
        printTree* temp = printRoot;
        if (printRoot -> syntaxError) return "SYNTAX ERROR";
        while (temp != NULL){
            if(temp -> operation == PLUS){
                operations.push(temp -> operation);
                temp = temp -> next;
            }
            else{
                stringFinal.push(temp -> print);
                temp = temp -> next;
                }

        }
        if (operations.size() != 0 && stringFinal.size() - 1 != operations.size()) return "SYNTAX ERROR";
        else{
            while (!stringFinal.empty()){
                returnValue = returnValue + stringFinal.top();
                stringFinal.pop();
            }
        }
        return returnValue;
    }
    void print(){
        std::cout << evalPrint();
    }
};
