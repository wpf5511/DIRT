//
// Created by 王鹏飞 on 16/5/5.
//

#ifndef DIRT_TEMPLATESFROMTREE_H
#define DIRT_TEMPLATESFROMTREE_H

#include <set>
#include <string>
#include <map>
#include <stack>
#include <fstream>

#include "TreeNode.h"



struct TreeComp{

    bool operator()(TemplateTree t1,TemplateTree t2)const{
        if(t1.nodes.size()!=t2.nodes.size()){
            return true;
        }
        else{
            for(int i=0;i<t1.nodes.size();i++){
                if((*(t1.nodes[i]))!=(*(t2.nodes[i]))){
                    return true;
                }
            }
        }
        return false;
    }
};

/*struct TripleComp{
    bool operator()(Triple* t1,Triple* t2){
        return t1->w!=t2->w||t1->slot!=t2->slot||t1->template_path!=t2->template_path;
    }
};*/

struct Tri_Pair;
struct Word_Pair;

//extern
extern int i;

extern std::map<Triple,int> triples;

extern std::map<TemplateTree,int> templateTrees;

extern std::map<int,TemplateTree> id_to_Tree;

extern std::map<Word_Pair,std::map<int,int>> template_matrix;

extern std::map<Real_Triple,int> r_triples;

extern std::set<std::string> noun_phrases;

extern std::set<std::string> verb_phrases;


template <typename T>
class TemplatesFromTree {

public:

    std::set<std::string> templates_path;
    //std::map<std::string,std::string> id_to_path;
    AbstractTree<T>* tree;

    //below should be global
    /*std::map<Triple*,int,TripleComp> tri_count;

    std::map<TemplateTree*,int,TreeComp> templateTrees;

    std::map<int,TemplateTree*> id_to_Tree;*/

    void CreateTemplates();

    static void save_template(std::map<int,TemplateTree> id_to_tree,std::string filename);

    static void save_path(std::map<int,TemplateTree> id_to_tree,std::string filename);

    static void save_nps(std::set<std::string>,std::string filename);

    //direction = true means up
    std::string halfPathToString(AbstractNode<T>*begin,AbstractNode<T>*end,bool direction,TemplateTree* templateTree);

    std::string posOfInfo(std::string pos);

    std::string dependencyInfo(AbstractNode<T>*node,bool direction);

    //
    void extractNP();
    void extractVP();
};

struct Tri_Pair{
    Word x;
    Word y;

    std::map<int,int> list_of_templates;

    Tri_Pair(){

    }

    Tri_Pair(Word x1,Word y1):x(x1),y(y1){

    }

};

struct Word_Pair{
    Word x;
    Word y;

    Word_Pair(Word x1,Word y1):x(x1),y(y1){

    }

    bool operator <(Word_Pair other) const{
        if(x!=other.x){
            return x<other.x;
        }
        else
            return y<other.y;

    }


};

#endif //DIRT_TEMPLATESFROMTREE_H
