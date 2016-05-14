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
            if(end!=begin&&end->get_parent()!=begin->get_Id()&&begin->get_parent()!=end->get_Id()){
                AbstractNode<T>* common = tree->getLeastCommonAncestorOf(begin,end);//不进行路径过滤先

                TemplateTree *templateTree = new TemplateTree();

                //add subtree node left
                std::string up = halfPathToString(begin,common, true,templateTree);

                //sub tree root
                TemplateNode *rootNode = new TemplateNode(common);
                rootNode->parent_id=-1;
                templateTree->add_node(rootNode);

                //add subtree node right
                std::string down = halfPathToString(end,common, false,templateTree);

                //change last right node parent id
                TemplateNode *last = templateTree->nodes.back();
                last->parent_id=rootNode->id;

                //the sub_tree
                templateTree->set_children_array();


                std::string path = up.append("<").append(common->get_lexeme())
                .append(">").append(down);

                //push to the templateTrees
                templateTree->template_string = path;
                auto insert_res = templateTrees.insert({templateTree,i});
                if(insert_res.second){
                    id_to_Tree.insert({i++,templateTree});
                }


                //Inset triple
                Triple *triple_b = new Triple(Word(begin->get_lexeme(),begin->get_pos()),path,Slot::SlotX);

                Triple *triple_e = new Triple(Word(end->get_lexeme(),end->get_pos()),path,Slot::SlotY);

                tri_count[triple_b]+=1;
                tri_count[triple_e]+=1;
            }
        }
    }
}

template <typename T>
std::string TemplatesFromTree<T>::halfPathToString(AbstractNode<T> *begin, AbstractNode<T> *common, bool direction,TemplateTree* templateTree) {
    std::stack<std::string> path;
    if(begin!=common){

        std::string depinfo = dependencyInfo(begin,direction);
        path.push(depinfo);//省略push开头词

        TemplateNode *templateNode = new TemplateNode(begin);
        templateNode->dependency=depinfo;
        templateNode->parent_id=templateTree->nodes.size()+1;
        //direction up slotx
        if(direction){
            templateNode->setSlot(Slot::SlotX);
            templateTree->add_node(templateNode);
        }
        else{
            templateNode->setSlot(Slot::SlotY);
            templateTree->add_node(templateNode);
        }
        auto current = tree->get_Node(begin->get_parent());
        while(current!=common){
            //add to string
            path.push(current->get_lexeme());
            std::string depinfo = dependencyInfo(current,direction);
            path.push(depinfo);

            //add node to template tree
            TemplateNode *templateNode = new TemplateNode(current);
            templateNode->dependency=depinfo;
            templateNode->parent_id=templateTree->nodes.size()+1;
            templateTree->add_node(templateNode);

            current = tree->get_Node(current->get_parent());
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
    if(path.empty()){
        sb.append(path.top());
        path.pop();
    }
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
    std::string parent_pos_info = posOfInfo(tree->get_Node(node->get_parent())->get_pos());
    if(direction){
        return node_pos_info.append(":").append(parent_pos_info);
    }
    else{
        return parent_pos_info.append(":").append(node_pos_info);
    }
}
template <typename T>

void TemplatesFromTree<T>::save(std::map<int, TemplateTree *> id_to_tree, std::string filename) {

    std::ofstream output(filename,std::ios::out);

    for(auto it=id_to_tree.begin();it!=id_to_tree.end();it++){
        output<<it->first<<std::endl;
        output<<it->second->toString();
    }
}


template  class  TemplatesFromTree<int>;