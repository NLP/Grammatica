#ifndef SYNTAXWORD_H
#define SYNTAXWORD_H
//#include "../../../CONFIG/config.h"
#include "../../Parser/Tagger/word.h"

using namespace NLP;
/**
 * @brief The SyntaxWord class Container for a Word and a Syntax Identifier
 */
class SyntaxWord{
private:
    /**
     * @brief _so the Syntax Indentifier
     */
    SyntaxObject _so;
    /**
     * @brief _word the Word
     */
    Word _word;
public:
    SyntaxWord();

    SyntaxWord(const SyntaxObject& so, const Word& word);
    bool isHeadWord(const GrammarPhrase& gp) const;
    void setWord(const Word& W);
    Word getWord();
    void setSyntax(SyntaxObject S);
    SyntaxObject getSyntax();
    friend std::ostream& operator <<(std::ostream& out, const SyntaxWord& S){
        out << S._word << ": " << syntaxLookUp[S._so];
        return out;
    }
};
#endif // SYNTAXWORD_H
