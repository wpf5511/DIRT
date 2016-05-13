#include <iostream>
#include <sstream>
#include "TemplatesFromTree.h"
using namespace std;

int i=0;
std::map<Triple*,int,TripleComp> tri_count;

std::map<TemplateTree*,int,TreeComp> templateTrees;

std::map<int,TemplateTree*> id_to_Tree;

Tri_Pair tri_pair;

int main() {

    TemplatesFromTree<int> templatesFromTree;

    ifstream Zparfile("/Users/wangpf/Downloads/reference-4.txt");

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
            istringstream is(line);

            is>>lexeme>>pos>>parent_id>>dependency;

            zparTree->add_node(new ZparNode(lexeme,pos,stoi(parent_id),dependency));
        }
    }


    cout << "Hello, World!" << endl;
    return 0;
}