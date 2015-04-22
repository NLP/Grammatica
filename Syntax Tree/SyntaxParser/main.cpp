#include <iostream>
#include "parser.h"
#include "syntaxtree.h"
using namespace std;
int main()
{
    TreeNode<int>* r = new TreeNode<int>;
    r->setData(1);
    TreeNode<int>::TNvector V;
    for(int i = 0; i < 10; i++){
        V.insert(V.begin(),new TreeNode<int>(i));
    }
    r->setChildren(V);
    r->children()[0]->addChild(12);
    cout << *r << endl;
    cout << rt::leaves(r) << endl;
    cout << rt::size(r) << endl;
    return 0;
}

