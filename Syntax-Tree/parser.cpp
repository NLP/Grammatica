#include "parser.h"

/**
 * @brief Parser::Parser Default Constructor
 */
Parser::Parser(){

}

/**
 * @brief Parser::Parser Constructor
 * @param G Grammar
 * @param words Words
 */
Parser::Parser(const Grammar& G, const Wvector& words){
    _G = G;
    _words = words;
}

/**
 * @brief Parser::setGrammar Set the Grammar
 * @param G Grammar
 */
void Parser::setGrammar(const Grammar& G){
    _G = G;
}

/**
 * @brief Parser::setSentence Set the sentence
 * @param W the sentence
 */
void Parser::setSentence(const Wvector& W){
    _words = W;
}

/**
 * @brief Parser::getGrammar Returns the grammar
 * @return grammar
 */
Grammar Parser::getGrammar(){
    return _G;
}

/**
 * @brief Parser::getSentence Returns the sentence
 * @return sentence
 */
Wvector Parser::getSentence(){
    return _words;
}

/**
 * @brief Parser::getTrees Returns the valid syntax trees
 * @return the syntax trees
 */
STvector Parser::getTrees(){
    return _valid;
}

/**
 * @brief Parser::parse Parses the sentence and creates the trees
 * @return the trees
 */
STvector Parser::parse(){
    SyntaxTree S(new TNpair(GtSpair(SENTENCE,SyntaxWord()))); //At the beginning, CURRENT is at the true root
    std::size_t cutoff = 0;
    while(recDescent(S,cutoff)){ //RecDescends based on the CURRENT pointer in the tree
//        cout << "WE HAVE A TREE" << endl;
        _valid.insert(_valid.end(),S);
//        std::cout << S << std::endl;
//        cin.get();
//        cout << "finding first incomplete of S" << endl;
        if(!findFirstIncomplete(S)){ //Sets the CURRENT to the first slowest subtree that has more defs to explore
            break; //If it cannot find any more subtrees with more defs to explore, then stop
        }
//        cout << "Found it and moved current" << endl;
//        cout << *S.getCurrent() << endl;
//        cout << S.leavesBefore() << endl;
        cutoff = S.leavesBefore();
//        cout << "Found new cutoff: " << cutoff << endl;
        removePartial(S);
//        cout << "removed partial" << endl;
    } //As long as recdescent is able to continue making trees
//    std::cout << "After while" << std::endl;
//    using namespace std;
    for(std::size_t i = 0; i < _valid.size(); ++i){
        assignType(_valid[i]);
        attachWords(_valid[i]);
        assignHeadWords(_valid[i]);
        assignObjects(_valid[i]);
//        cout << "SENTENCE TYPE: " << sentenceLookUp[_valid[i].getSentenceType()] << endl;
//        cout << _valid[i] << endl;
    }
//    for(std::size_t i = 0; i < _valid.size(); ++i){
//        cout << "SENTENCE TYPE: " << sentenceLookUp[_valid[i].getSentenceType()] << endl;
//        cout << _valid[i] << endl;
//    }
    return _valid;
}

std::vector<SyntaxWord> Parser::getAll(const SyntaxTree &S){
    return S.getAll();
}

std::vector<SyntaxWord> Parser::getObj(const SyntaxTree &S, SyntaxObject O){
    return S.getObj(O);
}

/**
 * @brief Parser::findFirstIncomplete Finds the first incomplete node
 * (The first phrase who has yet to go through all of its definitions))
 * @param S The tree
 * @return True if there is, False otherwise
 */
bool Parser::findFirstIncomplete(SyntaxTree& S){

    if(S.atLeaf())
        return false;
    for(std::size_t i = 0; i < S.childNum(); ++i){
        S.shiftDown(i);
        if(findFirstIncomplete(S))
            return true;
        S.shiftUp();
    }
    return !getNextDef(S.getPhrase(),S.getDef()).empty();
}

/**
 * @brief Parser::removePartial Destroys all of the nodes to the right of current
 * @param S the tree
 */
