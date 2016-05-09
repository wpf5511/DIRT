//
// Created by 王鹏飞 on 16/5/5.
//

#include "TreeNode.h"


int ZparNode::get_parent() {
    return this->parent_id;
}

ZparNode::ZparNode(std::string lexeme, std::string pos, int parent_id, std::string dependency) {
    this->lexeme = lexeme;
    this->pos = pos;
    this->parent_id =parent_id;
    this->dependency = dependency;
}

void ZparNode::set_id(int j) {
    this->id = j;
}

std::vector<int> ZparNode::get_children(AbstractTree<int>* Tree) {

    return  Tree->get_children_array().at(this->id);

}

std::string ZparNode::get_pos() {
    return this->pos;
}

std::string ZparNode::get_dependency() {
    return this->dependency;
}

std::string ZparNode::get_lexeme() {
    return this->lexeme;
}


void ZparTree::add_node(ZparNode* node) {

    int j = this->nodes.size();
    node->set_id(j);
    this->nodes.push_back(node);
}

void ZparTree::set_children_array() {
    for(int i=0;i<nodes.size();i++){
        if(nodes[i]->get_parent()!=-1){
            children_array[nodes[i]->get_parent()].push_back(i);
        }
    }

    for(int i=0;i<nodes.size();i++){
        if(children_array[nodes[i]->get_Id()].empty()){
            nodes[i]->isLeaf= true;
        }
    }
}

std::map<int,std::vector<int>> ZparTree::get_children_array() {
    return this->children_array;
}

int ZparNode::get_id() {
    return this->id;
}

std::vector<AbstractNode<int>*> ZparTree::findEndpoints() {

    std::vector<AbstractNode<int>*> ret;
    for(auto point:this->nodes){
        std::string ctb_pos = point->pos;
        burstpos bur_pos = ctbpos::ctb_to_burst.at(ctb_pos);
        if(bur_pos==burstpos::NOUN||bur_pos==burstpos::PRONOUN){
            ret.push_back(point);
        }
    }
    return ret;
}

void ZparTree::set_lcaMatrix() {

    int root_id;
    for(auto node:nodes){
        if(node->get_parent()==-1)
            root_id = node->get_Id();
    }

    for(int i=0;i<nodes.size();i++){
        for(int j=i+1;j<nodes.size();j++){
            if(i!=root_id && j!=root_id){
                auto path1 = path_to_ancestor(i,root_id);
                auto path2 = path_to_ancestor(j,root_id);
                auto lca_id = get_lca_id(path1,path2);

                lcaMatrix[i][j]=lcaMatrix[j][i]=lca_id;

            }
        }
    }
}

AbstractNode<int>* ZparTree::get_Node(int id) {
    return nodes[i];
}

std::vector<int> ZparTree::path_to_ancestor(int current, int ancestor) {

    std::vector<int>Path;

    while(nodes[current]->get_parent()!=ancestor){
        Path.push_back(current);
        current = nodes[current]->get_parent();
    }
    Path.push_back(ancestor);//push root node;

    return Path;
}

int ZparTree::get_lca_id(std::vector<int>path1, std::vector<int>path2) {

    for(auto i=path1.rbegin(),j=path2.rbegin();i!=path1.rend()&&j!=path2.rend();i++,j++){

        if(i==path1.rend()){
            return *i.base();
        }
        if(j==path2.rend()){
            return *j.base();
        }
        if(*i!=*j){
            return *i.base();
        }
    }
}

AbstractNode<int>* ZparTree::getLeastCommonAncestorOf(AbstractNode<int> *begin, AbstractNode<int> *end) {
    int begin_id = begin->get_Id();
    int end_id = end->get_Id();

    int lca_id = lcaMatrix[begin_id][end_id];

    return nodes[lca_id];
}
