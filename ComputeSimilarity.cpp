//
// Created by hadoop4 on 16-5-21.
//

#include "ComputeSimilarity.h"
#include <algorithm>
#include <cmath>


std::map<Slot,int> ComputeSimilarity::slot_counts;

std::map<words_tuple,std::set<Word>> ComputeSimilarity::words_map;

std::map<words_tuple,int> ComputeSimilarity::words_count;

std::map<paths_tuple,int> ComputeSimilarity::paths_count;




int ComputeSimilarity::get_Triple_count(std::map<Triple, int> triples, Triple obj) {

    auto iter=triples.find(obj);
    if(iter!=triples.end()){
        return iter->second;
    }
}

int ComputeSimilarity::get_Slot_count( Slot slot) {


    auto iter = slot_counts.find(slot);
    if(iter!=slot_counts.end()){
        return iter->second;
    }
    else{
        printf("slot_count_error\n");
        exit(1);
    }

}

std::set<Word> ComputeSimilarity::get_words(std::string path, Slot slot) {


    auto iter = words_map.find(std::make_tuple(path,slot));

    if(iter!=words_map.end()){
        return iter->second;
    }
    else{
        printf("words_error,words:%s\n",path.c_str());
        exit(1);
    }
}

int ComputeSimilarity::get_words_count( std::string path, Slot slot) {

    auto iter = words_count.find(std::make_tuple(path,slot));

    if(iter!=words_count.end()){
        return iter->second;
    }
    else{
        printf("words_count_error\n");
        exit(1);
    }
}

int ComputeSimilarity::get_path_count( Slot slot, Word word) {

    auto iter = paths_count.find(std::make_tuple(slot,word));
    if(iter!=paths_count.end()){
        return iter->second;
    }
    else{
        printf("path_count_error\n");
        exit(1);
    }

}

double ComputeSimilarity::get_mutual_information(std::map<Triple,int>triples,std::string path,Slot slot,Word word) {
    double mi;

    Triple obj(word,path,slot);

    int count1 = get_Triple_count(triples,obj);

    int count2 = get_Slot_count(slot);

    int count3 = get_words_count(path,slot);

    int count4 = get_path_count(slot,word);

    mi=log2(double(count1*count2)/(count3*count4));

    return mi;

}

//t1 and t2 slot must be the same
double ComputeSimilarity::sim_between_slots(std::map<Triple, int> triples, Triple t1, Triple t2) {

    std::set<Word>t1_words=get_words(t1.template_path,t1.slot);

    std::set<Word>t2_words=get_words(t2.template_path,t2.slot);

    std::set<Word> common;


    std::set_intersection(t1_words.begin(),t1_words.end(),t2_words.begin(),t2_words.end(),std::inserter(common,common.begin()));

    //printf("common:words size:%d\n",common.size());

    double  numerator=0;
    for(auto it=common.begin();it!=common.end();it++){
        numerator=numerator+get_mutual_information(triples,t1.template_path,t1.slot,*it)
                  +get_mutual_information( triples,t2.template_path,t2.slot,*it);
    }

    double denominator;

    for(auto it=t1_words.begin();it!=t1_words.end();it++){
        denominator+=get_mutual_information(triples,t1.template_path,t1.slot,*it);
    }

    for(auto it=t2_words.begin();it!=t2_words.end();it++){
        denominator+=get_mutual_information(triples,t2.template_path,t2.slot,*it);
    }

    double sim=numerator/denominator;
    return sim;
}

double ComputeSimilarity::sim_between_path(std::map<Triple, int> triples,Triple t1, Triple t2) {

    t1.slot=SlotX;
    t2.slot=SlotX;
    Triple t1_a_s(t1.w,t1.template_path,SlotY);
    Triple t2_a_s(t2.w,t2.template_path,SlotY);

    double sim1 = sim_between_slots(triples,t1,t2);

    double sim2 = sim_between_slots(triples,t1_a_s,t2_a_s);


    double sim_path = sqrt(sim1*sim2);

    //printf("excuted path2:%s,simlarity:%lf\n",t2.template_path.c_str(),sim_path);
    return sim_path;
}

void ComputeSimilarity::init(std::map<Triple, int> triples) {

    for(auto it=triples.begin();it!=triples.end();it++){

        std::string path = it->first.template_path;
        Slot  slot = it->first.slot;
        Word word = it->first.w;

        slot_counts[slot]++;

        words_map[std::make_tuple(path,slot)].insert(word);

        words_count[std::make_tuple(path,slot)]+=it->second;

        paths_count[std::make_tuple(slot,word)]+=it->second;

    }
}

std::set<Triple> ComputeSimilarity::get_candidate_triple(std::map<Triple, int> triples, Triple t1) {

    std::set<Triple> resTriple;
    for(auto it=triples.begin();it!=triples.end();it++){

        std::set<Word>t1_words_x=get_words(t1.template_path,SlotX);

        std::set<Word>t2_words_x=get_words(it->first.template_path,SlotX);

        std::set<Word> common_x;

        std::set_intersection(t1_words_x.begin(),t1_words_x.end(),t2_words_x.begin(),t2_words_x.end(),std::inserter(common_x,common_x.begin()));


        std::set<Word>t1_words_y=get_words(t1.template_path,SlotY);

        std::set<Word>t2_words_y=get_words(it->first.template_path,SlotY);

        std::set<Word> common_y;

        std::set_intersection(t1_words_y.begin(),t1_words_y.end(),t2_words_y.begin(),t2_words_y.end(),std::inserter(common_y,common_y.begin()));

        if(!common_x.empty()&&!common_y.empty()){
            resTriple.insert(it->first);
        }

    }
    return  resTriple;


}