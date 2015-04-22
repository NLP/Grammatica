#include "syntaxtree.h"


void SyntaxTree::assignSyntax(TreeNode<GtSpair>* root){
    if(!root) return; //possible throw
    if(root->isLeaf()) root->data().second = findHeadWord(root);
    TreeNode<GtSpair>::TNvector::iterator it = root->children().begin();
    while(it != root->children().end()){
        assignSyntax(*it);
        ++it;
    }
}

TreeNode<GtSpair>* SyntaxTree::findSyntax(TreeNode<GtSpair> *root, SyntaxObject syntax){
    if(!root) return nullptr;
    if(isPoS(root->data().first) && root->data().second._so == syntax)
        return root;
    TreeNode<GtSpair>::TNvector::iterator it = root->children().begin();
    TreeNode<GtSpair>* found = nullptr;
    while(it != root->children().end()){
        if((*it)->data().second._so == SUBJECT){
            found = findSyntax(*it,syntax);
            break;
        }
        ++it;
    }
    return found;
}

SyntaxWord SyntaxTree::findHeadWord(TreeNode<GtSpair> *root){
    if(!root) return SyntaxWord(UNKNOWN,NLP::Word());
    if(root->isLeaf()) return root->data().second;
    TreeNode<GtSpair>::TNvector::iterator it = root->children().begin();
    while(it != root->children().end()){
        SyntaxWord W = findHeadWord(*it);
        if(isHeadWord(root->data().first,W))
            return W;
        ++it;
    }
    return SyntaxWord(UNKNOWN,NLP::Word());
}

SyntaxTree::SyntaxTree():Tree<GtSpair>::Tree(){

}

SyntaxTree::SyntaxTree(const SyntaxTree &S):Tree<GtSpair>::Tree(S){

}

SyntaxTree::~SyntaxTree(){
    Tree<GtSpair>::~Tree();
}

SyntaxTree &SyntaxTree::operator =(const SyntaxTree &S){
    Tree<GtSpair>::_root = rt::copy(S._root);
    _current = _root;
    return *this;
}

SyntaxWord SyntaxTree::syntax(const TreeNode<GtSpair> *branch){
    return branch->data().second;
}

TreeNode<GtSpair> *SyntaxTree::getMainVerb() const{
    return findSyntax(_root,MAINVERB);
}

TreeNode<GtSpair> *SyntaxTree::getSubject() const{
    return findSyntax(_root,SUBJECT);
    //Probably for more complex sentences, though the sentence should end up as NP VP
//    TreeNode<GtSpair>::TNvector::iterator it = subj->children().begin();
//    while(it != subj->children().end()){
//        if(*it->data().first == NOUNPHRASE)
//    }
}

TreeNode<GtSpair> *SyntaxTree::getDO() const{
    return findSyntax(_root,DIRECTOBJ);
}

TreeNode<GtSpair> *SyntaxTree::getIDO() const{
    return findSyntax(_root,INDIRECTOBJ);
}

std::vector<TreeNode<GtSpair> *> &SyntaxTree::getAll() const{
    std::vector<TreeNode<GtSpair>*> all;
    for(auto& i : soList)
        all.insert(all.begin(),findSyntax(_root,i));
    return all;
}
