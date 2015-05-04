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
        _valid[i].shiftToRoot();
//        cout << "1" << endl;
        assignType(_valid[i]);
//        cout << "2" << endl;
        attachWords(_valid[i]);
//        cout << "3" << endl;
        assignHeadWords(_valid[i]);
//        cout << "4(/' _ ')/ ^ /(. o .)|" << endl;
        assignObjects(_valid[i]);
//        cout << "SENTENCE TYPE: " << sentenceLookUp[_valid[i].getSentenceType()] << endl;
//        cout << _valid[i] << endl;
    }
//    cout << "out "<< endl;
    removeTrees();
    return _valid;
}

/**
 * @brief Parser::getAll returns a vector of all syntax words
 * @param S the syntax tree
 * @return the vector
 */
std::vector<SyntaxWord> Parser::getAll(const SyntaxTree &S){
    return S.getAll();
}

/**
 * @brief Parser::getObj returns a vector of the syntax
 * @param S the syntax tree
 * @param O the syntax object
 * @return the vector
 */
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
    if(S.atLeaf()) return false;
    for(std::size_t i = 0; i < S.childNum(); ++i){
        S.shiftDown(i);
        if(findFirstIncomplete(S)) return true;
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
//            cout << "Match this: " << phraseLookUp[S.getPhrase()] << endl;
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
//            cout << "Popped out of recur/*s*/ion" << endl;
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
//                    S.shiftDown();
//                    break; //Why did I remove this again?
                }
                else{
                    while(i > 0 && S.getChildAt(i-1) && S.getChildAt(i-1)->isLeaf()){
    //                    cout << "In while" << endl;
    //                    cout << "i: " << i << endl;
    //                    cout << "c: " << c << endl;
                        --c;
                        --i;
                    }
//                    if(S.getChildAt(i)->isLeaf()){
//                        --c;
//                        --i;
//                    }
                    if(i == 0){

                        S.removeDef();
                        break;
                    }
                }

//                --i;
//                cout << "C: " << c << endl;
//                cout << "I: " << i << endl;

                S.shiftDown(i); //Previously 0
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
            if(!S.getParent(S.getCurrent())){
//                cout <<"For some reason it is already all the way at root" << endl;
                if(check && S.leafNum() == _words.size()) return true;
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
    TNpair::TNvector L = S.getLeaves();
    for(std::size_t i = 0; i < L.size(); ++i){
        Word W = getNextWord(i);
        removeAllOtherTypes(W,GPtoWT[L[i]->data()._d.first]);
        L[i]->data()._d.second.setWord(W);
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

/**
 * @brief Parser::assignType sets the sentence type
 * @param S syntax tree
 */
void Parser::assignType(SyntaxTree &S){
    S.determineType();
}

/**
 * @brief Parser::removeAllOtherTypes removes all other types for the words
 * @param W Word
 * @param trueType the actual type
 */
void Parser::removeAllOtherTypes(Word &W, WordType trueType){
    W = Word(Token(W.getTokenString(),ALPHA),{trueType},W.getDefinitions());
}

/**
 * @brief Parser::removeTrees removes certain trees that do not have the same length as the sentence
 */
void Parser::removeTrees(){
    STvector::iterator it = _valid.begin();
    for(std::size_t i = 0; i < _valid.size(); ++i,++it){
        if(_valid[i].leafNum() != _words.size()){
            _valid.erase(it);
            --i;
            --it;
        }
    }
    it = _valid.begin();
    for(std::size_t i = 0; i < _valid.size(); ++i, ++it){
        if(_valid[i].getSentenceType() == INTERROGATIVE){
            TNpair* f = _valid[i].getFirstLeaf();
            if(f->data()._d.first == WHWORD){
                std::string w = f->data()._d.second.getWord().getTokenString();
                if((w.compare("Who") == 0 || w.compare("What") == 0 ||
                        w.compare("Where") == 0 || w.compare("When") == 0)
                        && f->data()._d.second.getSyntax() == S_INVALID){
                    _valid.erase(it);
                    --i;
                    --it;
                }
            }
        }
    }
}

/**
 * @brief Parser::getNextWord Gets the next word in the sentence
 * @param i the word to get
 * @return  the word, or an IGNORETHIS word if not valid
 */
Word Parser::getNextWord(std::size_t i){
    if(i >= _words.size()) return Word();
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
    if(def.empty()){
        if(defs.empty()) return GPlist();
        return defs[0];
    }
    for(std::size_t i = 0; i < defs.size(); ++i){
        if(defs[i] == def){
            if(i == defs.size() - 1) return GPlist();
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
    if(T == IGNORETHIS) return *wt.begin();
    WTset::iterator it = wt.begin();
    while(it != wt.end()){
        if(*it == T){
            ++it;
            if(it == wt.end()) return IGNORETHIS;
            return *it;
        }
        ++it;
    }
    return IGNORETHIS;
}
