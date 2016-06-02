//
// Created by hadoop4 on 16-5-31.
//

#include "InferenceFromTemplate.h"

std::map<std::string,std::vector<Real_Triple*>> InferenceFromTemplate::path_to_rtriple;

std::map<Word,std::vector<Real_Triple*>> InferenceFromTemplate::wordx_to_rtriple;

std::map<Word,std::vector<Real_Triple*>> InferenceFromTemplate::wordy_to_rtriple;


void InferenceFromTemplate::init(std::map<Real_Triple, int> r_triples) {
    for(auto it=r_triples.begin();it!=r_triples.end();it++){
        auto R_Triple = it->first;
        path_to_rtriple[R_Triple.template_path].push_back(&R_Triple);

        wordx_to_rtriple[R_Triple.X].push_back(&R_Triple);

        wordy_to_rtriple[R_Triple.Y].push_back(&R_Triple);
    }
}

std::vector<Word_Pair> InferenceFromTemplate::getpair_frompath(std::string path_str) {

    std::vector<Word_Pair> res_pair;
    auto iter=path_to_rtriple.find(path_str);

    if(iter!=path_to_rtriple.end()){
        auto vec_item = iter->second;

        for(auto it=vec_item.begin();it!=vec_item.end();it++){

            res_pair.push_back(Word_Pair((*it)->X,(*it)->Y));

        }
    }

    return res_pair;
}

std::vector<Real_Triple*> InferenceFromTemplate::getrtriples_fromwordx(Word wordx) {

    auto iter = wordx_to_rtriple.find(wordx);

    if(iter!=wordx_to_rtriple.end()){
        return iter->second;
    }
}

std::vector<Real_Triple*> InferenceFromTemplate::getrtriples_fromwordy(Word wordy) {
    auto iter = wordy_to_rtriple.find(wordy);

    if(iter!=wordy_to_rtriple.end()){
        return iter->second;
    }
}