void Parser::removePartial(SyntaxTree &S){
    TNpair* c = S.getCurrent();
    S.shiftToRoot();
    bool f = false;
    S = removePartial(S.getCurrent(),c,f);
    S.shiftTo(c);
//    cout << "Partially Removed: " << S << endl;

//    TNpair* p = S.getParent(S.getCurrent());
//    cout << "Current: " << *S.getCurrent() << endl;
//    cout << "Parent of Current: " << *p << endl;
//    for(std::size_t i = S.childIndex(p,S.getCurrent()) + 1; i < p->children().size(); ++i){
//        for(std::size_t j = 0; j < p->children()[i]->children().size(); ++j){
//            cout << "i: " << i << ", j: " << j << endl;
//            cout << *p->children()[i]->children()[j] << endl;
////            rt::clear(p->children()[i]->children()[j]);
//        }
//    }
//    cout << "First for done" << endl;
//    TNpair* q = S.getParent(p);
////    cout << "Found parent of parent of current: " << *q << endl;
//    if(!q) cout << "grandparent is null" << endl;
//    while(q){
//        cout << "In while" << endl;
//        for(std::size_t i = S.childIndex(q,p) + 1; i < q->children().size(); ++i){
//            rt::clear(q->children()[i]);
//        }
//        p = q;
//        q = S.getParent(p);
//    }
    //    cout << S << endl;
}

/**
 * @brief Parser::removePartial recusively destroys the right
 * @param root the root
 * @param target the current
 * @return the new tree
 */
TNpair* Parser::removePartial(TNpair *root, TNpair *target, bool& found){
//    using namespace std;
//    cout << "in remove Partial" << endl;
//    cout << "Root: " << *root << endl;
//    cout << "Target: " << *target << endl;
//    cout << "found: " << found << endl;
//    if(target == root){
//        for(std::size_t i = 0; i < root->children().size(); ++i){
//            child.insert(child.end(),removePartial(root->children()[i],target,found));
//        }
//        found = true;
//        return new TNpair(root->data(),child);
//    }
    TNpair::TNvector child;
    for(std::size_t i = 0; i < root->children().size(); ++i){
//        cout << "Child: " << i << endl;
//        child.insert(child.end(),removePartial(root->children()[i],target,found));
//        if(target == root->children()[i]){
//            cout << "found the target" << endl;
//            child.insert(child.end(),removePartial(root->children()[i],target,found));
//            cout << "all children of target done" << endl;
//            found = true;
//            break;
//        }
        if(!found){
//            cout << "found false" << endl;
            child.insert(child.end(),removePartial(root->children()[i],target,found));
//            cout << "Added the child of " << i << endl;
        }
        else{
//            cout << "found true" << endl;
            child.insert(child.end(),new TNpair(root->children()[i]->data()));
//            cout << "Added just the data of " << i << endl;
        }
    }
    if(target == root) found = true;
//    cout << "Returning a copy of itself " << endl;
    return new TNpair(root->data(),child);
}

/**
 * @brief Parser::recDescent recursively parses the sentence
 * using the recursive descent top-down parsing method
 * @param S the tree
 * @param c the cutoff (How many words into the sentence does it start)
 * @return True if it is successful, False otherwise
 */
