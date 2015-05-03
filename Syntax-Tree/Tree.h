#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <iomanip>

template <typename Item>
/**
 * @brief The TreeNode struct the node that will occupy trees
 */
struct TreeNode{
    /**
     * @brief TNvector typedef of std::vector<TreeNode*>
     */
    typedef std::vector<TreeNode*> TNvector;

    /**
     * @brief _data the item inside the node
     */
    Item _data;

    /**
     * @brief _child a vector of children whose parent is this node
     */
    TNvector _child;

    /**
     * @brief TreeNode Constructor
     * @param data item, by default it is the Default Constructor for the Item Type
     * @param children the children, by default it is any empty vector
     */
    TreeNode(const Item& data = Item(),
             const TNvector& children = TNvector()) {
        _data = data;
        _child = children;
    }

    /**
      * @brief ~TreeNode destructor for TreeNode. Destroys all of its children.
      */
    ~TreeNode()                                     {
        for(std::size_t i = 0; i < _child.size(); ++i){
            delete _child[i];
        }
    }

    /**
     * @brief data returns a reference to the item
     * @return item reference
     */
    Item& data()                                    {return _data;}

    /**
     * @brief children returns a reference to the children vector
     * @return vector reference
     */
    TNvector& children()                            {return _child;}

    /**
     * @brief setData changes the item
     * @param data the new item
     */
    void setData(const Item& data)                  {_data = data;}

    /**
     * @brief setChildren changes the children
     * @param children the new children
     * NOTE: Does not clean up any dynamic items it may hold.
     */
    void setChildren(const TNvector& children)      {_child = children;}

    /**
     * @brief addChild adds a child to the vector
     * @param data the new child item
     */
    void addChild(const Item& data)                 {_child.insert(_child.end(),new TreeNode<Item>(data));}

    /**
     * @brief data returns a non reference item
     * @return non reference item
     */
    Item data()                     const           {return _data;}

    /**
     * @brief children returns a non reference vector
     * @return non reference vector
     */
    TNvector children()             const           {return _child;}

    /**
     * @brief isLeaf checks if the node is a leaf, i.e. has no children
     * @return True for is a Leaf, False for is not a leaf
     */
    bool isLeaf()                   const           {return _child.empty();}

    /**
     * @brief operator << insertion
     * @param out output stream
     * @param T the TreeNode
     * @return the output stream
     */
    friend std::ostream& operator <<
    (std::ostream& out, const TreeNode<Item>& T)   {
        out << T.data() << ":{ ";
        for(std::size_t i = 0; i < T._child.size(); ++i){
            if(i == T._child.size() - 1)
                out << *T._child[i];
            else
                out << *T._child[i] << " , ";
        }
        out << " } ";
        return out;
    }
};

//Namespace exclusive for TreeNode Functions
namespace rt{
    template <typename Item>
    /**
     * @brief clear clears the root and all of its children
     * @param root the root of the tree
     */
    void clear(TreeNode<Item>*& root){
        if(!root) return;
        for(std::size_t i = 0; i < root->children().size(); ++i)
            clear(root->children()[i]);
        delete root;
        root = nullptr;
    }

    template <typename Item>
    /**
     * @brief copy copies the root and all of its children
     * @param root the root of the tree
     * @return a copy of the tree
     */
    TreeNode<Item>* copy(const TreeNode<Item>* root){
        typename TreeNode<Item>::TNvector tChild;
        for(std::size_t i = 0; i < root->children().size(); ++i)
            tChild.insert(tChild.end(),copy(root->children()[i]));
        return new TreeNode<Item>(root->data(),tChild);
    }

