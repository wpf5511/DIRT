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

    bool operator()(TemplateTree* t1,TemplateTree* t2){
        if(t1->nodes.size()!=t2->nodes.size()){
            return true;
        }
        else{
            for(int i=0;i<t1->nodes.size();i++){
                if(*(t1->nodes[i])!=*(t2->nodes[i])){
                    return true;
                }
            }
        }
        return false;
    }
};

struct TripleComp{
    bool operator()(Triple* t1,Triple* t2){
        return t1->w!=t2->w||t1->slot!=t2->slot||t1->template_path!=t2->template_path;
    }
};

struct Tri_Pair;

//extern
extern int i;

extern std::map<Triple*,int,TripleComp> tri_count;

extern std::map<TemplateTree*,int,TreeComp> templateTrees;

extern std::map<int,TemplateTree*> id_to_Tree;

extern Tri_Pair tri_pair;


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

    //direction = true means up
    std::string halfPathToString(AbstractNode<T>*begin,AbstractNode<T>*end,bool direction,TemplateTree* templateTree);

    std::string posOfInfo(std::string pos);

    std::string dependencyInfo(AbstractNode<T>*node,bool direction);
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

#endif //DIRT_TEMPLATESFROMTREE_H
