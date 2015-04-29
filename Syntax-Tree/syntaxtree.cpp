#include "syntaxtree.h"

/**
 * @brief SyntaxTree::SyntaxTree Default Constructor
 */
SyntaxTree::SyntaxTree(): Tpair::Tree(){
    Tpair::_root = new TreeNode<GtSpair>(GtSpair(SENTENCE,SyntaxWord()));
    _current = _root;
}

/**
 * @brief SyntaxTree::SyntaxTree Constructor
 * @param root the root
 */
SyntaxTree::SyntaxTree(TNpair* root):Tpair::Tree(root){

}

/**
 * @brief SyntaxTree::SyntaxTree Copy Constructor
 * @param S SyntaxTree
 */
SyntaxTree::SyntaxTree(const SyntaxTree& S):Tpair::Tree(S){

}

/**
 * @brief SyntaxTree::operator = assignment operator
 * @param S Syntax Tree
 * @return this
 */
SyntaxTree& SyntaxTree::operator =(const SyntaxTree& S){
    Tpair::_root = rt::copy(S._root);
    _current = _root;
    return *this;
}

/**
 * @brief SyntaxTree::~SyntaxTree Destructor
 */
SyntaxTree::~SyntaxTree(){

}

/**
 * @brief SyntaxTree::addDef Adds the Definition to the current node (the children)
 * @param def the definition (children)
 */
void SyntaxTree::addDef(GPlist def){
    for(std::size_t i = 0; i < def.size(); ++i)
        Tpair::addNode(Tpair::_current,GtSpair(def[i],SyntaxWord()));
}

/**
 * @brief SyntaxTree::removeDef Removes the definition of current_exception()
 * NOTE: It will remove all of the children of the definitions
 */
void SyntaxTree::removeDef(){
    Tpair::_current->children().clear();
}

/**
 * @brief SyntaxTree::getDef Returns the definition as a vector of grammar phrases of current
 */
GPlist SyntaxTree::getDef(){
    TNpair::TNvector v = Tpair::_current->children();
    GPlist def;
    for(std::size_t i = 0; i < v.size(); ++i)
        def.insert(def.end(),v[i]->data()._d.first);
    return def;
}

/**
 * @brief SyntaxTree::getPhrase Returns the phrase at current
 * @return the phrase
 */
GrammarPhrase SyntaxTree::getPhrase(){
    return Tpair::_current->data()._d.first;
}

/**
 * @brief SyntaxTree::atLeaf Checks if current is a leaf
 * @return True if it is, False otherwise
 */
bool SyntaxTree::atLeaf(){
    return Tpair::_current->isLeaf();
}

/**
 * @brief SyntaxTree::getLastLeaf Returns the Rightmost bottom leaf
 * @return the last leaf
 */
TNpair* SyntaxTree::getLastLeaf(){
    TNpair* leaf = Tpair::_root;
    while(!leaf->isLeaf())
        leaf = leaf->children()[leaf->children().size() - 1];
    return leaf;
}

/**
 * @brief SyntaxTree::getFirstLeaf Returns the leftmost bottom leaf
 * @return the first leaf
 */
TNpair* SyntaxTree::getFirstLeaf(){
    TNpair* leaf = Tpair::_root;
    while(!leaf->isLeaf())
        leaf = leaf->children()[0];
    return leaf;
}

/**
 * @brief SyntaxTree::atLastLeaf Checks if current is at the last leaf
 * @return True if it is, False otherwise
 */
bool SyntaxTree::atLastLeaf(){
    return Tpair::_current == getLastLeaf();
}

/**
 * @brief SyntaxTree::atFirstLeaf Checks if current is at the first leaf
 * @return True if it is, False otherwise
 */
bool SyntaxTree::atFirstLeaf(){
    return Tpair::_current == getFirstLeaf();
}

/**
 * @brief SyntaxTree::leavesBefore Calculates the number of leaves before current
 * @return the number of leaves before current
 */