    template <typename Item>
    /**
     * @brief size calculates the size of the tree (how many nodes there are)
     * @param root the root of the tree
     * @return the size of the tree
     */
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
    /**
     * @brief leaves calculates the number of leaves of the tree
     * @param root the root of the tree
     * @return the number of leaves
     */
    std::size_t leaves(const TreeNode<Item>* root){
//        using namespace std;
//        cout << "in leaves" << endl;
        if(!root) return 0;
//        cout << "root is not nULL" << endl;
        if(root->isLeaf()) return 1;
//        cout << "root is not leaf" << endl;


        std::size_t num = 0;
        for(std::size_t i = 0; i < root->children().size(); ++i){
            num += leaves(root->children()[i]);
        }
        return num;
    }

    template <typename Item>
    /**
     * @brief search searches the tree for a specific item
     * @param root the root of the tree
     * @param item the target of the search
     * @return nullptr if no item was found, else the pointer to the node that holds the item
     */
    TreeNode<Item>* search(TreeNode<Item>* root, const Item& item){
        if(!root) return nullptr;
        if(root->data() == item) return root;
        TreeNode<Item>* result;
        for(std::size_t i = 0; i < root->children().size(); ++i){
            result = search(root->children()[i],item);
            if(result) return result;
        }
        return nullptr;
    }

    template <typename Item>
    /**
     * @brief parent finds the parent of the branch
     * @param root the root of the tree
     * @param branch the branch whose parent is the target
     * @return nullptr if no parent was found OR if branch is not in the tree, else
     * the parent
     */
    TreeNode<Item>* parent(TreeNode<Item>* root, const TreeNode<Item>* branch){
        if(!root || !branch) return nullptr;
        if(root == branch) return nullptr;
        TreeNode<Item>* result;
        for(std::size_t i = 0; i < root->children().size(); ++i){
            if(branch == root->children()[i])
                return root;
        }
        for(std::size_t i = 0; i < root->children().size(); ++i){
            result = parent(root->children()[i],branch);
            if(result) return result;
        }
        return nullptr;
    }

    template <typename Item>
    /**
     * @brief allLeaves gets a vector of all of the leaves of the tree
     * @param root the root of the tree
     * @return a vector of the leaves
     */
    std::vector<TreeNode<Item>*> allLeaves(TreeNode<Item>* root){
        std::vector<TreeNode<Item>*> s;
        if(!root) return s;
        if(root->isLeaf()){
            s.insert(s.begin(),root);
            return s;
        }
        typename TreeNode<Item>::TNvector::const_iterator it = root->children().begin();
        while(it != root->children().end()){
            std::vector<TreeNode<Item>*> t = allLeaves(*it);
            s.insert(s.end(),t.begin(),t.end());
            ++it;
        }
        return s;
    }
}


template <typename Item>
/**
 * @brief The Tree class a class to contain a TreeNode*
 */
class Tree{
protected:
    /**
     * @brief _root the root of the tree
     */
    TreeNode<Item>* _root;
    /**
     * @brief _current the treenode in which many operations are performed.
     * Can be changed via shift functions
     */
    TreeNode<Item>* _current;
public:
    /**
     * @brief Tree Default Constructor
     */
    Tree(){
        _root = nullptr;
        _current = _root;
    }

    /**
     * @brief Tree Constructor
     * @param root Sets the root to this root
     * NOTE: Does not copy the root
     */
    Tree(TreeNode<Item>* root){
        _root = root;
        _current = _root;
    }

    /**
     * @brief Tree Copy Constructor
     * @param T a Tree
     * NOTE: Copies the root of T
     */
    Tree(const Tree<Item>& T){
        _root = rt::copy(T._root);
        _current = _root;
    }

    /**
      * @brief ~Tree Destructor
      */
    ~Tree(){
        clear();
    }

    /**
     * @brief operator = assignment operator
     * @param T Tree
     * @return this
     */
    Tree<Item>& operator =(const Tree<Item>& T){
        clear();
        _root = rt::copy(T._root);
        _current = _root;
        return *this;
    }

    /**
     * @brief addHere Adds an item as a child to the current node
     * @param item the item to add
     */
    void addHere(const Item& item){
        if(!_root){
            _root = new TreeNode<Item>(item);
            _current = _root;
        }
        else _current->addChild(item);
    }

