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

int ComputeSimilarity::get_Slot_count(std::map<Triple, int> triples, Slot slot) {

    int count=0;

    auto iter = slot_counts.find(slot);
    if(iter!=slot_counts.end()){
        return iter->second;
    }
    else{
        for(auto it=triples.begin();it!=triples.end();it++){
            if(it->first.slot==slot){
                count+=it->second;
            } else{
                continue;
            }
        }

        slot_counts.insert({slot,count});
    }
    return count;

}

std::set<Word> ComputeSimilarity::get_words(std::map<Triple, int> triples, std::string path, Slot slot) {

    std::set<Word> res;

    auto iter = words_map.find(std::make_tuple(path,slot));

    if(iter!=words_map.end()){
        return iter->second;
    }
    else{
        for(auto it=triples.begin();it!=triples.end();it++){
            if(it->first.template_path==path&&it->first.slot==slot){
                res.insert(it->first.w);
            } else{
                continue;
            }
        }
        words_map.insert({std::make_tuple(path,slot),res});
    }
    return res;
}

int ComputeSimilarity::get_words_count(std::map<Triple, int> triples, std::string path, Slot slot) {
    int count = 0;

    auto iter = words_count.find(std::make_tuple(path,slot));

    if(iter!=words_count.end()){
        return iter->second;
    }
    else{
        for(auto it=triples.begin();it!=triples.end();it++){
            if(it->first.template_path==path&&it->first.slot==slot){
                count+=it->second;
            } else{
                continue;
            }
        }
        words_count.insert({std::make_tuple(path,slot),count});
    }
    return count;
}

int ComputeSimilarity::get_path_count(std::map<Triple, int> triples, Slot slot, Word word) {
    int count=0;

    auto iter = paths_count.find(std::make_tuple(slot,word));
    if(iter!=paths_count.end()){
        return iter->second;
    }
    else{
        for(auto it=triples.begin();it!=triples.end();it++){
            if(it->first.slot==slot&&word==it->first.w){
                count+=it->second;
            } else{
                continue;
            }
        }

        paths_count.insert({std::make_tuple(slot,word),count});
    }
    return count;

}

double ComputeSimilarity::get_mutual_information(std::map<Triple,int>triples,std::string path,Slot slot,Word word) {
    double mi;

    Triple obj(word,path,slot);

    int count1 = get_Triple_count(triples,obj);

    int count2 = get_Slot_count(triples,slot);

    int count3 = get_words_count(triples,path,slot);

    int count4 = get_path_count(triples,slot,word);

    mi=log2(double(count1*count2)/(count3*count4));

    return mi;

}

//t1 and t2 slot must be the same
double ComputeSimilarity::sim_between_slots(std::map<Triple, int> triples, Triple t1, Triple t2) {

    std::set<Word>t1_words=get_words(triples,t1.template_path,t1.slot);

    std::set<Word>t2_words=get_words(triples,t2.template_path,t2.slot);

    std::set<Word> common;

    std::set_intersection(t1_words.begin(),t1_words.end(),t2_words.begin(),t2_words.end(),std::inserter(common,common.begin()));

    double  numerator;
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

double ComputeSimilarity::sim_between_path(std::map<Triple, int> triples_x,std::map<Triple,int> triples_y,Triple t1, Triple t2) {

    t1.slot=SlotX;
    t2.slot=SlotX;
    Triple t1_a_s(t1.w,t1.template_path,SlotY);
    Triple t2_a_s(t2.w,t2.template_path,SlotY);

    double sim1 = sim_between_slots(triples_x,t1,t2);

    double sim2 = sim_between_slots(triples_y,t1_a_s,t2_a_s);

    double sim_path = sqrt(sim1*sim2);

    return sim_path;
}
