//
// Created by hadoop4 on 16-5-31.
//

#include <queue>
#include "InferenceFromTemplate.h"

std::map<std::string,std::vector<Real_Triple*>> InferenceFromTemplate::path_to_rtriple;

std::map<Word,std::vector<Real_Triple*>> InferenceFromTemplate::wordx_to_rtriple;

std::map<Word,std::vector<Real_Triple*>> InferenceFromTemplate::wordy_to_rtriple;

std::map<Word_Pair,std::vector<Real_Triple*>> InferenceFromTemplate::wpair_to_rtriple;


void InferenceFromTemplate::init(std::map<Real_Triple, int> r_triples) {
    for(auto it=r_triples.begin();it!=r_triples.end();it++){
        auto R_Triple = it->first;
        path_to_rtriple[R_Triple.template_path].push_back(&R_Triple);

        wordx_to_rtriple[R_Triple.X].push_back(&R_Triple);

        wordy_to_rtriple[R_Triple.Y].push_back(&R_Triple);

        Word_Pair wpair(R_Triple.X,R_Triple.Y);

        wpair_to_rtriple[wpair].push_back(&R_Triple);
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

std::vector< std::tuple< std::vector<Real_Triple*>,std::vector<Real_Triple*> > > InferenceFromTemplate::get_triples_pair(
        std::string path_str) {

    std::vector< std::tuple< std::vector<Real_Triple*>,std::vector<Real_Triple*> > > resvec_tup;

    std::vector<Word_Pair> res_pair=getpair_frompath(path_str);

    for(auto it=res_pair.begin();it!=res_pair.end();it++){
        Word t3_X=it->x;
        Word t3_Y=it->y;

        std::vector<Word> X1vec;
        auto t1_triples = getrtriples_fromwordy(t3_X);
        for(auto it1=t1_triples.begin();it1!=t1_triples.end();it1++){
            Word_Pair wp1((*it1)->X,t3_X);

            Word_Pair wp2((*it1)->X,t3_Y);

            std::vector<Real_Triple*>t1_restriples = wpair_to_rtriple[wp1];

            std::vector<Real_Triple*>t2_restriples = wpair_to_rtriple[wp2];

            resvec_tup.push_back(std::make_tuple(t1_restriples,t2_restriples));
        }
    }

}

std::vector< std::tuple< std::vector<Real_Triple*>,std::vector<Real_Triple*> > > InferenceFromTemplate::get_highscore_triples_pair(
        std::vector<std::tuple<std::vector<Real_Triple *>, std::vector<Real_Triple *> > > triples_pair, int counts) {
    auto all_triples_pair = triples_pair;

    decltype(all_triples_pair)  high_triples_pair;

    typedef  std::tuple<double,int> tuple_t;
    tuple_t score_index;

    std::priority_queue<tuple_t,std::vector<tuple_t>,std::greater<tuple_t>> score_queue;

    std::vector<int> sort_index(triples_pair.size());

}

std::vector<double > InferenceFromTemplate::compute_triples_pair_score(
        std::vector<std::tuple<std::vector<Real_Triple *>, std::vector<Real_Triple *> > >triples_pair,
        std::map<Real_Triple, int>r_triples) {
    int sum_count=0;
    for(auto it=r_triples.begin();it!=r_triples.end();it++){
        sum_count+=it->second;
    }
}

