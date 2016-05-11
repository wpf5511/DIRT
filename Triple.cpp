//
// Created by 王鹏飞 on 16/5/5.
//

#include "Triple.h"



Word::Word(std::string lexeme, std::string pos) {
    this->lexeme = lexeme;
    this->pos = pos;
}

Triple::Triple(Word w, std::string template_path, Slot slot) {
    this->w = w;
    this->template_path = template_path;
    this->slot = slot;
}