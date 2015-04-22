#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <iomanip>

template <typename Item>
struct TreeNode{
    typedef std::vector<TreeNode*> TNvector;
    Item _data;
    TNvector _child;

    TreeNode(const Item& data = Item(),
             const TNvector& children = TNvector()) {
        _data = data;
        _child = children;
    }
    ~TreeNode()                                     {
        typename TNvector::iterator it = _child.begin();
        typename TNvector::iterator temp = it;
        while(it != _child.end()){
            ++it;
            delete *it;
            temp = it;
        }
    }

    Item& data()                                    {return _data;}
    TNvector& children()                            {return _child;}

    void setData(const Item& data)                  {_data = data;}
    void setChildren(const TNvector& children)      {_child = children;}
    void addChild(const Item& data)                 {_child.insert(_child.end(),new TreeNode<Item>(data));}

    const Item& data()              const           {return _data;}
    const TNvector& children()      const           {return _child;}
    bool isLeaf()                   const           {return _child.empty();}

    template <typename Other>
    friend std::ostream& operator <<
    (std::ostream& out, const TreeNode<Other>& T)   {
        out << T.data() << ":(";
        typename TNvector::const_iterator it = T._child.begin();
        while(it != T._child.end()){
            out << **it << ", ";
            ++it;
        }
        out << ")";
        return out;
    }

};

namespace rt{
    template <typename Item>
    void clear(TreeNode<Item>*& root){
        if(root != NULL){
            typename TreeNode<Item>::TNvector::iterator it = root->children().begin();
            while(it != root->children.end()){
                clear(*it);
                ++it;
            }
            delete root; //Clear the root
            root = NULL;
        }
    }

    template <typename Item>
    TreeNode<Item>* copy(const TreeNode<Item>* root){
        typename TreeNode<Item>::TNvector tChild;
        if(root == NULL) return NULL; //If it goes past a leaf
        else{
            typename TreeNode<Item>::TNvector::iterator it = root->children().begin();
            while(it != root->children().end()){
                tChild.insert(tChild.begin(),*it);
                ++it;
            }
            return new TreeNode<Item>(root->data(),tChild);
        }
    }

    template <typename Item>
    std::size_t size(const TreeNode<Item>* root){
        if(root == NULL) return 0;
        std::size_t sum = 0;
        typename TreeNode<Item>::TNvector::const_iterator it = root->children().begin();
        while(it != root->children().end()){
            sum += size(*it);
            ++it;
        }
        return 1 + sum;
    }

    template <typename Item>
    std::size_t leaves(const TreeNode<Item>* root){
        if(!root) return 0;
        if(root->isLeaf()) return 1;
        typename TreeNode<Item>::TNvector::const_iterator it = root->children().begin();
        std::size_t num = 0;
        while(it != root->children().end()){
            num += leaves(*it);
            ++it;
        }
        return num;
    }

    template <typename Item>
    TreeNode<Item>* search(const TreeNode<Item>* root, const Item& item){
        if(!root) return nullptr;
        if(root->data() == item) return root;
        if(root->isLeaf()) return nullptr;
        typename TreeNode<Item>::TNvector::const_iterator it = root->children().begin();
        TreeNode<Item>* result;
        while(it != root->children().end()){
            result = search(*it,item);
            if(result) return result;
        }
        return nullptr;
    }

    template <typename Item> //Cannot handle root being the branch and vice-versa
    TreeNode<Item>* parent(const TreeNode<Item>* root, const TreeNode<Item>* branch){
        if(!root || !branch) return nullptr;
        if(root->isLeaf()) return nullptr;
        if(root == branch) return root;
        typename TreeNode<Item>::TNvector::const_iterator it = root->children().begin();
        TreeNode<Item>* result;
        while(it != root->children().end()){
            result = search(*it);
            if(result) return root;
        }
        return nullptr;
    }
}


template <typename Item>
class Tree{
private:
    TreeNode<Item>* _root;
    TreeNode<Item>* _current;
public:
    Tree(){
        _root = nullptr;
        _current = _root;
    }

    Tree(const Tree<Item>& T){
        _root = rt::copy(T._root);
        _current = _root;
    }

    ~Tree(){
        clear();
    }

    Tree<Item>& operator =(const Tree<Item>& T){
        clear();
        _root = rt::copy(T._root);
        _current = _root;
        return *this;
    }

    void addNode(TreeNode<Item>* parent, const Item& item){
        if(!inTree(parent)) return;
        parent->addChild(item);
    }

    TreeNode<Item>* search(const Item& item){
        return rt::search(_root,item);
    }

    bool inTree(TreeNode<Item>* node){
        if(node == _root) return true;
        else{
            if(parent(_root,node))
                return true;
            else return false;
        }
    }

    bool empty() const{
        return (!_root);
    }

    void clear(){
        if(!empty()) rt::clear(_root);
    }

    std::size_t leafNum(){
        return rt::leaves(_root);
    }
    TreeNode<Item>* getParent(TreeNode<Item>* branch){
        return rt::parent(_root,branch);
    }

    void removeNode(const Item& item){
        //remove node how would you find a successor from its children to take its place
    }

    void set(const Item& item){
        _current->setData(item);
    }

    void shiftToRoot(){
        _current = _root;
    }

    void shiftUp(){
        if(!hasParent()) return;
        _current = getParent(_current);
    }

    void shiftLeft(){
        TreeNode<Item>* parent = getParent(_current);
        typename TreeNode<Item>::TNvector::iterator it = parent->children().begin();
        if(_current == *it) return;
        while(it != parent->children().end()){
            if(*it == _current){
                --it;
                _current = *it;
                break;
            }
            ++it;
        }
    }

    void shiftRight(){
        TreeNode<Item>* parent = getParent(_current);
        typename TreeNode<Item>::TNvector::iterator it = parent->children().begin();
        if(_current == *(--(parent->children().end()))) return;
        while(it != parent->children().end()){
            if(*it == _current){
                ++it;
                _current = *it;
                break;
            }
            ++it;
        }
    }

    void shiftDown(std::size_t child){
        typename TreeNode<Item>::TNvector::iterator it = _current->children().begin();
        if(child >= _current->children().size()) return;
        for(std::size_t i = 0; i <= child; ++i){
            ++it;
        }
        _current = *it;
    }

    bool hasParent(){
        return (_current != _root);
    }

    bool hasChild(){
        return (!_current->isLeaf());
    }

    std::size_t childNum(){
        return (_current->children().size());
    }

    Item& get(){
        return (_current->data());
    }

    std::size_t size() const{
        return rt::size(_root);
    }
    friend std::ostream& operator <<(std::ostream& out, const Tree<Item> T){
        out << T._root;
        return out;
    }

};


#endif // TREE_H
