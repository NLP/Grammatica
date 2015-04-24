#include "syntaxtree.h"
/**
 * @brief SyntaxTree::isPoS Determines whether a grammar phrase is a part of speech
 * @param gp The grammar phrase
 * @return True/False
 * NOTE: Uses the posList for GrammarPhrases in CONFIG
 */
bool SyntaxTree::isPoS(const GrammarPhrase& gp) const{
    for(auto& i : posList){
        if(i == gp)
            return true;
    }
    return false;
}
//Assign each node beginning from the bottom a head syntaxword
void SyntaxTree::assignHead(TreeNode<GtSpair>* root){
    if(!root) return;
    if(root->isLeaf()) return; //The tree should already have the words attached to it
    TreeNode<GtSpair>::TNvector::iterator it = root->children().begin();
    std::vector<SyntaxWord> s;
    while(it != root->children().end()){
        assignHead(*it);
        s.insert(s.begin(),(*it)->data().second);
        ++it;
    }
    SyntaxWord sw = findHeadWord(root->data().first,s);
    if(sw._so == S_INVALID) std::cout << "Something fucked up" << std::endl;
    root->data().second = sw;
}

TreeNode<GtSpair>* SyntaxTree::findSyntax(TreeNode<GtSpair> *root, SyntaxObject syntax) const{
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
//Finds the head syntaxword given a grammar phrase and a list of syntaxwords
SyntaxWord SyntaxTree::findHeadWord(const GrammarPhrase& gp, const std::vector<SyntaxWord> &s){
    std::vector<SyntaxWord>::const_iterator it = s.begin();
    while(it != s.end()){
        if(it->isHeadWord(gp)) return *it;
    }
    return SyntaxWord();
//isHeadWord
}

SyntaxTree::SyntaxTree():Tree<GtSpair>::Tree(){

}

SyntaxTree::SyntaxTree(const SyntaxTree &S):Tree<GtSpair>::Tree(S){

}

SyntaxTree::~SyntaxTree(){

}

SyntaxTree &SyntaxTree::operator =(const SyntaxTree &S){
    Tree<GtSpair>::_root = rt::copy(S._root);
    _current = _root;
    return *this;
}

SyntaxWord SyntaxTree::syntax(const TreeNode<GtSpair> *branch) const{
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

std::vector<TreeNode<GtSpair> *> SyntaxTree::getAll() const{
    std::vector<TreeNode<GtSpair>*> all;
    for(auto& i : soList)
        all.insert(all.begin(),findSyntax(_root,i));
    return all;
}

void SyntaxTree::assignSyntax(TreeNode<GtSpair> *root){
    if(!root) return;
    root->data().second._so = MAINVERB;
    std::vector<TreeNode<GtSpair>*>::iterator it = root->children().begin();
    while(it != root->children().end()){ //For each child
        //Check if there is a noun phrase
        //If there is a noun phrase, then the head word of that node is the subject
        //Evertyhing else in the noun phrase has NONE
        //Check if there is a noun phrase in the verbphrase
        //If there is, then the head word of that noun phrase is the direct object
        //Everything else that is independent in the noun phrase has NONE
        //The independent verb of the verphrase is the main verb
        //Check if there is a preposition phrase in the verb phrase
        //If there is, the head word of that phrase is the indirect object
        //Everything else will be none
    }
}

void SyntaxTree::attachWords(const std::vector<Word>& w){
    std::vector<Word>::const_iterator it = w.begin();
    while(it != w.end()){

    }
}
