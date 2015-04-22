#include <iostream>
#include "grammar.h"
#include "cfgzero.h"
using namespace std;

int main()
{
    Grammar G;
    cout << "Testing addrules" << endl;
    G.addRule(SENTENCE,{NOUNPHRASE,VERBPHRASE});
    G.addRule(NOUNPHRASE,{DETERMINER,NOUN});
    cout << G << endl;
    cout << "Testing getdefinition" << endl;
    GPlist g = G.getDefinition(SENTENCE);
    for(GPlist::iterator it = g.begin(); it != g.end(); ++it){
        cout << *it << ", ";
    }
    cout << endl;
    cout << "Testing getdefiner" << endl;
    cout << G.getDefiner({NOUNPHRASE,VERBPHRASE}) << endl;
    cout << "Testing removerules" << endl;
    G.removeRule(NOUNPHRASE,{DETERMINER,NOUN});
    cout << G << endl;
    return 0;
}

