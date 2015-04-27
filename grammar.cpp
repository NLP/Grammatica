#include "grammar.h"

/**
 * @brief Grammar::createInitialRule Creates the initial rule of SENTENCE -> ...
 * Only called in the Constructor
 */
void Grammar::createInitialRule(){
    _grammar.insert(mmap::value_type(SENTENCE,GPlist()));
}

/**
 * @brief Grammar::Grammar Default Constructor. Creates a new multimap with a single blank definition for a sentence.
 * The reason for the initial sentence definition is because ALL grammar structures MUST begin with a sentence definition.
 */
Grammar::Grammar(){
    createInitialRule();
}

/**
 * @brief Grammar::addRule Adds the specified relationship by creating and adding a pair in the multimap
 * @param define This is the LHS of the definition. This is what is being defined, i.e. the key
 * @param rule This is the RHS. This is the definition, i.e. the value
 * NOTE: This will take care of the empty sentence definition
 */
void Grammar::addRule(const GrammarPhrase &define, const GPlist &rule){
    std::vector<GPlist> g = getDefinition(define);
    if(g.empty())
        _grammar.erase(define);
    _grammar.insert(mmap::value_type(define,rule));
}

/**
 * @brief Grammar::removeRule Removes the specified rule by finding and deleting it from the multimap
 * @param define The phrase that is defined by the rule
 * @param rule The definition itself
 * NOTE: No need for finding the exact position in the map. Just create a copy of the definition and pass it in.
 */
void Grammar::removeRule(const GrammarPhrase &define, const GPlist &rule){
    std::pair<mmap::iterator,mmap::iterator> p = _grammar.equal_range(define);
    for(mmap::iterator it = p.first; it != p.second; ++it)
        if(rule == it->second) _grammar.erase(it);
}

/**
 * @brief operator << insertion operator. Writes out the Grammar Structure to the out stream
 * @param out the output stream
 * @param G the Grammar Structure
 * @return the output stream reference
 */
std::ostream &operator <<(std::ostream &out, const Grammar &G){
    for(mmap::const_iterator it = G._grammar.begin(); it != G._grammar.end(); ++it){
        out << phraseLookUp[it->first] << "-> {";
        for(GPlist::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt){
            out  << phraseLookUp[*jt];
            if(++jt != it->second.end())
                out << " + ";
            --jt;
        }
        out << "}\n";
    }
    return out;
}

/**
 * @brief Grammar::getDefinition Returns the definitions of the specified phrase
 * @param define the phrase whose definitions are desired
 * @return a vector of grammarphrases
 * NOTE: If the vector is empty, then there were no definitions found
 */
std::vector<GPlist> Grammar::getDefinition(const GrammarPhrase &define){
    std::pair<mmap::iterator,mmap::iterator> it = _grammar.equal_range(define);
    std::vector<GPlist> g;
    for(mmap::iterator i = it.first; i != it.second; ++i){
        g.insert(g.end(),i->second);
    }
    if(define == SENTENCE && g.size() > 1){
        g.erase(g.begin());
    }
    return g;
}

/**
 * @brief Grammar::getDefiner Returns the phrase whose definition is the same as the one specified
 * @param rule the definition
 * @return the phrase that corresponds to the rule
 * NOTE: If the phrase is G_INVALID, then the definer was not found
 */
GrammarPhrase Grammar::getDefiner(const GPlist &rule){
    for(mmap::iterator it = _grammar.begin(); it != _grammar.end(); ++it)
        if(it->second == rule) return it->first;
    return G_INVALID;
}
