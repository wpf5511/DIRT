//
// Created by 王鹏飞 on 16/5/5.
//

#include "Triple.h"



Word::Word(std::string lexeme, std::string pos) {
    this->lexeme = lexeme;
    this->pos = pos;
}

Triple::Triple(Word word, std::string template_path,std::vector<std::string>rewrite_sentence,Slot slot):w(word) {
    this->template_path = template_path;
    this->rewrite_sentence = rewrite_sentence;
    this->slot = slot;
}

Triple::Triple(std::string template_path,Slot slot) {
    this->template_path = template_path;
    this->slot = slot;
}

Triple::Triple(Word word, std::string template_path,Slot slot):w(word){
    this->template_path = template_path;
    this->slot = slot;
}

Real_Triple::Real_Triple(Word wordx, std::string temp_path, Word wordy):X(wordx),Y(wordy){
    this->template_path = temp_path;
}