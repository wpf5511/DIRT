//
// Created by hadoop4 on 16-5-21.
//

#ifndef DIRT_COMPUTESIMILARITY_H
#define DIRT_COMPUTESIMILARITY_H


#include "Triple.h"
#include <map>
#include <set>
#include <tuple>


typedef  std::tuple<std::string,Slot> words_tuple;

typedef  std::tuple<Slot,Word> paths_tuple;


class ComputeSimilarity {
public:
    static std::map<Slot,int> slot_counts;

    static std::map<words_tuple,std::set<Word>> words_map;

    static std::map<words_tuple,int> words_count;

    static std::map<paths_tuple,int> paths_count;


    static int get_Triple_count(std::map<Triple,int>triples,Triple obj);

    static int get_Slot_count(std::map<Triple,int>triples,Slot slot);

    static std::set<Word> get_words(std::map<Triple,int>triples,std::string path,Slot slot);

    static int get_words_count(std::map<Triple,int>triples,std::string path,Slot slot);

    static int get_path_count(std::map<Triple,int>triples,Slot slot,Word word);

    static double get_mutual_information(std::map<Triple,int>triples,std::string,Slot,Word);

    static double sim_between_slots(std::map<Triple,int>triples,Triple t1,Triple t2);

    static double sim_between_path(std::map<Triple,int>triples_x,std::map<Triple,int>triples_y,Triple t1,Triple t2);
};



#endif //DIRT_COMPUTESIMILARITY_H