bool Parser::recDescent(SyntaxTree& S, std::size_t& c){
//    cin.get();
//    cout << "in RecDescent" << endl;
//    if(S.getPhrase() == SENTENCE)
//        c = 0;
//    cout << "EHFIE" << endl;
//    cout << "S so far: " << S << endl << endl;
//    cout << "c = " << c << endl;
//    if(c == _words.size()){
//        --c;
//        return false;
//    }
//    cout << "Scur: " << *S.getCurrent() << endl;
//    cout << "init def is " << (S.getDef().empty() ? "EMPTY":"NOT EMPTY") << endl;
//    cout << "The phrase is " << phraseLookUp[S.getPhrase()] << endl;
//    if(S.leafNum() > _words.size()) return false;
    GPlist def = getNextDef(S.getPhrase(),S.getDef());
//    cout << "Def: ";
//    for(std::size_t i = 0; i < def.size(); ++i){
//        cout << def[i] << "|";
//    }cout << endl;
    if(def.empty() && S.getDef().empty()){
//        cout << "Def is empty OR root is leaf" << endl;
        Word W;
        if(S.atLastLeaf()){
//            cout << "S is at the last leaf" << endl;
             W = getNextWord(c + 1);
//             cout << "The word at c+1: " << W << endl;
            if(*W.getTypes().begin() != IGNORETHIS){
//                --c;
                return false;
            }
//            cout << "at the last word" << endl;
            W = getNextWord(c);
        }
        else
            W = getNextWord(c);
//        cout << "Got the next word: " << W << endl;
        for(WordType cT = getNextType(W,IGNORETHIS); cT != IGNORETHIS; cT = getNextType(W,cT)){
            GrammarPhrase g = WTtoGP[cT];
//            cout << "The WT converted to gp: " << phraseLookUp[g] << endl;
            if(S.getPhrase() == g){
//                cout << "THERE IS A MATCH" << endl;
                ++c;
                return true;
            }
        }
        return false;
    }
    if(!S.getDef().empty()){
        S.removeDef();
    }
//    cout << "Def is not leaf" << endl;
    while(!def.empty()){
//        cout << "def is still avail" << endl;
        if(S.getDef().empty()) S.addDef(def);

//        cout << "Added def" << endl;
//        cout << "S with added def: " << S << endl;
        bool check = false;
//        cout << "Going into each child" << endl;
        for(std::size_t i = 0; i < S.childNum(); ++i){
//            cout << "i: " << i << endl;
            S.shiftDown(i);
//            cout << "The CHild: " << *S.getCurrent() << endl;
//            cout << "shifted down to i" << endl;
//            cout << *S.getCurrent() << endl;
            check = recDescent(S,c);
//            cout << "Popped out of recursion" << endl;
//            cin.get();
            if(!check && i != 0){
                S.shiftUp();
//                cout << "recur returned false" << endl;
//                cout << "Not first child" << endl;
//                c -= i;
//                cout << "Now C: " << c << endl;
//                 --c;
//                cout << "C after first check: " << c << endl;

//                cout << "i here: " << i << endl;
                if(S.getChildAt(i-1) && !S.getChildAt(i-1)->isLeaf()){
                    c -= rt::leaves(S.getChildAt(i-1));
                    i -= 2;

                }
                else{
                    while(i > 0 && S.getChildAt(i-1) && S.getChildAt(i-1)->isLeaf()){
    //                    cout << "In while" << endl;
    //                    cout << "i: " << i << endl;
    //                    cout << "c: " << c << endl;
                        --c;
                        --i;
                    }
                    if(i == 0){

                        S.removeDef();
                        break;
                    }
                }


//                cout << "C: " << c << endl;
//                cout << "I: " << i << endl;

                S.shiftDown(0);
//                --i;

//                i -= 2;
            }
            else if(!check && i == 0){
//                cout << "recur returned false" << endl;
//                cout << "First child" << endl;

                //Got to its previous child
                //Recur that child again
//                c -= rt::leaves(S.getCurrent());
                S.shiftUp();
                S.removeDef();
                break;
//                if(S.getPhrase() == SENTENCE) c = 0;
//                if(i == 0)

//                else --i;
//                if(i != 0) --i;


//                cout << "removing children and STOP" << endl;
//                break;
            }
            S.shiftUp();
//            cout << "shifted back up" << endl;
//            cout << *S.getCurrent() << endl;
        }
        if(check){
//            cout << "recur returned true for all children" << endl;
            return true;
        }
        def = getNextDef(S.getPhrase(),def);
//        if(S.getCurrent()->data()._d.first == SENTENCE)c = 0;
//        cout << "Got next def: ";
//        for(std::size_t i = 0; i < def.size(); ++i){
//            cout << def[i] << "|";
//        }cout << endl;
    }
//    cout << "No more defs for this phrase and no successful recur, returning false" << endl;

    return false;
}

