#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include "syntaxtree.h"
#include <queue>
using namespace NLP;
//Given a Grammar and a set of tokens, create syntax trees
//Use Recursive Descent Parser
class Parser{
private:
    std::vector<SyntaxTree> _valid;
    std::vector<Word> _words;
    TreeNode<GtSpair>* _current;
    Grammar _G;
    std::vector<SyntaxTree> loopedParse(TreeNode<GtSpair>* root);
    void recursiveDescent(TreeNode<GtSpair>* root); //Change
    bool backtrack(TreeNode<GtSpair>* root);
    void attachWords();
    void attachHeads();
    void attachSyntax();
public:
    Parser();
    Parser(const std::vector<Word>& words, const Grammar& G);
    std::vector<SyntaxTree> parse();
    void reset();
    void setWords(const std::vector<Word>& words);
    std::vector<Word> getWords();
    void setGrammar(const Grammar& G);
    Grammar getGrammar();
};

#endif // PARSER_H
