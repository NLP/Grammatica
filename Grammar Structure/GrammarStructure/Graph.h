#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <cassert>
#include <set>
static const std::size_t MAX = 30;
template <typename Item>
class Graph{
protected:
    bool _edges[MAX][MAX];
    Item _labels[MAX];
    std::size_t _vertices;
public:
    Graph(){
        _vertices = 0;
    }

    void addVertex(const Item& label){
        assert(size() < MAX);
        std::size_t newVertex = _vertices++;
        for(std::size_t i = 0; i < _vertices; ++i){
            _edges[i][newVertex] = false;
            _edges[newVertex][i] = false;
        }
        _labels[newVertex] = label;

    }

    void addEdge(std::size_t source, std::size_t target){
        assert(source < size());
        assert(target < size());
        _edges[source][target] = true;
    }

    void removeEdge(std::size_t source, std::size_t target){
        assert(source < size());
        assert(target < size());
        _edges[source][target] = false;
    }

    Item& operator [](std::size_t vertex){
        return _labels[vertex];
    }

    std::size_t size() const{
        return _vertices;
    }
    bool isEdge(std::size_t source, std::size_t target) const{
        assert(source < size());
        assert(target < size());
        return _edges[source][target];
    }
    std::set<std::size_t> neighbors(std::size_t vertex) const{
        assert(vertex < size());
        std::set<std::size_t> neighborhood;
        for(std::size_t i = 0; i < size(); ++i){
            if(_edges[vertex][i])
                neighborhood.insert(i);
        }
        return neighborhood;

    }
    Item operator [](std::size_t vertex) const{
        return _labels[vertex];
    }
    friend std::ostream& operator <<(std::ostream& out, const Graph<Item>& G){
        for(std::size_t i = 0; i < G._vertices; ++i)
            out << i << ": {" << G._labels[i] << "} | ";
        out << std::endl << "   ";
        for(std::size_t i = 0; i < G._vertices; ++i)
            out << G._labels[i] << " ";
        out << std::endl;
        for(std::size_t i = 0; i < G._vertices; ++i){
            out << G._labels[i] << ": ";
            for(std::size_t j = 0; j < G._vertices; ++j)
                out << G._edges[i][j] << "|";
            out << std::endl;
        }
        return out;
    }
    std::size_t index(const Item& item) const{
        for(std::size_t i = 0; i < _vertices; ++i){
            if(_labels[i] == item)
                return i;
        }
        return -1;
    }
};

#endif // GRAPH_H
