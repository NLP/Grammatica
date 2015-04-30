#include "cfgq.h"

void CFGQ::createCFG(){
    for(auto& i : cfgqInit)
        Grammar::addRule(i.first,i.second);
}

CFGQ::CFGQ()
{
    createCFG();
}
