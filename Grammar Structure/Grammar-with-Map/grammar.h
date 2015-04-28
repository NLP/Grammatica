#ifndef GRAMMAR_H
#define GRAMMAR_H
#include <iostream>
#include <map>
#include <vector>
#include "../../CONFIG/config.h"

using namespace NLP;
//In the structure, each phrase is in a sense unique, in that if there exist
//multiple 'nominals' in the structure, no matter what leads to the nominal, each
//nominal can go to every possible path any other nominal can go
//So in this sense, the phrases are unique, thus we can just identify them
//with their names.
//If we wish to see if one phrase can lead to another, it does not matter if there
//are multiple versions of this phrase in the structure, if one of them can lead to the
//other phrase, they all can.


/**
 * @brief The Grammar class A generic Grammar class that contains a multimap. It maps a Grammar Phrase to
 * a vector of Grammar Phrases. This denotes the definition of the Grammar Phrase to other Grammar Phrases.
 * There may be more than one definition for a Grammar Phrase
 */
class Grammar{
private:
    /**
     * @brief _grammar the multimap that will hold the definitions between grammar phrases.
     */
    mmap _grammar;
    void createInitialRule();
public:
    Grammar();
    void addRule(const GrammarPhrase& define, const GPlist& rule);
    void removeRule(const GrammarPhrase& define, const GPlist& rule);
    friend std::ostream& operator <<(std::ostream& out, const Grammar& G);
    std::vector<GPlist> getDefinition(const GrammarPhrase& define);
    GrammarPhrase getDefiner(const GPlist& rule);

};
#endif // GRAMMAR_H
