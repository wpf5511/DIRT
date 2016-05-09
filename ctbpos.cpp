//
// Created by 王鹏飞 on 16/5/3.
//

#include "ctbpos.h"


std::map<std::string,burstpos> ctbpos::ctb_to_burst={
        {"VA",burstpos::VERB},
        {"VC",burstpos::VERB},
        {"VE",burstpos::VERB},
        {"VV",burstpos::VERB},
        {"NR",burstpos::NOUN},
        {"NT",burstpos::NOUN},
        {"NN",burstpos::NOUN},
        {"LC",burstpos::LOCALIZER},
        {"PN",burstpos::PRONOUN},
        {"DT",burstpos::DET_NUM},
        {"CD",burstpos::DET_NUM},
        {"OD",burstpos::DET_NUM},
        {"M",burstpos::MEASURE},
        {"AD",burstpos::ADVERB},
        {"P",burstpos::PREPOSITION},
        {"CC",burstpos::CONJUNCTION},
        {"CS",burstpos::CONJUNCTION},
        {"DEC",burstpos::PARTICLE},
        {"DEG",burstpos::PARTICLE},
        {"DER",burstpos::PARTICLE},
        {"DEV",burstpos::PARTICLE},
        {"AS",burstpos::PARTICLE},
        {"SP",burstpos::PARTICLE},
        {"ETC",burstpos::PARTICLE},
        {"MSP",burstpos::PARTICLE},
        {"IJ",burstpos::OTHER},
        {"ON",burstpos::OTHER},
        {"LB",burstpos::OTHER},
        {"SB",burstpos::OTHER},
        {"BA",burstpos::OTHER},
        {"JJ",burstpos::OTHER},
        {"FW",burstpos::OTHER},
        {"PU",burstpos::OTHER}

};