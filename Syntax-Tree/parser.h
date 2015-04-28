#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include "syntaxtree.h"
using namespace NLP;

/**
 * @brief STvector typedef for std::vector<SyntaxTree>
 */
typedef std::vector<SyntaxTree> STvector;

/**
 * @brief Wvector typedeft for std::vector<Word>
 */
typedef std::vector<Word> Wvector;

/**
 * @brief WTset std::set<WordType>
 */
typedef std::set<WordType> WTset;

/**
 * @brief The Parser class The Parser class. It takes a Grammar Structure and
 * a vector of Words to create a vector of all possible Syntax Trees that follow
 * the Grammar Structure and matches the vector of Words.
 */
class Parser{
private:

    /**
     * @brief _valid the vector of valid Syntax Trees
     */
    STvector _valid;

    /**
     * @brief _G the Grammar Structure
     */
    Grammar _G;

    /**
     * @brief _words the vector of Words
     */
    Wvector _words;

    bool recDescent(SyntaxTree& S, size_t &c);
    bool findFirstIncomplete(SyntaxTree &S);
    void removePartial(SyntaxTree& S);

    TNpair *removePartial(TNpair* root, TNpair* target);

    Word getNextWord(std::size_t i);
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
