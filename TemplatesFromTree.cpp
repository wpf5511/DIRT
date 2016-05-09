//
// Created by 王鹏飞 on 16/5/5.
//

#include "TemplatesFromTree.h"

template <typename T>
void TemplatesFromTree<T>::CreateTemplates() {

    std::vector<AbstractNode<T>*> endPoints = tree->findEndpoints();

    for(auto begin:endPoints){
        for(auto end:endPoints){
            //不是直接的父子关系
            if(end!=begin&&end->get_parent()!=begin->get_id()&&begin->get_parent()!=end->get_id()){
                AbstractNode<T>* common = tree->getLeastCommonAncestorOf(begin,end);//不进行路径过滤先
                std::string up = halfPathToString(begin,common, true);
                std::string down = halfPathToString(end,common, false);
                std::string path = up.append("<").append(common->get_lexeme())
                .append(">").append(down);
                templates_path.insert(path);
            }
        }
    }
}

template <typename T>
std::string TemplatesFromTree<T>::halfPathToString(AbstractNode<T> *begin, AbstractNode<T> *common, bool direction) {
    std::stack<std::string> path;
    if(begin!=common){
        path.push(dependencyInfo(begin,direction));//省略push开头词
        auto current = tree->get_Node(begin->get_parent());
        while(current!=common){
            path.push(current->get_lexeme());
            path.push(dependencyInfo(current,direction));
        }
    }
    std::string delimiter =">";
    if(direction){
        std::stack<std::string> temp;
        while(!path.empty()){
            temp.push(path.top());
            path.pop();
        }
        path = temp;
        delimiter = "<";
    }

    std::string sb;
    sb.append(path.top());
    path.pop();
    while (!path.empty()){
        sb.append(delimiter);
        sb.append(path.top());
        path.pop();
    }

    return sb;

}


template <typename T>
std::string TemplatesFromTree<T>::posOfInfo(std::string ctb_pos) {

    std::string ret;
    burstpos bur_pos = ctbpos::ctb_to_burst.at(ctb_pos);
    switch (bur_pos){
        case NOUN:
            ret = "n";
            break;
        case VERB:
            ret = "v";
            break;
        case PRONOUN:
            ret = "n";
            break;
        case PREPOSITION:
            ret = "p";
            break;
        case DET_NUM:
            ret = "d";
            break;
        case ADVERB:
            ret = "a";
            break;
        case CONJUNCTION:
            ret = "p";
            break;
        default:
            ret = "o";
            break;

    }
    return ret;
}

template <typename T>
std::string TemplatesFromTree<T>::dependencyInfo(AbstractNode<T> *node,bool direction) {

    std::string node_pos_info = posOfInfo(node->get_pos());
    std::string parent_pos_info = posOfInfo(tree->get_Node(node->get_parent()));
    if(direction){
        return node_pos_info.append(":").append(parent_pos_info);
    }
    else{
        return parent_pos_info.append(":").append(node_pos_info);
    }
}