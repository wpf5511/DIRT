#include <iostream>
#include <sstream>
#include <queue>
#include "TemplatesFromTree.h"
#include "ComputeSimilarity.h"

using namespace std;

int i=0;
std::map<Triple,int> tri_count_x;
std::map<Triple,int> tri_count_y;

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

    //TemplatesFromTree<int>::save_template(id_to_Tree,"/home/hadoop4/template_file001.txt");

    //TemplatesFromTree<int>::save_path(id_to_Tree,"/home/hadoop4/path_file001.txt");

    std::string path1="n:OBJ:v<作出>v:SBJ:n>贡献>n:NMOD:n";
    std::vector<string> similar_path;

    Triple t_center(path1);
    priority_queue<double,vector<double>,greater<double>>sim_score;
    map<double,Triple> tri_score;

    int sim_size=10;
    int i=0;
    for(auto it=tri_count_x.begin();it!=tri_count_x.end();it++,i++){
      double score= ComputeSimilarity::sim_between_path(tri_count_x,tri_count_y,t_center,it->first);
        if(i<sim_size){
            sim_score.push(score);
            tri_score.insert({score,it->first});
        }else if(score>sim_score.top()){
            auto erase_iter = tri_score.find(sim_score.top());
            if(erase_iter==tri_score.end()){
                cout<<"must not happen";
            }
            tri_score.erase(erase_iter);
            sim_score.pop();
        }
    }

    for(auto it=tri_score.begin();it!=tri_score.end();it++){
        cout<<it->first<<"   "<<it->second.template_path<<endl;
    }

    cout << "Hello, World!" << endl;
    return 0;
}
