#include <iostream>
#include <sstream>
#include "TemplatesFromTree.h"
using namespace std;

int i=0;
std::map<Triple,int> tri_count;

std::map<TemplateTree,int> templateTrees;

std::map<int,TemplateTree> id_to_Tree;

std::map<Word_Pair,std::map<int,int>> template_matrix;

int main() {

    TemplatesFromTree<int> templatesFromTree;

    ifstream Zparfile("/home/hadoop4/reference-4.txt",ios::in);

    ZparTree *zparTree = new ZparTree();

    std::string line;
    std::string lexeme,pos,parent_id,dependency;
    while(getline(Zparfile,line)){
        if(line.empty()){
            zparTree->set_children_array();
            zparTree->set_lcaMatrix();
            templatesFromTree.tree=zparTree;
            templatesFromTree.CreateTemplates();
            delete zparTree;
            zparTree = new ZparTree();
        }
        else{
           // cout<<line<<endl;
            istringstream is(line);

            is>>lexeme>>pos>>parent_id>>dependency;

            //cout<<lexeme<<pos<<parent_id<<dependency<<endl;

            zparTree->add_node(new ZparNode(lexeme,pos,stoi(parent_id),dependency));
        }
    }

    TemplatesFromTree<int>::save(id_to_Tree,"/home/hadoop4/template_file3.txt");


    cout << "Hello, World!" << endl;
    return 0;
}