#include "syntaxtree.h"
SyntaxTree::SyntaxTree(): Tpair::Tree(){

}

SyntaxTree::SyntaxTree(TNpair* root):Tpair::Tree(root){

}

SyntaxTree::SyntaxTree(const SyntaxTree& S):Tpair::Tree(S){

}

SyntaxTree& SyntaxTree::operator =(const SyntaxTree& S){
    Tpair::_root = rt::copy(S._root);
    _current = _root;
    return *this;
}

SyntaxTree::~SyntaxTree(){

}

//Do stuff to current
//Create child (Must not have any children)
void SyntaxTree::addDef(GPlist def){
    Tpair::addNode(Tpair::_current,def);
}

//The def to be removed must be leaves
void SyntaxTree::removeDef(){
    Tpair::_current->children().clear();
}

GPlist SyntaxTree::getDef(){
    TNpair::TNvector v = Tpair::_current->children();
    GPlist def;
    for(std::size_t i = 0; i < v.size(); ++i){
        def.insert(def.end(),v[i]->data().first);
    }
    return def;
}

GrammarPhrase SyntaxTree::getPhrase(){
    return Tpair::_current->data().first;
}

bool SyntaxTree::atLeaf(){
    return Tpair::_current->isLeaf();
}

TNpair* SyntaxTree::getLastLeaf(){
    TNpair* leaf = Tpair::_root;
    while(!leaf->isLeaf())
        leaf = leaf->children()[leaf->children().size() - 1];
    return leaf;
}

TNpair* SyntaxTree::getFirstLeaf(){
    TNpair* leaf = Tpair::_root;
    while(!leaf->isLeaf())
        leaf = leaf->children()[0];
    return leaf;
}

bool SyntaxTree::atLastLeaf(){
    return Tpair::_current == getLastLeaf();
}

bool SyntaxTree::atFirstLeaf(){
    return Tpair::_current == getFirstLeaf();
}

std::size_t SyntaxTree::leavesBefore(){
    TNpair* head = rt::parent(_root,_current);
    std::size_t sum = 0;
    while(head){
        for(std::size_t i = 0; i < head->children().size(); ++i){
            if(head->children()[i] == _current)
                break;
            sum += rt::leaves(head->children()[i]);
        }
        head = rt::parent(_root,head);
    }
    return sum;
}

void SyntaxTree::assignHeads(){

}

void SyntaxTree::assignObjects(){

}
