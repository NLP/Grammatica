#include <iostream>
#include "grammar.h"
#include "ContexFreeGrammarZero.h"
using namespace std;
using namespace nlp;

int main()
{
    ContextFreeGrammarZero Z;
    cout << Z << endl;
    Z.printDef();
    return 0;
}

