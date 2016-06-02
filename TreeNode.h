//
// Created by 王鹏飞 on 16/5/5.
//

#ifndef DIRT_ABSTRACTNODE_H
#define DIRT_ABSTRACTNODE_H

#include <vector>
#include <string>
#include <map>
#include "Triple.h"
#include "ctbpos.h"


template <typename >class AbstractTree;

template<typename T>
class AbstractNode {
public:
    virtual T get_parent()=0;
    virtual T get_Id()=0;
    virtual std::vector<T> get_children(AbstractTree<T>*)=0;
    virtual std::string get_pos()=0;
    virtual std::string get_dependency()=0;
    virtual std::string get_lexeme()=0;
    bool isLeaf= false;
};

class ZparNode:public AbstractNode<int>{
public:
    virtual int get_parent();
    virtual std::vector<int> get_children(AbstractTree<int>*);
    virtual int get_Id();
    virtual std::string get_pos();
    virtual std::string get_dependency();
    virtual std::string get_lexeme();

    ZparNode(std::string lexeme,std::string pos,int parent_id,std::string dependency);
    ZparNode(const ZparNode &node);

    void set_id(int);

    int id;
    std::string lexeme;
    std::string pos;
    int parent_id;
    std::string dependency;
};

class TemplateNode:public ZparNode{
public:
    Slot slot;
    bool isSlot= false;

    int rewrite_index;// rewrite sentence's word position
    TemplateNode(int parent_id,std::string dependency,std::string pos,std::string lexeme);
    TemplateNode(AbstractNode<int>* zparNode);//TemplateNode 的dependency为pos:dependency:dependency
    void setSlot(Slot type);
    bool operator <(TemplateNode& other){
        if(id!=other.id)return id<other.id;
        if(lexeme!=other.lexeme)return lexeme<other.lexeme;
        if(pos!=other.pos)return pos<other.pos;
        return dependency<other.dependency;
    }

    bool operator !=(TemplateNode& other){
        return id!=other.id||lexeme!=other.lexeme||pos!=other.pos||dependency!=other.dependency;
    }

    std::string toString(){
        return lexeme+"\t"+pos+"\t"+std::to_string(parent_id)+"\t"+dependency;
    }
};

template <typename U>
class AbstractTree{
public:
    virtual std::map<U,std::vector<U>> get_children_array()=0;

    virtual std::vector<AbstractNode<U>*> findEndpoints()=0;

    virtual std::vector<AbstractNode<U>*> findVVpoints()=0;

    virtual AbstractNode<U>* getLeastCommonAncestorOf(AbstractNode<U> *begin,AbstractNode<U> *end)=0;

    virtual AbstractNode<U>* get_Node(int id)=0;
};

class TemplateTree{
public:
    std::vector<TemplateNode*> nodes;
    std::map<int,std::vector<int>> children_array;
    std::string template_string;
    std::vector<std::string> rewrite_sentence;
    std::string toString();

    void add_node(TemplateNode* node);
    void set_children_array();
    void set_rewrite_sentence();
    std::map<int,std::vector<int>> get_children_array();
    TemplateNode* get_Node(int id);
    TemplateNode* get_Root();
    std::vector<int> get_children(int id);

    bool operator <(TemplateTree other)const{
        if(this->nodes.size()!=other.nodes.size()){
            return this->nodes.size()<other.nodes.size();
        }
        else{
            return this->template_string<other.template_string;
        }
    }

};

class ZparTree:public AbstractTree<int>{
public:


    std::vector<ZparNode*> nodes;
    std::map<int,std::vector<int>> children_array;
    int lcaMatrix[200][200];


    void add_node(ZparNode* node);
    void set_children_array();
    void set_lcaMatrix();
    ~ZparTree(){
        for(auto node:nodes){
            delete node;
        }
    }


    std::vector<int> path_to_ancestor(int current,int ancestor);
    int get_lca_id(std::vector<int>,std::vector<int>);

    virtual std::map<int,std::vector<int>> get_children_array();
    virtual std::vector<AbstractNode<int>*> findEndpoints();
    virtual std::vector<AbstractNode<int>*> findVVpoints();
    virtual AbstractNode<int>* getLeastCommonAncestorOf(AbstractNode<int> *begin,AbstractNode<int> *end);
    virtual AbstractNode<int>* get_Node(int id);

};


#endif //DIRT_ABSTRACTNODE_H
