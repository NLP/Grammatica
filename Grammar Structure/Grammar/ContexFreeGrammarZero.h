#ifndef CONTEXFREEGRAMMARZERO_H
#define CONTEXFREEGRAMMARZERO_H
#include "grammar.h"
using namespace nlp;
/* HOW THE GRAPH WORKS
 * Each Node represents either the left or right sides of the definition
 * The first Label of the edge indicates which phrase in the node is the source of the edge
 * The second label indicates the destination phrase in the connected node
 * (Ex: For the very first definition, we have S->NP+VP.
 * Let's say the next definition is NP->D+NN.
 * Then there will be an edge from the NPVP node to the DNN node.
 * To indicate the source and the destination, the edge label will say NP:ALL
 * to indicate that the edge is from NP specifically (not VP) and goes to the entirety of the node.
 * Now for a definition like NP->D+NN, NN->N+NN, NN->N, there is some recursion in the definition,
 * i.e. NP->D+(N+(N+(...))). So to indicate the source and destination for the edges, we write
 * From NPVP to DNN, A:NP,B:Default; From DNN to NNN, A:NN,B:Default; From DNN to N, A:NN,B:Default;
 * From NNN to DNN, A:NN,B:NN; (Default will be represented as ALL)
 */
class ContextFreeGrammarZero{
private:
    Grammar _G;
    void createGrammar(){
        //Construct the definitions:
        //Create S
        gnl sent;
        sent.insertEnd(gpList[SENTENCE]);
        cout << sent << endl;
        //Create NP+VP
        gnl npvp;
        npvp.insertEnd(gpList[NOUNPHRASE]);
        npvp.insertEnd(gpList[VERBPHRASE]);
        //Create NP
        gnl np;
        np.insertEnd(gpList[NOUNPHRASE]);
        //Create VP
        gnl vp;
        vp.insertEnd(gpList[VERBPHRASE]);
        //Create D+NN
        gnl dnn;
        dnn.insertEnd(gpList[DETERMINER]);
        dnn.insertEnd(gpList[NOMINAL]);
        //Create D
        gnl d;
        d.insertEnd(gpList[DETERMINER]);
        //Create NN
        gnl nn;
        nn.insertEnd(gpList[NOMINAL]);
        //Create N+NN
        gnl nnn;
        nnn.insertEnd(gpList[NOUN]);
        nnn.insertEnd(gpList[NOMINAL]);
        //Create N
        gnl n;
        n.insertEnd(gpList[NOUN]);
        //Create V
        gnl v;
        v.insertEnd(gpList[VERB]);
        //Create V+NP
        gnl vnp;
        vnp.insertEnd(gpList[VERB]);
        vnp.insertEnd(gpList[NOUNPHRASE]);
        //Create V+NP+PP
        gnl vnppp;
        vnppp.insertEnd(gpList[VERB]);
        vnppp.insertEnd(gpList[NOUNPHRASE]);
        vnppp.insertEnd(gpList[PREPPHRASE]);
        //Create V+PP
        gnl vpp;
        vpp.insertEnd(gpList[VERB]);
        vpp.insertEnd(gpList[PREPPHRASE]);
        //Create PP
        gnl pp;
        pp.insertEnd(gpList[PREPPHRASE]);
        //Create P
        gnl p;
        p.insertEnd(gpList[PREP]);
        //Create P + NP
        gnl pnp;
        pnp.insertEnd(gpList[PREP]);
        pnp.insertEnd(gpList[NOUNPHRASE]);

        //Add to Grammar & Define
        //Define S
        // Define S->NP+VP
        _G.add(npvp,sent,SENTENCE,DEFAULT);
        //Define NP->N
        _G.add(n,npvp,NOUNPHRASE,DEFAULT);
        //Define NP->D+NN
        _G.add(dnn,npvp,NOUNPHRASE,DEFAULT);
        //Define VP->V
        _G.add(v,npvp,VERBPHRASE,DEFAULT);
        //Define VP->V+NP
        _G.add(vnp,npvp,VERBPHRASE,DEFAULT);
        //Define VP->V+NP+PP
        _G.add(vnppp,npvp,VERBPHRASE,DEFAULT);
        //Define VP->V+PP
        _G.add(vpp,npvp,VERBPHRASE,DEFAULT);
        //Define PP->P+NP
        _G.add(pnp,vpp,PREPPHRASE,DEFAULT);
        _G.add(pnp,vnppp,PREPPHRASE,DEFAULT);
        //Define NN->N+NN
        _G.add(nnn,dnn,NOMINAL,DEFAULT);
        //Define NN->N
        _G.add(n,dnn,NOMINAL,DEFAULT);
        //Connect NN's
        _G.connect(nnn,dnn,NOMINAL,NOMINAL);
        //Connect NP's
        _G.connect(vnp,npvp,NOUNPHRASE,NOUNPHRASE);
        _G.connect(pnp,npvp,NOUNPHRASE,NOUNPHRASE);
//        cout << G << endl;
    }

public:
    ContextFreeGrammarZero(){
        createGrammar();
    }
//    std::set<gnl> findNext(const gnl& start){
//        return _G.Graph<gnl>::neighbors(Graph<gnl>::getIndex(start));
//    }
    void printDef(){
        _G.printDef();
    }

    friend std::ostream& operator <<(std::ostream& out, const ContextFreeGrammarZero& G){
        out << G._G;
        return out;
    }
};
/* The Simplest Context-Free Grammar defined in the Book: L0
 * Sentence -> Noun Phrase + Verb Phrase
 * Noun Phrase -> Pronoun
 * Noun Phrase -> Proper Noun
 * Noun Phrase -> Determiner + Nominal
 * Nominal -> Noun + Nominal
 * Nominal -> Noun
 * Verb Phrase -> Verb
 * Verb Phrase -> Verb + Noun Phrase
 * Verb Phrase -> Verb + Noun Phrase + Preposition Phrase
 * Verb Phrase -> Verb + Preposition Phrase
 * Preposition Phrase -> Preposition + Noun Phrase
 *
 * Follow beginning at Sentence and substitute each part on the Right Hand Side
 * With their respective definitions.
 * Once you get down to the lowest level (The Part of Speech Level) you are done
 * After that you can link each part of speech that appears in the tree with their
 * respective word
 *
 * For Imperatives (Commands), there are additional definitions:
 * Sentence -> Verb Phrase
 *
 * For more advanced structures, there will be adjectives and adverbs to describe
 * Along with quantifiers to provide features for the words (ie ten, many, the color red)
 */
#endif // CONTEXFREEGRAMMARZERO_H
