#include "parser.h"



Parser::Parser(){
    _current = nullptr;
}

Parser::Parser(const std::vector<Word>& words, const Grammar &G){
    _current = nullptr;
    _words = words;
    _G = G;
}
std::vector<SyntaxTree> Parser::loopedParse(TreeNode<GtSpair> *root){
    std::vector<SyntaxTree> validTrees;
    if(recursiveDescent(_current,0)){
        validTrees.insert(validTrees.begin(),SyntaxTree(_current));
        while(backtrack(_current)){
            validTrees.insert(validTrees.begin(),SyntaxTree(_current));
        }
    }
    return validTrees;

}
//Requires DEf getNextDef(gp, def) //if def is empty then gets the first//if there is no next def returns an empty def
//Requires type getNextType(word, type) //if type is inval, then gets first //if there is no next type returns inval
//Requires word getNextWord(word, secondary word) //if word has inval type, gets first//if there is no next word, returns inval word
bool Parser::recursiveDescent(TreeNode<GtSpair>* root, int i = 0){
    if(!root) return false;
    if(root->data().first == SENTENCE)
        i = 0;
    std::vector<GrammarPhrase> def = getDef(root->children()); //GETS THE DEFINITION FORM OF THE CHILDREN OF A NODE
    def = getNextDef(root->data().first,def);
    if(def.empty()){ //it is a leaf
        Word w = getNextWord(i++); //make default construct create a word of inval type and empty token
        WordType wt = getNextType(w,IGNORETHIS);
        while(wt != IGNORETHIS){
            if(wt == convertWTtGP(wt)){ //Convert (NEED CONVERTER)
                w = singleOut(w,wt); //REMOVE ALL OTHER WORD TYPES FOR THAT WORD
                root->data().second._word = w;
                return true;
            }
            wt = getNextType(w,wt);
        }
        return false;
    }
    while(!def.empty()){
        createChild(root,def); //CREATE CHILDREN FOR ROOT FOR EACH PHRASE IN DEF
        bool check = false;
        TreeNode<GtSpair>::TNvector::iterator it = root->children().begin();
        while(it != root->children().end()){
            check = recursiveDescent(*it);
            if(!check){
                root->setChildren(TreeNode<GtSpair>::TNvector());
                break;
            }
        }
        if(check){
            return true;
        }
        def = getNextDef(root->data().first,def);
    }
    return false;
}

bool Parser::backtrack(TreeNode<GtSpair> *root)
{

}

void Parser::attachWords();
void Parser::attachHeads();
void Parser::attachSyntax();
std::vector<SyntaxTree> Parser::parse(){
    _current = new TreeNode<GtSpair>(GtSpair(SENTENCE,SyntaxWord()));
    _valid = loopedParse(_current);
    attachWords();
    attachHeads();
    attachSyntax();
    return _valid;
}

void Parser::reset(){
    _valid.clear();
    rt::clear(_current);
}

void Parser::setWords(const std::vector<Word>& words){
    _words = words;
}

std::vector<Word> Parser::getWords(){
    return _words;
}

void Parser::setGrammar(const Grammar &G){
    _G = G;
}

Grammar Parser::getGrammar(){
    return _G;
}