std::size_t SyntaxTree::leavesBefore(){
    using namespace std;
//    cout << "In leavesbefore" << endl;
    TNpair* head = rt::parent(_root,_current);
//    if(head) cout << "Head: " << *head << endl;
//    else cout << "Head: EMPTY" << endl;
    std::size_t sum = 0;
    while(head){
//        cout << "In while" << endl;
        for(std::size_t i = 0; i < head->children().size(); ++i){
//            cout << "i: " << i << endl;
            if(head->children()[i] == _current){
//                cout << "in for if" << endl;
                break;
            }
//            cout << "head->children()[i] != _current" << endl;
            sum += rt::leaves(head->children()[i]);
//            cout << "new sum: " << sum << endl;
        }
        head = rt::parent(_root,head);
//        cout << "got new head" << endl;
        if(head == Tpair::_root) break;
    }
//    cout << "Done/ sum: " << sum << endl;
    return sum;
}

/**
 * @brief SyntaxTree::childIndex Calculates which child is the child (from 0)
 * @param parent the parent
 * @param child the child
 * @return the index of the child vector of parent
 */
size_t SyntaxTree::childIndex(TNpair* parent,TNpair *child){
    for(std::size_t i = 0; i < parent->children().size(); ++i){
        if(parent->children()[i] == child)
            return i;
    }
    return -1;
}

std::vector<SyntaxWord> SyntaxTree::getAll() const{
    std::vector<SyntaxWord> All;
    std::vector<TNpair*> L = rt::allLeaves(_root);
    for(std::size_t i = 0; i < L.size(); ++i){
        All.insert(All.end(),L[i]->data()._d.second);
    }
    return All;
}

std::vector<SyntaxWord> SyntaxTree::getObj(SyntaxObject S) const{
    std::vector<SyntaxWord> Obj;
    std::vector<TNpair*> L = rt::allLeaves(_root);
    for(std::size_t i = 0; i < L.size(); ++i){
        if(L[i]->data()._d.second.getSyntax() == S){
            Obj.insert(Obj.end(),L[i]->data()._d.second);
        }
    }
    return Obj;
}

/**
 * @brief SyntaxTree::assignHeads assigns the head words to each node
 */
void SyntaxTree::assignHeads(){
    recurHead(_root);
}
/**
 * @brief SyntaxTree::assignObjects assigns the syntax to each node
 */
void SyntaxTree::assignObjects(){
    setSubj(Tpair::_root);
    setMV(Tpair::_root);
    setDO(Tpair::_root);
    setIDO(Tpair::_root);
}

/**
 * @brief SyntaxTree::recurHead recursively finds the head word for each subtree
 * @param root the root
 */
void SyntaxTree::recurHead(TNpair* root){
    if(!root) return;
    if(root->isLeaf())
        return; //It is assumed to already have the word attached to it
    for(std::size_t i = 0; i < root->children().size(); ++i)
        recurHead(root->children()[i]);
    Word W = getHeadWord(root->data()._d.first,root->children());
    //Once it analyzes each of its children, find out which head word is for this node
    root->data()._d.second.setWord(W);
}

/**
 * @brief SyntaxTree::recurObj recursively assigns the object to each node
 * @param root the root
 * @param W the Word that is the definee of the object
 * @param S the object
 * NOTE: The objects must have already been found. This just assigns the other nodes
 */
void SyntaxTree::recurObj(TNpair* root, const Word& W, SyntaxObject S){
    //Assumed to be a normal declarative
    //Add cases later for different types of sentences, ie more complex ones
    //like questions and commands

    //The head word of a declarative is the main verb
    if(!root) return;
    for(std::size_t i = 0; i < root->children().size(); ++i)
        recurObj(root->children()[i],W,S);
    if(root->data()._d.second.getWord().getTokenString() == W.getTokenString())
        root->data()._d.second.setSyntax(S);

    //determine sentence struct
    //if declarative
    //subj is the head noun of the noun phrase before the main verb
    //the mainverb is the head verb of the sentence
    //the do(if any) is the head noun of the noun phrase that comes directly after the main verb
    //the ido is the head noun of the prep phrase
    //HOWEVER, the do and ido can be swapped
    //Ex: John gives the ball to him & John gives him the ball

}

/**
 * @brief SyntaxTree::getHeadWord Finds the headword of the grammar phrase in a vector of words
 * @param g the grammar phrase
 * @param W the vector of words
 * @return the head word
 */
