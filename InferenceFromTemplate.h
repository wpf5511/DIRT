//
// Created by hadoop4 on 16-5-31.
//

#ifndef DIRT_INFERENCEFROMTEMPLATE_H
#define DIRT_INFERENCEFROMTEMPLATE_H

#include <map>
#include <vector>
#include "Triple.h"
#include "TemplatesFromTree.h"

class InferenceFromTemplate {
public:
    static std::map<std::string,std::vector<Real_Triple*>>path_to_rtriple;

    static std::map<Word,std::vector<Real_Triple*>> wordx_to_rtriple;

    static std::map<Word,std::vector<Real_Triple*>> wordy_to_rtriple;

    static std::map<Word_Pair,std::vector<Real_Triple*>> wpair_to_rtriple;

    static void init(std::map<Real_Triple,int>r_triples);

    //function

    static std::vector<Word_Pair> getpair_frompath(std::string path_str);

    static std::vector<Real_Triple*> getrtriples_fromwordx(Word wordx);

    static std::vector<Real_Triple*> getrtriples_fromwordy(Word wordy);

    static std::vector< std::tuple< Real_Triple*,Real_Triple* > > get_triples_pair(std::string path_str,std::map<Real_Triple,int>r_triples);

    static std::vector< std::tuple< Real_Triple*,Real_Triple* > > get_highscore_triples_pair(
            std::vector< std::tuple< Real_Triple*,Real_Triple* > > triples_pair,int counts,std::map<Real_Triple, int>r_triples
    )

    static std::vector<double > compute_triples_pair_score(
            std::vector< std::tuple<Real_Triple*,Real_Triple* > >,
            std::map<Real_Triple,int>);
};


#endif //DIRT_INFERENCEFROMTEMPLATE_H
