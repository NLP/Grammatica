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

//GO HERE:
//www.ucl.ac.uk/internet-grammar/frames/contents.htm

//Phrases
/* Phrases always have the form Pre-Head-Post
 * The Head is the most important part and defines the entire phrase
 *Noun Phrase:
 * In the Pre is usually Determiners and Adjectives
 * The Post is usually began with that, which, who, whose, etc
 * The Head is the Noun
 *Verb Phrase:
 * The Pre will be either a negator (never, not) or an adverb phrase
 * There MUST be a post for Transitive Verb Phrases (indicates Direct Object, etc...)
 * Intransitive Verb Phrases NEVER have a Post
 * Most verbs are both...
 * The Head is the Verb
 *Adjective Phrase:
 * Head is the Adjective
 * Pre will include adverb phrases
 * Post will be whatever, usually infinitives or of-phrases
 *Adverb Phrase:
 * Pre will include Averb Phrases
 * Post will be RARE, but may include for-phrases
 *Prepositional Phrase:
 * Pre is rare
 * Head is the preposition
 * Post will be a noun phrases
 */

 //Clauses
 /*Clauses require a subject and a verb
  * Finite clauses are ones whose main verb is finite
  * Infinite clauses have infinitive main verbs, these are dependent clauses and require an inpendent clause
  */
//Indentifying the Subject, Main Verb, Direct Object, Indirect Object...
/*Subject:
 * Declarative Sentences will have the Subject before the Main Verb
 * Interrogative Sentences (Questions) will have the subject after the Main Verb
 * Imperative Sentences will have no subject (implied 'You' subject)
 * HOWEVER, Extraposition will allow subjects to come at the END for declaratives
 * -If there is an anticipatory it that begins the sentence
 * -
 * Most of the time will be the Noun Phrase before the Main Verb
 * Finite That-Clauses before the main verb
 * Nominal Relative Clauses before the main verb
 * To-infinitive Clauses before the main verb
 * Present Progressive -ing Clauses before the main verb
 * Prepositional Phrases before the Main Verb, tpyically for time and space
 * There/That-Existential Sentences before the main verb
 * It-description Sentences before the main verb
 * There will be ONE subject for EACH main verb
 *Main Verb:
 * There will be ONE main verb for each independent clause
 * Subject and Main Verb will ALWAYS agree on plurality in the present tense and to third person subjects
 *Direct Object:
 *
 */

//Basic Syntax Tree Outline
//1. Create Syntax Tree
//2. Attach corresponding Tokens to the Leaves of the Tree (Set the second of the pair's word to that word)
//3. From Bottom Up, Find the head word of each subtree and assign it as the word of the node
//4. From Top Down, Find the objects for each node
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
        _so = UNKNOWN; //Does Word have a default constructor?
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