Word SyntaxTree::getHeadWord(GrammarPhrase g, TNpair::TNvector W){
    switch(g){
        case NOUNPHRASE:{
            Word hold;
            for(std::size_t i = 0; i < W.size(); ++i){
                WordType wt = *W[i]->data()._d.second.getWord().getTypes().begin(); //There should ONLY be one type at this moment
                if(wt == noun && W[i]->data()._d.first == NOUN){
                    return W[i]->data()._d.second.getWord();
                }
                if(wt == noun && W[i]->data()._d.first == NOUNPHRASE){
                    hold = W[i]->data()._d.second.getWord();
                }
            }
            return hold;
            break;
        }
        case SENTENCE:
        case VERBPHRASE:{
            Word hold;
            for(std::size_t i = 0; i < W.size(); ++i){
                WordType wt = *W[i]->data()._d.second.getWord().getTypes().begin(); //There should ONLY be one type at this moment
                if(wt == verb && W[i]->data()._d.first == VERB){
                    return W[i]->data()._d.second.getWord();
                }
                if(wt == verb && W[i]->data()._d.first == VERBPHRASE){
                    hold = W[i]->data()._d.second.getWord();
                }
            }
            return hold;
            break;
        }
        case PREPPHRASE:{
            Word hold;
            for(std::size_t i = 0; i < W.size(); ++i){
                WordType wt = *W[i]->data()._d.second.getWord().getTypes().begin(); //There should ONLY be one type at this moment
                if(wt == preposition && W[i]->data()._d.first == PREP){ //NEEDS WordType Prep
                    return W[i]->data()._d.second.getWord();
                }
                if(wt == preposition && W[i]->data()._d.first == PREPPHRASE){
                    hold = W[i]->data()._d.second.getWord();
                }
            }
            return hold;
            break;
        }

        default:{

            break;
        }
    }
    return Word();
}

/**
 * @brief SyntaxTree::findPhrase Finds the phrase in the tree
 * @param start the start subtree
 * @param find the phras
 * @return the pointer to the node, OR nullptr if not found
 */
TNpair *SyntaxTree::findPhrase(TNpair *start, GrammarPhrase find){
    for(std::size_t i = 0; i < start->children().size(); ++i){
        TNpair* r = findPhrase(start->children()[i],find);
        if(r) return r;
    }
    if(start->data()._d.first == find)
        return start;
    return nullptr;
}

/**
 * @brief SyntaxTree::setSubj Sets the subject of the sentence
 * @param sentence the root
 */
void SyntaxTree::setSubj(TNpair *sentence){
    TNpair* r = findPhrase(sentence,NOUNPHRASE);
    if(!r) return;
    r->data()._d.second.setSyntax(SUBJECT);
    Word W = r->data()._d.second.getWord();
    recurObj(sentence,W,SUBJECT);
}

/**
 * @brief SyntaxTree::setMV Sets the main verb of the sentence
 * @param sentence the root
 */
void SyntaxTree::setMV(TNpair *sentence){
    sentence->data()._d.second.setSyntax(MAINVERB);
    recurObj(sentence,sentence->data()._d.second.getWord(),MAINVERB);
}

/**
 * @brief SyntaxTree::setDO Sets the Direct Object of the sentence
 * @param sentence the root
 */
void SyntaxTree::setDO(TNpair *sentence){
    TNpair* r = findPhrase(sentence,VERBPHRASE);
    if(!r) return;
    r = findPhrase(r,NOUNPHRASE);
    if(!r) return;
    r->data()._d.second.setSyntax(DIRECTOBJ);
    Word W = r->data()._d.second.getWord();
    recurObj(sentence,W,DIRECTOBJ);
}

/**
 * @brief SyntaxTree::setIDO Sets the Indirect Object of the sentence
 * @param sentence the root
 */
void SyntaxTree::setIDO(TNpair *sentence){
    TNpair* r = findPhrase(sentence,VERBPHRASE);
    if(!r) return;
    r = findPhrase(r,PREPPHRASE);
    if(!r) return;
    r = findPhrase(r,NOUNPHRASE);
    if(!r) return;
    r->data()._d.second.setSyntax(INDIRECTOBJ);
    Word W = r->data()._d.second.getWord();
    recurObj(sentence,W,INDIRECTOBJ);
}

