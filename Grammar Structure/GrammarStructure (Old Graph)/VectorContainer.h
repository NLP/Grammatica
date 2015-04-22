#ifndef VECTORCONTAINER_H
#define VECTORCONTAINER_H
#include <vector>
#include <iostream>
template <typename Item>
struct VectorContainer{
    std::vector<Item> _vec;
    VectorContainer(){

    }

    VectorContainer(const Item& init){
        addBegin(init);
    }
    void addBegin(const Item& item){
        _vec.insert(_vec.begin(),item);
    }
    void addEnd(const Item& item){
        _vec.insert(_vec.end(),item);
    }

    friend std::ostream& operator <<(std::ostream& out,  VectorContainer<Item> V){
        typename std::vector<Item>::iterator it = V._vec.begin();
        while(it != V._vec.end()){
            out << *it << "|";
            ++it;
        }
        return out;
    }
    friend bool operator ==(const VectorContainer<Item>& L, const VectorContainer<Item>& R){
        return L._vec == R._vec;
    }
};
#endif // VECTORCONTAINER_H
