#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H
#include "Tree.h"
#include "../../Grammar Structure/Grammar-with-Map/grammar.h"
#include "../../../Parser/Tagger/word.h"
//Holds a grammar rule tree attached at the very ends as leafs the words
//Then for each subtree, it finds the head word
//Give it functions to access these head words and identify which is which

//The syntax tree with have nodes which hold pairs of GrammarPhrase and a SyntaxWord
//The tree will be created with the grammar phrases from the Grammar Structure and with the SyntaxWord as empty
//Once the tree is completed and checked against the set of words, it will set the SyntaxWord of the leaves
//to their corresponding words

//Suggest: Make SyntaxWord into just Word and have the Syntax functions just calculate it
//SO we do not store the syntax
//Suggest: Once the tree is complete, just attach the word to the leaves and leave the syntax as none
//After we find the head word for each subtree and assign the syntaxword at that node with the corresponding head word
//Go from top to bottom and find out the syntax for each word
enum SyntaxObject{
    UNKNOWN,
    None,
    SUBJECT,
    MAINVERB,
    DIRECTOBJ,
    INDIRECTOBJ,
    MODIFIERVERB
};

static const std::map<SyntaxObject,std::string> syntaxLookUp = {
    {   UNKNOWN,        "Unknown"           },
    {   SUBJECT,        "Subject"           },
    {   MAINVERB,       "Main Verb"         },
    {   DIRECTOBJ,      "Direct Object"     },
    {   INDIRECTOBJ,    "Indirect Object"   },
    {   MODIFIERVERB,   "Modifier Verb"     }
};

static const SyntaxObject soList[] = {
    UNKNOWN,
    SUBJECT,
    MAINVERB,
    DIRECTOBJ,
    INDIRECTOBJ,
    MODIFIERVERB
};

enum PoSPhrase{
    UNKNOWN,
    NONE,
    NOUN,
    VERB,
    DETERMINER,
    PREP
};

//Possible coners: PosPhrase -> wordtype and vice-versa
//since word stores its parts of speech as a wordtype
static const std::map<PoSPhrase,std::string> posLookUp = {
    {UNKNOWN,       "Unknown"       },
    {NONE,          "None"          },
    {NOUN,          "Noun"          },
    {VERB,          "Verb"          },
    {DETERMINER,    "Determiner"    },
    {PREP,          "Preposition"   }
};

static const PoSPhrase posList[] = {
    UNKNOWN,
    NONE,
    NOUN,
    VERB,
    DETERMINER,
    PREP
};

bool isPoS(const GrammarPhrase& gp){
    for(auto& i : posList){
        if(posLookUp[i] == phraseLookUp[gp])
            return true;
    }
    return false;
}
bool isHeadWord(const GrammarPhrase& gp, const SyntaxWord& W){
    switch(gp){
    case PREPPHRASE:
    case NOUNPHRASE:{
        //if W is a noun
        return true;
        break;
    }
    case SENTENCE:
    case VERBPHRASE:{
        //if W is a verb
        return true;
        break;
    }
    default:{
        break;
    }
    }
    return false;
}

struct SyntaxWord{ //Container for a Word and a Syntactical Identifier
    SyntaxObject _so;
    NLP::Word _word;
    SyntaxWord(){
        _so = UNKNOWN;
        _word = NLP::Word(); //Does Word have a default constructor?
    }

    SyntaxWord(const SyntaxObject& so, const NLP::Word& word){
        _so = so;
        _word = word;
    }
};

typedef std::pair<GrammarPhrase,SyntaxWord> GtSpair;
class SyntaxTree: public Tree<GtSpair>{
private:
    //Finds a specified syntax in the tree
    TreeNode<GtSpair> *findSyntax(TreeNode<GtSpair>* root, SyntaxObject syntax);
    //Calculates the head word of the specified subtree
    SyntaxWord findHeadWord(TreeNode<GtSpair>* root);
    //Assigns the head word to each node in the tree (Sets the word in the syntaxword)
    void assignHead(TreeNode<GtSpair>* root);
public:
    SyntaxTree();
    SyntaxTree(const SyntaxTree& S);
    ~SyntaxTree();
    SyntaxTree& operator =(const SyntaxTree& S);

    TreeNode<GtSpair>* getMainVerb() const;
    TreeNode<GtSpair>* getSubject() const;
    TreeNode<GtSpair>* getDO() const;
    TreeNode<GtSpair>* getIDO() const;
    std::vector<TreeNode<GtSpair>*>& getAll() const;
    //Assigns the syntax to each node in the tree (Sets the syntax in the syntaxword)
    void assignSyntax(TreeNode<GtSpair> *root);

    SyntaxWord syntax(const TreeNode<GtSpair> *branch) const;
};

#endif // SYNTAXTREE_H
