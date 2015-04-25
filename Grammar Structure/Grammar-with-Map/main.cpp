#include <iostream>
#include "cfgzero.h"
using namespace std;

int main()
{
    CFGZero z;
    cout << z << endl;
    std::vector<GPlist> g = z.getDefinition(NOUNPHRASE);
    std::vector<GPlist>::iterator it = g.begin();
    while(it != g.end()){
        GPlist::iterator git = it->begin();
        while(git != it->end()){
            cout << *git << endl;
            ++git;
        }
        ++it;
    }
    return 0;
}

