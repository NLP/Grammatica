#include "grammar.h"
using namespace std;
void Grammar::createSentence(){
    GPvector gp(SENTENCE);
    _grammar.addVertex(gp);
}

Grammar::Grammar(){
    createSentence();
}

void Grammar::addPhrase(const GPvector &phrase, std::size_t parent, GrammarPhrase source, GrammarPhrase dest){
//    cout << "Adding " << phrase << endl;
    _grammar.addVertex(phrase);
//    cout << "Index of phrase: " << getIndex(phrase) << endl;
//    cout << "index of parent: " << parent << endl;
//    cout << "Index of Sentence: " << getIndex(GPvector(SENTENCE)) << endl;
    _grammar.addEdge(parent,getIndex(phrase),source,dest);
//    cout << "Done adding " << phrase << endl;
}

void Grammar::addRule(std::size_t from, std::size_t to, GrammarPhrase source, GrammarPhrase dest){
    _grammar.addEdge(from,to,source,dest);
}

void Grammar::removeRule(std::size_t from, std::size_t to){
    _grammar.removeEdge(from,to);
}

GPvector &Grammar::getVector(std::size_t index){
    return _grammar[index];
}

std::size_t Grammar::getIndex(const GPvector &phrase){
    return _grammar.index(phrase);
}

GrammarPhrase Grammar::getSource(std::size_t from, std::size_t to){
    return _grammar.getLabelA(from,to);
}

GrammarPhrase Grammar::getDest(std::size_t from, std::size_t to){
    return _grammar.getLabelB(from,to);
}

std::set<std::size_t> Grammar::getNeighbors(std::size_t phrase){
    return _grammar.neighbors(phrase);
}

std::ostream& operator <<(std::ostream &out, const Grammar &G){
    for(std::size_t i = 0; i < G._grammar.size(); ++i){
        for(std::size_t j = 0; j < G._grammar.size(); ++j){
            if(G._grammar.isEdge(i,j)){
//                std::vector<GrammarPhrase>::iterator it = G._grammar[i]._vec.begin();
//                out << phraseLookUp[*G._grammar[i]._vec.begin()];
//                int i = 0;
//                while(it != G._grammar[i]._vec.end()){
//                    out << i++ << std::endl;
////                    out << phraseLookUp[*it] << "|";
//                    ++it;
//                }
                out << G._grammar[i] << ": (" << phraseLookUp[G._grammar.getLabelA(i,j)] << ")->("
                    << phraseLookUp[G._grammar.getLabelB(i,j)] << ")  " << G._grammar[j];;
//                it = G._grammar[j]._vec.begin()
//                while(it != G._grammar[j]._vec.end()){
//                    out << phraseLookUp[*it] << "|";
//                    ++it;
//                }
                out << std::endl;
            }
        }
    }
    return out;
}
