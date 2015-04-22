#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H
#include "Tree.h"
//Holds a grammar rule tree attached at the very ends as leafs the words
//Then for each subtree, it finds the head word
//Give it functions to access these head words and identify which is which

class SyntaxTree:public Tree{
public:
    SyntaxTree();
private:
};

#endif // SYNTAXTREE_H
