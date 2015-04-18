#ifndef GRAMMAR_H
#define GRAMMAR_H
#include <iostream>
#include <vector>
#include <map>
#include "LabelledGraph.h"

namespace nlp{
    enum GrammarPhrase{
        UNKNOWN     = 0,
        DEFAULT     = 1,
        SENTENCE    = 2,
        NOUNPHRASE  = 3,
        VERBPHRASE  = 4,
        PREPPHRASE  = 5,
        NOMINAL     = 6,
        NOUN        = 7,
        VERB        = 8,
        PREP        = 9,
        DETERMINER  = 10
    };
    static const std::size_t gpSize = 10;
    static const GrammarPhrase gpList[] ={
        UNKNOWN,
        DEFAULT,
        SENTENCE,
        NOUNPHRASE,
        VERBPHRASE,
        PREPPHRASE,
        NOMINAL,
        NOUN,
        VERB,
        PREP,
        DETERMINER
    };

    static std::map<GrammarPhrase,std::string> phraseLookUp = {
        {    UNKNOWN,       "Unknown"       },
        {    DEFAULT,       "Default"       },

        {    SENTENCE,      "Sentence"      },
        {    NOUNPHRASE,    "Noun Phrase"   },
        {    VERBPHRASE,    "Verb Phrase"   },
        {    PREPPHRASE,    "Prep. Phrase"  },
        {    NOMINAL,       "Nominal"       },
        {    NOUN,          "Noun"          },
        {    VERB,          "Verb"          },
        {    PREP,          "Preposition"   },
        {    DETERMINER,    "Determiner"    }

    };

    //struct GrammarNode{
    //    GrammarPhrase _phrase;
    //    GrammarNode(GrammarPhrase phrase = DEFAULT){
    //        _phrase = phrase;
    //    }
    //    friend std::ostream& operator <<(std::ostream& out, const GrammarNode& G){
    //        out << phraseLookUp[G._phrase];
    //        return out;
    //    }
    //    friend bool operator ==(const GrammarNode& L, const GrammarNode& R){
    //        return L._phrase == R._phrase;
    //    }
    //};

    //template <typename Item>
    //struct ListContainer{
    //    std::vector<Item>* _L;
    //    ListContainer(){
    //        _L = new std::vector<Item>();
    //    }
    //    ListContainer(const ListContainer<Item>& L){
    //        typename std::vector<Item>::iterator it = L.front();
    //        while(it != L.back()){
    //            insertEnd(*it);
    //            ++it;
    //        }
    //    }
    //    ListContainer<Item>& operator =(const ListContainer<Item>& L){
    //        _L->clear();
    //        typename std::vector<Item>::iterator it = L.front();
    //        while(it != L.back()){
    //            insertEnd(*it);
    //            ++it;
    //        }
    //        return *this;
    //    }

    //    void insertHead(const Item& I){
    //        _L->insert(_L->begin(),I);
    //    }
    //    void insertEnd(const Item& I){
    //        _L->insert(_L->end(),I);
    //    }
    //    typename std::vector<Item>::iterator front() const{
    //        return _L->begin();
    //    }
    //    typename std::vector<Item>::iterator back() const{
    //        return _L->end();
    //    }

    //    friend std::ostream& operator <<(std::ostream& out, ListContainer<Item> G){
    //        typename std::vector<Item>::iterator it = G._L->begin();
    //        while(it != G._L->end()){
    //            out << *it << "|";
    //            ++it;
    //        }
    //        return out;
    //    }
    //    friend bool operator ==(const ListContainer<Item>& L, const ListContainer<Item>& R){
    //        return *L._L == *R._L;
    //    }
    //    ~ListContainer(){
    //        delete _L;
    //    }
    //};

    template <typename Item>
    struct Container{
        std::vector<Item> _vec;
        Container(){

        }
        void insertBegin(const Item& I){
            _vec.insert(_vec.begin(),I);
        }
        void insertEnd(const Item& I){
            _vec.insert(_vec.end(),I);
        }
    //    typename std::vector<Item>::iterator front() const{
    //        return _vec.begin();
    //    }
    //    typename std::vector<Item>::iterator back() const{
    //        return _vec.end();
    //    }

        friend std::ostream& operator <<(std::ostream& out, Container<Item> G){
            typename std::vector<Item>::iterator it = G._vec.begin();
            out << "{";
            while(it != G._vec.end()){
                out << *it << "|";
                ++it;
            }
            out << "}";
            return out;
        }
        friend bool operator ==(const Container<Item>& L, const Container<Item>& R){
            return L._vec == R._vec;
        }
    //    ~Container(){
    //        cout <<"DETROY: " << endl;
    //    }

    };

    typedef Container<GrammarPhrase> gnl;

    class Grammar{
    private:
        //How to store the Grammar
        //Tree?
        //Graph?
        //How to store multiple phrases in a node

        LabelledGraph<gnl,GrammarPhrase> _gStruct;



    public:
        Grammar();
        void add(const gnl& phrase, const gnl& parent, GrammarPhrase from = DEFAULT, GrammarPhrase to = DEFAULT);
        void connect(const gnl& phrase, const gnl& child,GrammarPhrase from = DEFAULT, GrammarPhrase to = DEFAULT);
        gnl* search(const gnl& phrase);

        friend std::ostream& operator <<(std::ostream& out, const Grammar& G){
            out << G._gStruct;
            return out;
        }
        void printDef(){
            _gStruct.print();
        }

        //In the structure, each phrase is in a sense unique, in that if there exist
        //multiple 'nominals' in the structure, no matter what leads to the nominal, each
        //nominal can go to every possible path any other nominal can go
        //So in this sense, the phrases are unique, thus we can just identify them
        //with their names.
        //If we wish to see if one phrase can lead to another, it does not matter if there
        //are multiple versions of this phrase in the structure, if one of them can lead to the
        //other phrase, they all can.



    //    //In the structure, does this phrase exist?
    //    bool exist(const gnl&, std::size_t size);

    //    void add(const gnl& G, const gnl &phrase, GrammarPhrase from = DEFAULT, GrammarPhrase to = DEFAULT);

    //    void connect(const gnl& phrase, const gnl& child, GrammarPhrase from = DEFAULT, GrammarPhrase to = DEFAULT);

    //    gnl* find(const gnl &phrase);

    //    friend std::ostream& operator <<(std::ostream& out, const Grammar& G){
    //        out << G._gStruct;
    //        return out;
    //    }

    };
}


#endif // GRAMMAR_H
