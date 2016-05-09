//
// Created by 王鹏飞 on 16/5/5.
//

#ifndef DIRT_TEMPLATESFROMTREE_H
#define DIRT_TEMPLATESFROMTREE_H

#include <set>
#include <string>
#include <map>
#include <stack>

#include "TreeNode.h"

template <typename T>
class TemplatesFromTree {


    std::set<std::string> templates_path;
    //std::map<std::string,std::string> id_to_path;
    AbstractTree<T>* tree;

    void CreateTemplates();

    //direction = true means up
    std::string halfPathToString(AbstractNode<T>*begin,AbstractNode<T>*end,bool direction);

    std::string posOfInfo(std::string pos);

    std::string dependencyInfo(AbstractNode<T>*node,bool direction);
};


#endif //DIRT_TEMPLATESFROMTREE_H
