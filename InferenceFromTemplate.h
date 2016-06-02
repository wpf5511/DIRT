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

    static void init(std::map<Real_Triple,int>r_triples);

    //function

    static std::vector<Word_Pair> getpair_frompath(std::string path_str);

    static std::vector<Real_Triple*> getrtriples_fromwordx(Word wordx);

    static std::vector<Real_Triple*> getrtriples_fromwordy(Word wordy);
};


#endif //DIRT_INFERENCEFROMTEMPLATE_H
