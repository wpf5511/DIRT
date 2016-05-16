//
// Created by 王鹏飞 on 16/5/5.
//

#ifndef DIRT_TRIPLE_H
#define DIRT_TRIPLE_H

#include <string>
#include <vector>

struct Word{

    std::string lexeme;
    std::string pos;
    Word(){}
    Word(std::string,std::string);
    bool operator <(Word other)const{
        if(lexeme!=other.lexeme)return lexeme<other.lexeme;
        else return pos<other.pos;
    }

    bool operator !=(Word other)const {
        return (lexeme==other.lexeme)&&(pos==other.pos);
    }
};
enum Slot{
    SlotX,
    SlotY
};
class Triple {

public:
    Word w;
    std::string template_path;
    Slot slot;
//functions
    std::vector<Word> getSlot(std::string path);//get another slot
    Triple(Word w,std::string template_path,Slot slot);
};


#endif //DIRT_TRIPLE_H
