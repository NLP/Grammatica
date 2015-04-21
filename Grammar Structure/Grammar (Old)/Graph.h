#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <set>
#include <cassert>
using namespace std;

template <typename Item>
class Graph{
protected:
    bool** _edges; //stores the edges between vertices
    Item* _labels; //Stores the labels of each vertex
    std::size_t _allocated; //The amount of space allocated
    std::size_t _vertices; //The number of vertices currently (must not be greater than allocated)
protected:
    //Reallocates the adjaceny matrix and labels to the new size (ie, recreates it to the new size0
    void reallocate(std::size_t nSize){
        bool** edgeTemp = _edges; //Temporary holders for the matrix and label
        Item* labelTemp = _labels;
        allocate2D(_edges,nSize); //allocate
        allocate(_labels,nSize);
        initialize2D(_edges,nSize);
        if(size() != 0){
            for(std::size_t i = 0; i < size(); i++) //Copy the previous values into the previous spots
                copyPtr(edgeTemp[i],_edges[i],size());
            copyPtr(labelTemp,_labels,size());
            for(std::size_t i = 0; i < size(); i++) //delete the old matrix
                delete edgeTemp[i];
            delete edgeTemp;
            delete labelTemp;
        }
        _allocated = nSize;
    }
    //initialize the array
    void initialize(bool* array, std::size_t size){
        for(std::size_t i = 0; i < size; ++i)
            array[i] = false;
    }
    //Initialize a 2D array
    void initialize2D(bool** array, std::size_t size){
        for(std::size_t i = 0; i < size; ++i)
            initialize(array[i],size);
    }
    //allocate the array
    template <typename Type>
    void allocate(Type*& array, std::size_t size){
        array = new Type[size];
    }
    //allocate a 2D array
    template <typename Type>
    void allocate2D(Type**& array, std::size_t size){
        array = new Type*[size];
        for(std::size_t i = 0; i < size; ++i)
            allocate(array[i],size);
    }
    //copy the pointer from source to destination
    template <typename Type>
    void copyPtr(Type* source, Type* dest, std::size_t size){
        for(std::size_t i = 0; i < size; ++i)
            dest[i] = source[i];
    }

public:
    //Constructors
    Graph(std::size_t size = 0){
        _vertices = 0;
        _allocated = size;
        allocate2D(_edges,_allocated);
        initialize2D(_edges,_allocated);
        allocate(_labels,_allocated);
    }
    //Add a vertex
    void addVertex(const Item& label){
        if(_allocated <= size()) resize(_allocated*2); //If there is no more room, resize with double the space
        std::size_t newVertex = _vertices++;
//        cout << "allocated: " << _allocated << endl;
        for(std::size_t other = 0; other < _vertices; ++other){
//            cout << "other: " << other << endl;
//            cout << "newVertex: " << newVertex << endl;
            _edges[other][newVertex] = false;
            _edges[newVertex][other] = false;
        }
        _labels[newVertex] = label;
    }
    //Add an edge
    void addEdge(std::size_t source, std::size_t target){
        assert(source < size());
        assert(target < size());
        _edges[source][target] = true;
    }
    //Remove an edge
    void removeEdge(std::size_t source, std::size_t target){
        assert(source < size());
        assert(target < size());
        _edges[source][target] = false;
    }
    //Resize the matrix
    void resize(std::size_t size){
        reallocate(size);
    }
    //Brackets
    Item& operator [](std::size_t vertex){
        assert(vertex < size());
        return _labels[vertex];
    }
    //Returns size
    std::size_t size() const{
        return _vertices;
    }
    //Checks if there is an edge
    bool isEdge(std::size_t source, std::size_t target) const{
        assert(source < size());
        assert(target < size());
        return _edges[source][target];
    }
    //Gets a set of all of the neighbors of the vertex
    std::set<std::size_t> neighbors(std::size_t vertex) const{
        assert(vertex < size());
        std::set<std::size_t> adjacents;
        for(std::size_t i = 0; i < size(); ++i)
            if(_edges[vertex][i]) adjacents.insert(i);
        return adjacents;
    }
    //Const Bracket
    Item operator [](std::size_t vertex) const{
        assert(vertex < size());
        return _labels[vertex];
    }
    Item* find(const Item& label){
//        cout << "Label: " << label << endl;
        for(std::size_t i = 0; i < _vertices; ++i)
            if(_labels[i] == label){
//                cout << "_labels[i]: " << _labels[i] << endl;
//                cout << &_labels[i] << endl;
                return &_labels[i];
            }

        return nullptr;
    }

    //Output
    friend std::ostream& operator << (std::ostream& out, const Graph<Item> G){
//        out << "   ";
//        for(std::size_t i = 0; i < G.size(); ++i)
//            out << G._labels[i] << "|";
//        out  << std::endl;
//        for(std::size_t i = 0; i < G.size(); ++i){
//            out << G._labels[i] << ":|";
//            for(std::size_t j = 0; j < G.size(); ++j)
//                out << G._edges[i][j] << "|";
//            out << std::endl;
//        }
        for(std::size_t i = 0; i < G.size(); ++i)
            out << i << ":" << G._labels[i] << "|";
        out << std::endl << std::endl;
        out << "   ";
        for(std::size_t i = 0; i < G.size(); ++i)
            out << i << " ";
        out  << std::endl;
        for(std::size_t i = 0; i < G.size(); ++i){
            out << i << ":|";
            for(std::size_t j = 0; j < G.size(); ++j)
                out << G._edges[i][j] << "|";
            out << std::endl;
        }
        return out;
    }
    std::size_t getIndex(const Item& label){
//        cout << "Label in getIndex: " << label << endl;
        for(std::size_t i = 0; i < _vertices; ++i)
            if(_labels[i] == label) return i;
        return -1;
    }

};

#endif // GRAPH_H
