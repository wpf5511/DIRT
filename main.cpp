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

template  <typename T>
ostream& operator<< (ostream& out,const vector<T>&vec){
    for(auto item:vec){
        out<<item<<" ";
    }
}



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


    priority_queue<double,vector<double>,greater<double>>sim_score;
    multimap<double,string> path_score;

    map<string,std::vector<std::string>> path_candidate;
    int sim_size=5;
    int i=0;

    ComputeSimilarity::init(triples);

    path_candidate = ComputeSimilarity::get_candidate_triple(triples,path1);
    cout<<path_candidate.size()<<endl;

    for(auto it=path_candidate.begin();it!=path_candidate.end();it++,i++){
      double score= ComputeSimilarity::sim_between_path(triples,path1,it->first);
        if(i<sim_size){
            sim_score.push(score);
            path_score.insert({score,it->first});
        }else if(score>sim_score.top()){
            auto erase_iter = path_score.equal_range(sim_score.top());
            if(erase_iter.first==path_score.end()){
                cout<<"must not happen";
            }
            path_score.erase(erase_iter.first);
            sim_score.pop();

            path_score.insert({score,it->first});
            sim_score.push(score);
        }
    }

    for(auto it=path_score.begin();it!=path_score.end();it++){
        cout<<it->first<<"   "<<it->second<<" "<<path_candidate[it->second]<<endl;
    }

    cout << "Hello, World!" << endl;
    return 0;
}