    /**
     * @brief addNode Adds an item as a child to the parent
     * @param parent the parent
     * @param item the item
     */
    void addNode(TreeNode<Item>* parent, const Item& item){
        if(!_root){
            _root = new TreeNode<Item>(item);
            _current = _root;
        }
        else{
            if(!inTree(parent)) return;
            parent->addChild(item);
        }
    }

    /**
     * @brief search searches for a specific item
     * @param item the target
     * @return nullptr if not found, or the pointer to the node
     */
    TreeNode<Item>* search(const Item& item){
        return rt::search(_root,item);
    }

    /**
     * @brief inTree Checks if the node is part of the tree
     * @param node the node
     * @return True if it is in the tree, False otherwise
     */
    bool inTree(TreeNode<Item>* node){
        if(node == _root) return true;
        else{
            if(rt::parent(_root,node))
                return true;
            else return false;
        }
    }

    /**
     * @brief empty Checks if the tree is empty
     * @return True if it is empty, False otherwise
     */
    bool empty() const{
        return (!_root);
    }

    /**
     * @brief clear Clears the tree
     */
    void clear(){
        if(!empty()) rt::clear(_root);
    }

    /**
     * @brief leafNum Counts the number of leaves in the tree
     * @return number of leaves
     */
    std::size_t leafNum(){
        return rt::leaves(_root);
    }

    /**
     * @brief getParent Gets the parent of the branch
     * @param branch the branch
     * @return nullptr if there is no parent OR the branch is no part of the tree,
     * The parent if found
     */
    TreeNode<Item>* getParent(TreeNode<Item>* branch){
        return rt::parent(_root,branch);
    }

    /**
     * @brief getCurrent Returns the current node pointer
     * @return current node pointer
     */
    TreeNode<Item>* getCurrent(){
        return _current;
    }

    /**
     * @brief set Set the item of the current node
     * @param item the item
     */
    void set(const Item& item){
        _current->setData(item);
    }

    /**
     * @brief shiftToRoot shift the current to the root
     */
    void shiftToRoot(){
        _current = _root;
    }

    /**
     * @brief shiftUp Shift the current to its parent
     */
    void shiftUp(){
        if(!hasParent()) return;
        _current = getParent(_current);
    }

    /**
     * @brief shiftDown Shift the current to one of its children
     * @param child the child to shift to
     * NOTE: Does not change current if the child does not exist
     */
    void shiftDown(std::size_t child){
        if(child >= _current->children().size()) return;
        _current = _current->children()[child];
    }

    /**
     * @brief shiftTo Shift the current to the specified target
     * @param target the target
     * NOTE: Does not change current if the target is not part of the tree
     */
    void shiftTo(TreeNode<Item>* target){
        if(inTree(target))
            _current = target;
    }

    /**
     * @brief hasParent Checks if current has a parent
     * @return True if it does, False otherwise
     */
    bool hasParent(){
        return (_current != _root);
    }

    /**
     * @brief hasChild Checks if current has children
     * @return True if it does, False otherwise
     */
    bool hasChild(){
        return (!_current->isLeaf());
    }

    /**
     * @brief childNum Finds the number of children of current
     * @return the number of children
     */
    std::size_t childNum(){
        return (_current->children().size());
    }

    /**
     * @brief get Returns the item of current
     * @return the item reference
     */
    Item& get(){
        return (_current->data());
    }

    /**
     * @brief size Returns the size of the tree
     * @return the size
     */
    std::size_t size() const{
        return rt::size(_root);
    }

    /**
     * @brief getLeaves Returns a vector of the leaves of the tree
     * @return the vector of leaves
     */
    std::vector<TreeNode<Item>*> getLeaves(){
        return rt::allLeaves(_root);
    }

    /**
     * @brief operator << insertion
     * @param out output stream
     * @param T Tree
     * @return output stream
     */
    friend std::ostream& operator <<(std::ostream& out, const Tree<Item> T){
        out << *T._root;
        return out;
    }
};


#endif // TREE_H
