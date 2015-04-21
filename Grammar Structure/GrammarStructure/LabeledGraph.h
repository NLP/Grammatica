#ifndef LABELEDGRAPH_H
#define LABELEDGRAPH_H

#include "Graph.h"
template <typename Item, typename Label>
class LabeledGraph:public Graph<Item>{
private:
    Label _eLabelA[MAX][MAX];
    Label _eLabelB[MAX][MAX];
public:
    LabeledGraph():Graph<Item>(){

    }
    void addEdge(std::size_t source, std::size_t target, Label a, Label b){
        Graph<Item>::addEdge(source,target);
        _eLabelA[source][target] = a;
        _eLabelB[source][target] = b;
    }
    friend std::ostream& operator <<(std::ostream& out, const LabeledGraph<Item,Label>& G){
        for(std::size_t i = 0; i < G.Graph<Item>::_vertices; ++i)
            out << i << ": {" << G.Graph<Item>::_labels[i] << "} | ";
        out << std::endl << "    ";
        for(std::size_t i = 0; i < G.Graph<Item>::_vertices; ++i)
            out << G.Graph<Item>::_labels[i] << "   ";
        out << std::endl;
        for(std::size_t i = 0; i < G.Graph<Item>::_vertices; ++i){
            out << G.Graph<Item>::_labels[i] << ": ";
            for(std::size_t j = 0; j < G.Graph<Item>::_vertices; ++j){
                if(G.Graph<Item>::_edges[i][j])
                    out << G._eLabelA[i][j] << ":" << G._eLabelB[i][j] << "|";
            }

            out << std::endl;
        }
        return out;
    }
    Label getLabelA(std::size_t from, std::size_t to) const{
        return _eLabelA[from][to];
    }
    Label getLabelB(std::size_t from, std::size_t to) const{
        return _eLabelB[from][to];
    }
};

#endif // LABELEDGRAPH_H
