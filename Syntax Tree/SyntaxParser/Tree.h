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
            delete temp;
            temp = it;
        }
    }

    Item& data()                                    {return _data;}
    TNvector& children()                            {return _child;}

    void setData(const Item& data)                  {_data = data;}
    void setChildren(const TNvector& children)      {_child = children;}

    const Item& data()              const           {return _data;}
    const TNvector& children()      const           {return _child;}
    bool isLeaf()                   const           {return _child.empty();}

    template <typename Other>
    friend std::ostream& operator <<
    (std::ostream& out, const TreeNode<Other>& T)   {
        out << T.data() << ":(";
        typename TNvector::iterator it = T._child.begin();
        while(it != T._child.end()){
            out << *it << ", ";
        }
        out << ")";
        return out;
    }

};
template <typename Process, typename Node>
void inOrder(Process p, Node* ptr){
    if(ptr != NULL){
        inOrder(p,ptr->left()); //Go to the left branch
        p(ptr->data()); //Perform process on the data of the node
        inOrder(p,ptr->right()); //Go to the right branch
    }
}

template <typename Process, typename Node>
void preOrder(Process p, Node* ptr){
    if(ptr != NULL){
        p(ptr->data()); //Perform process on the data of the node
        preOrder(p,ptr->left()); //Go to the left branch
        preOrder(p,ptr->right()); //Go to the right branch
    }
}

template <typename Process, typename Node>
void postOrder(Process p, Node* ptr){
    if(ptr != NULL){
        postOrder(p,ptr->left()); //Go to the left branch
        postOrder(p,ptr->right()); //Go to the right branch
        p(ptr->data()); //Perform process on the data of the node
    }
}

template <typename Item>
class Tree{
private:
public:
    Tree();
    Tree(const Tree<Item>& T);
    ~Tree();
    Tree<Item>& operator =(const Tree<Item>& T);

    void addNode(TreeNode* parent, const Item& item);
    TreeNode* search(const Item& item);
    bool empty();
    void clear();
    std::size_t leafNum();
    void removeNode(const Item& item);
    void set(const Item& item);
    void shiftToRoot();
    void shiftUp();
    void shiftLeft();
    void shiftRight();
    void shiftDown(std::size_t child);
    bool hasParent();
    bool hasChild();
    std::size_t childNum();
    Item& get();
    std::size_t size();
    friend std::ostream& operator <<(std::ostream& out, const Tree<Item> T);

};



template <typename Item, typename Size>
void print(TreeNode<Item>* root, Size depth){
    if(root != NULL){
        print(root->right(),depth + 1);
        for(int i = 0; i < depth; i++) std::cout << " ";
        std::cout << root->data() << std::endl;
        print(root->left(),depth + 1);
    }
}

template <typename Item>
void clear(TreeNode<Item>*& root){
    TreeNode<Item>* branch;
    if(root != NULL){
        branch = root->left(); //Clear all of the left branches
        clear(branch);
        branch = root->right(); //Clear all of the right branches
        clear(branch);
        delete root; //Clear the root
        root = NULL;
    }
}

template <typename Item>
TreeNode<Item>* copy(const TreeNode<Item>* root){
    TreeNode<Item>* tLeft;
    TreeNode<Item>* tRight;
    if(root == NULL) return NULL; //If it goes past a leaf
    else{
        tLeft = copy(root->left()); //Copy all of the left
        tRight = copy(root->right()); //Copy all of the right
        return new TreeNode<Item>(root->data(),tLeft,tRight); //Create a node with the left and right
    }
}

template <typename Item>
std::size_t size(const TreeNode<Item>* root){
    if(root == NULL) return 0;
    else return 1 + size(root->left()) + size(root->right());
}

#endif // BINARYTREE_H

#endif // TREE_H
