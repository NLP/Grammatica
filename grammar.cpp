#include "grammar.h"


void Grammar::createInitialRule(){
    _grammar.insert(mmap::value_type(SENTENCE,GPlist()));
}

Grammar::Grammar(){
    createInitialRule();

}

void Grammar::addRule(const GrammarPhrase &define, const GPlist &rule){
    GPlist g = getDefinition(define);
    if(g.empty())
        _grammar.erase(define);
    _grammar.insert(mmap::value_type(define,rule));

}

void Grammar::removeRule(const GrammarPhrase &define, const GPlist &rule){
    std::pair<mmap::iterator,mmap::iterator> p = _grammar.equal_range(define);


    for(mmap::iterator it = p.first; it != p.second; ++it){
        if(rule == it->second){
            _grammar.erase(it);
        }
    }

}

std::ostream &operator <<(std::ostream &out, const Grammar &G){
    for(mmap::const_iterator it = G._grammar.begin(); it != G._grammar.end(); ++it){
        out << it->first << ": {";

        for(GPlist::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt){
            out << " (" << *jt << "),";
        }
        out << "}\n";
    }
    return out;
}

GPlist &Grammar::getDefinition(const GrammarPhrase &define){
    mmap::iterator it = _grammar.find(define);
    if(it != _grammar.end())
        return it->second;
    else{
        GPlist g;
        return g;
    }
}

GrammarPhrase Grammar::getDefiner(const GPlist &rule){
    for(mmap::iterator it = _grammar.begin(); it != _grammar.end(); ++it){
        if(it->second == rule)
            return it->first;
    }
    return UNKNOWN;
}
