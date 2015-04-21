#ifndef GRAMMAR_H
#define GRAMMAR_H
#include "LabeledGraph.h"
#include "VectorContainer.h"
#include <map>
enum GrammarPhrase{
    UNKNOWN     = 0,
    ALL         = 1,
    SENTENCE    = 2,
    NOUNPHRASE  = 3,
    VERBPHRASE  = 4,
    PREPPHRASE  = 5,
    NOMINAL     = 6,
    NOUN        = 7,
    VERB        = 8,
    PREP        = 9,
    DETERMINER  = 10
};
static const std::size_t gpSize = 10;
static const GrammarPhrase gpList[] ={
    UNKNOWN,
    ALL,
    SENTENCE,
    NOUNPHRASE,
    VERBPHRASE,
    PREPPHRASE,
    NOMINAL,
    NOUN,
    VERB,
    PREP,
    DETERMINER
};

//Requires c++11
static std::map<GrammarPhrase,std::string> phraseLookUp = {
    {    UNKNOWN,       "Unknown"       },
    {    ALL,           "All"           },
    {    SENTENCE,      "Sentence"      },
    {    NOUNPHRASE,    "Noun Phrase"   },
    {    VERBPHRASE,    "Verb Phrase"   },
    {    PREPPHRASE,    "Prep. Phrase"  },
    {    NOMINAL,       "Nominal"       },
    {    NOUN,          "Noun"          },
    {    VERB,          "Verb"          },
    {    PREP,          "Preposition"   },
    {    DETERMINER,    "Determiner"    }

};

//In the structure, each phrase is in a sense unique, in that if there exist
//multiple 'nominals' in the structure, no matter what leads to the nominal, each
//nominal can go to every possible path any other nominal can go
//So in this sense, the phrases are unique, thus we can just identify them
//with their names.
//If we wish to see if one phrase can lead to another, it does not matter if there
//are multiple versions of this phrase in the structure, if one of them can lead to the
//other phrase, they all can.
typedef VectorContainer<GrammarPhrase> GPvector;
class Grammar{
private:
    LabeledGraph<GPvector,GrammarPhrase> _grammar;
    void createSentence();
public:
    Grammar();
    void addPhrase(const GPvector& phrase, std::size_t parent, GrammarPhrase source = ALL, GrammarPhrase dest = ALL);
    void addRule(std::size_t from, std::size_t to, GrammarPhrase source = ALL, GrammarPhrase dest = ALL);
    void removeRule(std::size_t from, std::size_t to);

    GPvector& getVector(std::size_t index);
    std::size_t getIndex(const GPvector& phrase);
    GrammarPhrase getSource(std::size_t from, std::size_t to);
    GrammarPhrase getDest(std::size_t from, std::size_t to);
    friend std::ostream& operator <<(std::ostream& out, const Grammar& G);
    std::set<std::size_t> getNeighbors(std::size_t phrase);
    //Add Phrase

    //Add Rule
    //Remove Rule
    //Print
    //Access Vector at Indexes
    //Get Labels at Indexes
    //
};

#endif // GRAMMAR_H
