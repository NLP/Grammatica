#include "cfgzero.h"

/**
 * @brief CFGZero::createCFG adds the rules defined by cfgzInit
 */
void CFGZero::createCFG(){
    for(auto& i : cfgzInit)
        Grammar::addRule(i.first,i.second);
}

/**
 * @brief CFGZero::CFGZero Constructor. Calls createCFG()
 */
CFGZero::CFGZero(){
    createCFG();
}
