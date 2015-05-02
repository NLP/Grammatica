#include "cfgq.h"
/**
 * @brief CFGQ::createCFG Creates the Grammar
 */
void CFGQ::createCFG(){
    for(auto& i : cfgqInit)
        Grammar::addRule(i.first,i.second);
}

/**
 * @brief CFGQ::CFGQ Constructor
 */
CFGQ::CFGQ()
{
    createCFG();
}
