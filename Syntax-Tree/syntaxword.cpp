#include "syntaxword.h"

/**
 * @brief SyntaxWord::SyntaxWord Default Constructor
 */
SyntaxWord::SyntaxWord(){
    _so = S_INVALID;
}

/**
 * @brief SyntaxWord::SyntaxWord Constructor
 * @param so Syntax Indentifier
 * @param word the Word
 */
SyntaxWord::SyntaxWord(const SyntaxObject &so, const Word &word){
    _so = so;
    _word = word;
}

/**
 * @brief SyntaxWord::isHeadWord Checks if the word is a head word of the given grammar phrase
 * @param gp grammar phrase
 * @return True if it is, False otherwise
 * NOTE: Possibly not used anymore
 */
bool SyntaxWord::isHeadWord(const GrammarPhrase &gp) const{
    switch(gp){
    case PREPPHRASE:
    case NOUNPHRASE:{
        //if W is a noun
        return true;
        break;
    }
    case SENTENCE:
    case VERBPHRASE:{
        //if W is a verb
        return true;
        break;
    }
    default:{
        break;
    }
    }
    return false;
}

/**
 * @brief SyntaxWord::setWord Sets the word
 * @param W the word
 */
void SyntaxWord::setWord(const Word& W){
    _word = W;
}

/**
 * @brief SyntaxWord::getWord Returns the word
 * @return the word
 */
Word SyntaxWord::getWord(){
    return _word;
}

/**
 * @brief SyntaxWord::setSyntax Sets the Syntax
 * @param S the Syntax
 */
void SyntaxWord::setSyntax(SyntaxObject S){
    _so = S;
}

/**
 * @brief SyntaxWord::getSyntax Returns the Syntax
 * @return the Syntax
 */
SyntaxObject SyntaxWord::getSyntax(){
    return _so;
}

/**
 * @brief SyntaxWord::operator =
 * @param other
 * @return self
 */
SyntaxWord &SyntaxWord::operator =(const SyntaxWord &other) {
    _so = other.getSyntax ();
    _word = other.getWord ();
}
