#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H
#include "Tree.h"
#include "../../Grammar Structure/GrammarStructure/cfgzero.h"
//Holds a grammar rule tree attached at the very ends as leafs the words
//Then for each subtree, it finds the head word
//Give it functions to access these head words and identify which is which
enum SyntaxObject{
    UNKNOWN,
    SUBJECT,
    MAINVERB,
    DIRECTOBJ,
    INDIRECTOBJ,
    MODIFIERVERB
};
typedef std::pair<GrammarPhrase,SyntaxObject> GtSpair;
class SyntaxTree: public Tree<GtSpair>{
private:
    void assignSyntax();
public:
    SyntaxTree();
    SyntaxTree(const SyntaxTree& S);
    ~SyntaxTree();
    SyntaxTree& operator =(const SyntaxTree& S);

    SyntaxObject syntax(const TreeNode<GtSpair>* branch);
    TreeNode<GtSpair>* getMainVerb() const;
    TreeNode<GtSpair>* getSubject() const;
    TreeNode<GtSpair>* getDO() const;
    TreeNode<GtSpair>* getIDO() const;
};

#endif // SYNTAXTREE_H
