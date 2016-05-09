//
// Created by 王鹏飞 on 16/5/3.
//

#ifndef DIRT_CTBPOS_H
#define DIRT_CTBPOS_H

#include <map>
#include <string>
enum burstpos{
    NOUN,//n
    VERB,//v
    LOCALIZER,
    PRONOUN,//n
    DET_NUM,//d
    MEASURE,//o
    ADVERB,//a
    PREPOSITION,//p
    CONJUNCTION,//p
    PARTICLE,//o
    OTHER//o
};

class ctbpos {
public:
    static std::map<std::string,burstpos> ctb_to_burst;
};



#endif //DIRT_CTBPOS_H
