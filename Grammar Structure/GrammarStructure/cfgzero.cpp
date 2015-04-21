#include "cfgzero.h"

void CFGZero::createCFG(){
    //Create the Grammar here


    //Create S
    GPvector sent;
    sent.addEnd(gpList[SENTENCE]);
    //Create NP+VP
    GPvector npvp;
    npvp.addEnd(gpList[NOUNPHRASE]);
    npvp.addEnd(gpList[VERBPHRASE]);
    //Create NP
    GPvector np;
    np.addEnd(gpList[NOUNPHRASE]);
    //Create VP
    GPvector vp;
    vp.addEnd(gpList[VERBPHRASE]);
    //Create D+N
    GPvector dn;
    dn.addEnd(gpList[DETERMINER]);
    dn.addEnd(gpList[NOUN]);
    //Create D
    GPvector d;
    d.addEnd(gpList[DETERMINER]);
    //Create N
    GPvector n;
    n.addEnd(gpList[NOUN]);
    //Create V
    GPvector v;
    v.addEnd(gpList[VERB]);
    //Create V+NP
    GPvector vnp;
    vnp.addEnd(gpList[VERB]);
    vnp.addEnd(gpList[NOUNPHRASE]);
    //Create V+NP+PP
    GPvector vnppp;
    vnppp.addEnd(gpList[VERB]);
    vnppp.addEnd(gpList[NOUNPHRASE]);
    vnppp.addEnd(gpList[PREPPHRASE]);
    //Create V+PP
    GPvector vpp;
    vpp.addEnd(gpList[VERB]);
    vpp.addEnd(gpList[PREPPHRASE]);
    //Create PP
    GPvector pp;
    pp.addEnd(gpList[PREPPHRASE]);
    //Create P
    GPvector p;
    p.addEnd(gpList[PREP]);
    //Create P + NP
    GPvector pnp;
    pnp.addEnd(gpList[PREP]);
    pnp.addEnd(gpList[NOUNPHRASE]);

    //Add to Grammar & Define
    // Define S->NP+VP
    Grammar::addPhrase(npvp,getIndex(sent),SENTENCE,ALL);
    //Define NP->N
    Grammar::addPhrase(n,getIndex(npvp),NOUNPHRASE,ALL);
    //Define NP->D+N
    Grammar::addPhrase(dn,getIndex(npvp),NOUNPHRASE,ALL);
    //Define VP->V
    Grammar::addPhrase(v,getIndex(npvp),VERBPHRASE,ALL);
    //Define VP->V+NP
    Grammar::addPhrase(vnp,getIndex(npvp),VERBPHRASE,ALL);
    //Define VP->V+NP+PP
    Grammar::addPhrase(vnppp,getIndex(npvp),VERBPHRASE,ALL);
    //Define VP->V+PP
    Grammar::addPhrase(vpp,getIndex(npvp),VERBPHRASE,ALL);
    //Define PP->P+NP
    Grammar::addPhrase(pnp,getIndex(vpp),PREPPHRASE,ALL);
    Grammar::addPhrase(pnp,getIndex(vnppp),PREPPHRASE,ALL);
    //Connect NP's
    Grammar::addRule(getIndex(vnp),getIndex(npvp),NOUNPHRASE,NOUNPHRASE);
    Grammar::addRule(getIndex(pnp),getIndex(npvp),NOUNPHRASE,NOUNPHRASE);
}

CFGZero::CFGZero():Grammar::Grammar(){
    createCFG();
}
