#include <iostream>
#include "cfgzero.h"
using namespace std;

int main()
{
    Grammar G;
    GPvector gp(NOUNPHRASE);
    G.addPhrase(gp,0);
    cout << G << endl;
    CFGZero Z;
    cout << Z << endl;
    return 0;
}

