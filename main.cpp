#include <iostream>
#include <sstream>
#include <queue>
#include "TemplatesFromTree.h"
#include "ComputeSimilarity.h"

using namespace std;

int i=0;
std::map<Triple,int> triples;

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

    std::string path1="n:OBJ:v<作出>v:SBJ:n>发展>n:NMOD:n";

    Triple t_center(path1);
    priority_queue<double,vector<double>,greater<double>>sim_score;
    map<double,Triple> tri_score;

    set<Triple> tri_candidate;
    int sim_size=10;
    int i=0;

    ComputeSimilarity::init(triples);
    tri_candidate = ComputeSimilarity::get_candidate_triple(triples,t_center);
    cout<<tri_candidate.size()<<endl;

    for(auto it=tri_candidate.begin();it!=tri_candidate.end();it++,i++){
      double score= ComputeSimilarity::sim_between_path(triples,t_center,*it);
        if(i<sim_size){
            sim_score.push(score);
            tri_score.insert({score,*it});
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
