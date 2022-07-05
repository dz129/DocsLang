#include "lexer.h"
#include <iostream>
/*
          Eval::
            O 
          / | \
        num Op O  
             / | \
          num  Op  O
                / | \
             num  Op num (num gets completed here) and then the tree is filled out recursively
*/


//if identifier is eval::, do this
struct evalTree{
    int firstnum;
    Token operation;
    //as recursion finishes, second num will get filled out, and the operation will happen
    int secondnum;
    evalTree* next;
};

//if identifier is print::, do this
struct printTree{
    std::string firstPrint;
    Token operation;
    std::string secondPrint;
    printTree* next;
};

//the scanIdentifier function initializes this root
struct identifierRoot{
    evalTree* evaluation;
    printTree* printStatement;
};