/**
 * @brief Parser::attachWords Attachs the words to the leaves of the tree
 * @param S the tree
 */
void Parser::attachWords(SyntaxTree& S){
    std::size_t i = 0;
    TNpair::TNvector L = S.getLeaves(); //NEED LEAVES FUNCTION
    TNpair::TNvector::iterator it = L.begin();
    while(it != L.end()){
        Word W = getNextWord(i);
        removeAllOtherTypes(W,GPtoWT[(*it)->data()._d.first]);
        (*it)->data()._d.second.setWord(W);
        ++it;
        ++i;
    }
}

/**
 * @brief Parser::assignHeadWords Assigns the head words
 * @param S the tree
 */
void Parser::assignHeadWords(SyntaxTree& S){
    S.assignHeads();
}

/**
 * @brief Parser::assignObjects Assigns the objects
 * @param S the tree
 */
void Parser::assignObjects(SyntaxTree& S){
    S.assignObjects();
}

void Parser::assignType(SyntaxTree &S){
    S.determineType();
//    std::cout << "ASSIGNTYPE: " << sentenceLookUp[S.getSentenceType()] << std::endl;
}

void Parser::removeAllOtherTypes(Word &W, WordType trueType){
    W = Word(Token(W.getTokenString(),ALPHA),{trueType},W.getDefinitions());

}

/**
 * @brief Parser::getNextWord Gets the next word in the sentence
 * @param i the word to get
 * @return  the word, or an IGNORETHIS word if not valid
 */
Word Parser::getNextWord(std::size_t i){
//    cout << "size of words: " << _words.size() << endl;
    if(i >= _words.size()){
        return Word();
    }
//    cout << "words at c: " << _words[i] << endl;
    return _words[i];
}

/**
 * @brief Parser::getNextDef Gets the next definition
 * @param g the phrase
 * @param def the current def
 * @return the next def, OR the first def if current is empty, OR and empty def if current is the last
 */
GPlist Parser::getNextDef(GrammarPhrase g, GPlist def){
    std::vector<GPlist> defs = _G.getDefinition(g);
//    cout << "defs in getNextDef: " << endl;
//    cout << "defs size " << defs.size() << endl;
//    cout << "phrase of defs: " << phraseLookUp[g] << endl;
//    for(std::size_t i = 0; i < defs.size(); ++i){
//        for(std::size_t j = 0; j < defs[i].size(); ++j){
//            cout << i << "," << j << ":" <<  defs[i][j] << "|";
//        }cout << endl;
//    }cout << endl;
//    cout << "defs[0] " << endl;
//    for(std::size_t i = 0; i < defs[0].size(); ++i){
//        cout << defs[0][i] << "|";
//    }cout << endl;
//    cout << "checking if empty" << endl;
    if(def.empty()){
//        cout << "def is empty" << endl;
        if(defs.empty()){
            return GPlist();
        }
        return defs[0];
    }
//    cout << "def is not empty" << endl;
    for(std::size_t i = 0; i < defs.size(); ++i){
        if(defs[i] == def){
            if(i == defs.size() - 1){
                return GPlist();
            }
            return defs[++i];
        }
    }
    return GPlist();

}

/**
 * @brief Parser::getNextType Gets the next Word Type of the Word
 * @param W the word
 * @param T the current type
 * @return the next type, OR the first type if the current is IGNORETHIS, OR IGNORETHIS if current is last
 */
WordType Parser::getNextType(const Word& W, WordType T){
    WTset wt = W.getTypes();
    if(T == IGNORETHIS)
        return *wt.begin();
    WTset::iterator it = wt.begin();
    while(it != wt.end()){
        if(*it == T){
            ++it;
            if(it == wt.end())
                return IGNORETHIS;
            return *it;
        }
        ++it;
    }
    return IGNORETHIS;
}
