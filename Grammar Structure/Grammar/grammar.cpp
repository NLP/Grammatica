#include "grammar.h"
using namespace nlp;
using namespace std;
Grammar::Grammar(){
    _gStruct.resize(20);
    gnl init;
    init.insertBegin(SENTENCE);
    _gStruct.addVertex(init);

}

void Grammar::add(const gnl &phrase, const gnl &parent, GrammarPhrase from, GrammarPhrase to){
//    cout << "IN ADD" << endl;
//    cout << "Phrase: " << phrase << endl;
//    cout << "Parent: " << parent << endl;
//    cout << "FROM: " << from << phraseLookUp[from] << endl;
//    cout << "TO: " << to << phraseLookUp[to] << endl;
    gnl* p = search(parent);
    if(!p) return; //no parent
//    cout << "We found a parent: " << *p << endl;
    _gStruct.addVertex(phrase);
//    cout << "Added Vertex" << endl;
    p = search(parent);
//    cout << "Refind parent: " << *p << endl;
    std::size_t fi = _gStruct.Graph<gnl>::getIndex(*p);
    std::size_t gi = _gStruct.Graph<gnl>::getIndex(phrase);
//    cout << "Parent found index: " << fi << endl;
//    cout << "phrase index: " << gi << endl;
//    cout << "SIZE: " << _gStruct.size() << endl;
    if(fi >= _gStruct.size() || gi >= _gStruct.size()) return;
    if(fi < 0 || gi < 0) return;
    _gStruct.addEdge(fi,gi,from,to);
//    cout << "DONE" << endl;
}

void Grammar::connect(const gnl &phrase, const gnl &child, GrammarPhrase from, GrammarPhrase to){
    gnl* f = Grammar::search(phrase);
    gnl* c = Grammar::search(child);
    if(!f || !c) return;
    _gStruct.addEdge(_gStruct.getIndex(*f),_gStruct.getIndex(*c),from,to);
}

gnl *Grammar::search(const gnl &phrase){
    return _gStruct.find(phrase);
}

//bool Grammar::isConnected(GrammarPhrase phraseA, GrammarPhrase phraseB){

//}

//bool Grammar::exist(const gnl& phrase, size_t size){
//    return find(phrase);
//}

//void Grammar::add(const gnl& G, const gnl& parent, GrammarPhrase from, GrammarPhrase to){
//    gnl* f = Grammar::find(parent);
//    if(!f) return;
//    _gStruct.addVertex(G);
//    f = Grammar::find(parent);
//    std::size_t fi = _gStruct.getIndex(*f);
//    std::size_t gi = _gStruct.getIndex(G);
//    if(fi >= _gStruct.size() || gi >= _gStruct.size()) return;
//    if(fi < 0 || gi < 0) return;
////    cout << "fi: " << fi << endl;
////    cout << "gi: " << gi << endl;
////    cout << "SIZE: " <<_gStruct.size() << endl;

//    _gStruct.addEdge(fi,gi,from,to);

//}

//void Grammar::connect(const gnl& phrase, const gnl& child, GrammarPhrase from, GrammarPhrase to){
//    gnl* f = Grammar::find(phrase);
//    gnl* c = Grammar::find(child);
//    if(!f || !c) return;
//    _gStruct.addEdge(_gStruct.getIndex(*f),_gStruct.getIndex(*c),from,to);
//}

//gnl *Grammar::find(const gnl& phrase){
//    return _gStruct.find(phrase);
//}




//void Grammar::createS(){
//    gnl  gL;
//    gL.insertHead(SENTENCE);
//    _gStruct.addVertex(gL);
//}
