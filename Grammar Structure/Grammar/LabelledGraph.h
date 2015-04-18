#ifndef LABELLEDGRAPH_H
#define LABELLEDGRAPH_H
#include "Graph.h"
using namespace std;
template <typename Item, typename Label>
class LabelledGraph : public Graph<Item>{
private:
    Label** _edgeLabelsA;
    Label** _edgeLabelsB;
public:
    //Constructors
    LabelledGraph(std::size_t size = 0):Graph<Item>(size){
        Graph<Item>::allocate2D(_edgeLabelsA,size);
        Graph<Item>::allocate2D(_edgeLabelsB,size);
    }
    //Add an edge with a label
    void addEdge(std::size_t source, std::size_t target, const Label& labelA, const Label& labelB){
//        cout << "In ADDEDGE" << endl;
        Graph<Item>::addEdge(source,target);
//        cout << "ALLOCATED: " << Graph<Item>::_allocated << endl;
//        cout << "@ source: " << Graph<Item>::_labels[source] << endl;
//        cout << "@ target: " << Graph<Item>::_labels[target] << endl;
//        cout << "LabelA: " << labelA << endl;
//        cout << "LabelB: " << labelB << endl;
        _edgeLabelsA[source][target] = labelA;
//        cout << "A: " << _edgeLabelsA[source][target] << endl;
        _edgeLabelsB[source][target] = labelB;
//        cout << "B: " << _edgeLabelsA[source][target] << endl;
//        cout << *this << endl;
    }
    void resize(std::size_t nSize){
        Label** labelTempA = _edgeLabelsA; //Temporary holders for the matrix and label
        Label** labelTempB = _edgeLabelsB;
        Graph<Item>::allocate2D(_edgeLabelsA,nSize); //allocate
        Graph<Item>::allocate2D(_edgeLabelsB,nSize); //allocate
//        Graph<Item>::initialize2D(_edgeLabelsA,nSize);
//        Graph<Item>::initialize2D(_edgeLabelsB,nSize);
        if(Graph<Item>::size() != 0){
            for(std::size_t i = 0; i < Graph<Item>::size(); i++) //Copy the previous values into the previous spots
                Graph<Item>::copyPtr(labelTempA[i],_edgeLabelsA[i],Graph<Item>::size());
            for(std::size_t i = 0; i < Graph<Item>::size(); i++) //Copy the previous values into the previous spots
                Graph<Item>::copyPtr(labelTempB[i],_edgeLabelsB[i],Graph<Item>::size());
            for(std::size_t i = 0; i < Graph<Item>::size(); i++) //delete the old matrix
                delete labelTempA[i];
            for(std::size_t i = 0; i < Graph<Item>::size(); i++) //delete the old matrix
                delete labelTempB[i];
            delete labelTempA;
            delete labelTempB;
        }
        Graph<Item>::resize(nSize);
    }

    //Output
    friend std::ostream& operator <<(std::ostream& out, const LabelledGraph<Item,Label>& G){
        for(std::size_t i = 0; i < G.size(); ++i)
            out << i << ":" << G._labels[i] << "|";
        out << std::endl;
        out << "    ";
        for(std::size_t i = 0; i < G.size(); ++i)
            out << i << "   ";
        out  << std::endl;
        for(std::size_t i = 0; i < G.size(); ++i){
            out << i << ":|";
            for(std::size_t j = 0; j < G.size(); ++j){
                if(G._edges[i][j])
                    out << G._edgeLabelsA[i][j] << ":" << G._edgeLabelsB[i][j] << "|";
                else
                    out << " : |";
            }
            out << std::endl;
        }
        return out;
    }
    void print(){
        for(std::size_t i = 0; i < Graph<Item>::_vertices; ++i){
            for(std::size_t j = 0; j < Graph<Item>::_vertices; ++j){
                if(Graph<Item>::_edges[i][j]){
                    cout << Graph<Item>::_labels[i] << "(" << _edgeLabelsA[i][j] << ")->("
                         << _edgeLabelsB[i][j] << ")" << Graph<Item>::_labels[j] << endl;
                }

            }
        }
    }
};
#endif // LABELLEDGRAPH_H
