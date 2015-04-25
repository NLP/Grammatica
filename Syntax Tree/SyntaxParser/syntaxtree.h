#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H
#include "Tree.h"
#include "../../Grammar Structure/Grammar-with-Map/grammar.h"
#include "../../../Parser/Tagger/word.h"
#include "../../../CONFIG/config.h"
#include "syntaxword.h"
typedef std::pair<GrammarPhrase,SyntaxWord> GtSpair;
typedef TreeNode<GtSpair> TNpair;
typedef Tree<GtSpair> Tpair;
class SyntaxTree: public Tree<GtSpair>{
private:
public:
    SyntaxTree();
    SyntaxTree(TNpair* root);
    SyntaxTree(const SyntaxTree& S);
    SyntaxTree& operator =(const SyntaxTree& S);
    ~SyntaxTree();

    void assignHeads();
    void assignObjects();


    //Do stuff to current
    //Create child (Must not have any children)
    void addDef(GPlist def);
    //Remove the child
    void removeDef();
    GPlist getDef();
    GrammarPhrase getPhrase();
    bool atLeaf();
    TNpair* getLastLeaf();
    TNpair* getFirstLeaf();
    bool atLastLeaf();
    bool atFirstLeaf();
    std::size_t leavesBefore();
};



#endif // SYNTAXTREE_H
