#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include "syntaxtree.h"
using namespace NLP;
typedef std::vector<SyntaxTree> STvector;
typedef std::vector<Word> Wvector;
typedef std::set<WordType> WTset;
class Parser{
private:
    STvector _valid;
    Grammar _G;
    Wvector _words;

    bool recDescent(SyntaxTree& S, std::size_t c);
    bool findFirstIncomplete(SyntaxTree &S);

    Word& getNextWord(std::size_t i);
    GPlist getNextDef(GrammarPhrase g, GPlist def);
    WordType getNextType(const Word& W, WordType T);

    void attachWords(SyntaxTree& S);
    void assignHeadWords(SyntaxTree& S);
    void assignObjects(SyntaxTree& S);
public:
    Parser();
    Parser(const Grammar& G, const Wvector& words);

    void setGrammar(const Grammar& G);
    void setSentence(const Wvector& W);
    Grammar getGrammar();
    Wvector getSentence();
    STvector getTrees();

    STvector parse();

};

#endif // PARSER_H
