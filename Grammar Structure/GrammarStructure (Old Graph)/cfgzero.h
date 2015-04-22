//#ifndef CFGZERO_H
//#define CFGZERO_H
//#include "grammar.h"
///* HOW THE GRAPH WORKS
// * Each Node represents either the left or right sides of the definition
// * The first Label of the edge indicates which phrase in the node is the source of the edge
// * The second label indicates the destination phrase in the connected node
// * (Ex: For the very first definition, we have S->NP+VP.
// * Let's say the next definition is NP->D+NN.
// * Then there will be an edge from the NPVP node to the DNN node.
// * To indicate the source and the destination, the edge label will say NP:ALL
// * to indicate that the edge is from NP specifically (not VP) and goes to the entirety of the node.
// * Now for a definition like NP->D+NN, NN->N+NN, NN->N, there is some recursion in the definition,
// * i.e. NP->D+(N+(N+(...))). So to indicate the source and destination for the edges, we write
// * From NPVP to DNN, A:NP,B:Default; From DNN to NNN, A:NN,B:Default; From DNN to N, A:NN,B:Default;
// * From NNN to DNN, A:NN,B:NN; (Default will be represented as ALL)
// */
//const std::map<std::string,GPvector> gpvecList = {

//};
//class CFGZero:public Grammar{
//private:
//    void createCFG();
//public:
//    CFGZero();
//};
///* The Simplest Context-Free Grammar defined in the Book: L0
// * Sentence -> Noun Phrase + Verb Phrase
// * Noun Phrase -> Pronoun
// * Noun Phrase -> Proper Noun
// * Noun Phrase -> Determiner + Nominal
// * Nominal -> Noun + Nominal
// * Nominal -> Noun
// * Verb Phrase -> Verb
// * Verb Phrase -> Verb + Noun Phrase
// * Verb Phrase -> Verb + Noun Phrase + Preposition Phrase
// * Verb Phrase -> Verb + Preposition Phrase
// * Preposition Phrase -> Preposition + Noun Phrase
// *
// * Follow beginning at Sentence and substitute each part on the Right Hand Side
// * With their respective definitions.
// * Once you get down to the lowest level (The Part of Speech Level) you are done
// * After that you can link each part of speech that appears in the tree with their
// * respective word
// *
// * For Imperatives (Commands), there are additional definitions:
// * Sentence -> Verb Phrase
// *
// * For more advanced structures, there will be adjectives and adverbs to describe
// * Along with quantifiers to provide features for the words (ie ten, many, the color red)
// */
//#endif // CFGZERO_H
