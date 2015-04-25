#include "parser.h"

Parser::Parser(){

}

Parser::Parser(const Grammar& G, const Wvector& words){
    _G = G;
    _words = words;
}

void Parser::setGrammar(const Grammar& G){
    _G = G;
}

void Parser::setSentence(const Wvector& W){
    _words = W;
}

Grammar Parser::getGrammar(){
    return _G;
}

Wvector Parser::getSentence(){
    return _words;
}

STvector Parser::getTrees(){
    return _valid;
}

STvector Parser::parse(){
    SyntaxTree S(TNpair(SENTENCE,SyntaxWord())); //At the beginning, CURRENT is at the true root
    int cutoff = 0;
    while(recDescent(S,cutoff)){ //RecDescends based on the CURRENT pointer in the tree
        _valid.insert(_valid.end(),S);
        if(!findFirstIncomplete(S)) //Sets the CURRENT to the first slowest subtree that has more defs to explore
            break; //If it cannot find any more subtrees with more defs to explore, then stop
        cutoff = S.leavesBefore();
    } //As long as recdescent is able to continue making trees
    return _valid;
}

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
//    if(def.empty())
//        return false;
//    else return true;

}

bool Parser::recDescent(SyntaxTree& S, std::size_t c){
    if(S.getPhrase() == SENTENCE)
        c = 0;
    GPlist def = getNextDef(S.getPhrase(),S.getDef());
    if(def.empty()){
        Word W;
        if(S.atLastLeaf()){
             W = getNextWord(c + 1);
            if(*W.getTypes().begin() != IGNORETHIS)
                return false;
            W = getNextWord(c);
        }
        else
            W = getNextWord(c);
        ++c;
        for(WordType cT = getNextType(W,IGNORETHIS); cT != IGNORETHIS; cT = getNextType(W,cT)){
            if(S.getPhrase() == WTtoGP[cT]){
                return true;
            }
        }
        return false;
    }
    while(!def.empty()){
        S.addDef(def);
        bool check = false;
        for(std::size_t i = 0; i < S.childNum(); ++i){
            S.shiftDown(i);
            check = recDescent(S,c);
            if(!check){
                S.removeDef();
                break;
            }
            S.shiftUp();
        }
        if(check){
            return true;
        }
        def = getNextDef(S.getPhrase(),S.getDef());
    }
    return false;
}

void Parser::attachWords(SyntaxTree& S){
    std::size_t i = 0;
    TNpair::TNvector L = S.leaves(); //NEED LEAVES FUNCTION
    TNpair::TNvector::iterator it = L.begin();
    while(it != L.end()){
        (*it)->data().second.setWord(getNextWord(i));
        ++it;
        ++i;
    }
}

void Parser::assignHeadWords(SyntaxTree& S){
    S.assignHeads();
}

void Parser::assignObjects(SyntaxTree& S){
    S.assignObjects();
}

Word& Parser::getNextWord(std::size_t i){
    if(i >= _words.size())
        return Word(Token(),{IGNORETHIS});
    return _words[i];
}

GPlist Parser::getNextDef(GrammarPhrase g, GPlist def){
    std::vector<GPlist> defs = _G.getDefinition(g);
    if(def.empty())
        return defs[0];
    std::vector<GPlist>::iterator it = defs.begin();
    while(it != defs.end()){
        if(*it == def){
            ++it;
            if(it == defs.end())
                return GPlist();
            return *it;
        }
        ++it;
    }
    return GPlist();
}

WordType Parser::getNextType(const Word& W, WordType T){
    WTset wt = W.getTypes();
    if(T == IGNORETHIS)
        return wt[0];
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
