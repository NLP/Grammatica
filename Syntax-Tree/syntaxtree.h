#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H
#include "Tree.h"
#include "../Grammar Structure/Grammar-with-Map/grammar.h"
//#include "../../../Parser/Tagger/word.h"
//#include "../../../CONFIG/config.h"
#include "syntaxword.h"

/**
 * @brief GPSWpair typedef for std::pair<GrammarPhrase,SyntaxWord>
 */
typedef std::pair<GrammarPhrase,SyntaxWord> GPSWpair;

/**
 * @brief The GSContainerpair struct Container for a GPSWpair
 */
struct GSContainerpair{
    /**
     * @brief _d the pair
     */
    GPSWpair _d;

    /**
     * @brief GSContainerpair Default Constructor
     */
    GSContainerpair(){}

    /**
     * @brief GSContainerpair Constructor
     * @param g GrammarPhrase
     * @param W SyntaxWord
     */
    GSContainerpair(GrammarPhrase g, const SyntaxWord& W){
        _d = GPSWpair(g,W);
    }

    /**
     * @brief operator << insertion
     * @param out output stream
     * @param G Container
     * @return output stream
     */
    friend std::ostream& operator <<(std::ostream& out, const GSContainerpair& G){
        out << "( " << phraseLookUp[G._d.first] << " , " << G._d.second << " )";
        return out;
    }
};

/**
 * @brief GtSpair typedef for GSContainerpair
 */
typedef GSContainerpair GtSpair;

/**
 * @brief TNpair typedef for TreeNode<GtSpair>
 */
typedef TreeNode<GtSpair> TNpair;

/**
 * @brief Tpair typedef for Tree<GtSpair>
 */
typedef Tree<GtSpair> Tpair;

/**
 * @brief The SyntaxTree class The Tree specialized for holding syntax and words
 * INHERITS: from Tree
 */
class SyntaxTree: public Tree<GtSpair>{
private:
    /**
     * @brief _st the sentence type
     */
    SentenceType _st;
    void recurHead(TNpair* root);
    void recurObj(TNpair* root, const Word &W, SyntaxObject S);
    Word getHeadWord(GrammarPhrase g, TNpair::TNvector W);

    TNpair* findPhrase(TNpair *start, GrammarPhrase find) const;
    void setSubj(TNpair* sentence);
    void setMV(TNpair* sentence);
    void setDO(TNpair* sentence);
    void setIDO(TNpair* sentence);
    void setQ(TNpair* sentence);
    void setAux(TNpair* sentence);
    size_t hasDef(TNpair *phrase, GrammarPhrase g);

public:
    SyntaxTree();
    SyntaxTree(TNpair* root);
    SyntaxTree(const SyntaxTree& S);
    SyntaxTree& operator =(const SyntaxTree& S);
    ~SyntaxTree();

    // Public static function
    static string getSyntaxEncoding(const vector<SyntaxWord>& SWord);
    //These are functions for Parser only
    void assignHeads();
    void assignObjects();
    void determineType();

    //Do stuff to current
    //Create child (Must not have any children)
    void addDef(GPlist def);
    void removeDef();
    GPlist getDef();
    GrammarPhrase getPhrase();
    bool atLeaf();
    TNpair* getLastLeaf();
    TNpair* getFirstLeaf();
    TNpair* getChildAt(std::size_t i);
    bool atLastLeaf();
    bool atFirstLeaf();
    std::size_t leavesBefore();
    std::size_t childIndex(TNpair* parent, TNpair* child);

    std::vector<SyntaxWord> getAll() const;
    std::vector<SyntaxWord> getObj(SyntaxObject S) const;
    SentenceType getSentenceType() const;
    SyntaxObject askingFor() const;
};



#endif // SYNTAXTREE_H
