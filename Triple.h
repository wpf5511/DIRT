//
// Created by 王鹏飞 on 16/5/5.
//

#ifndef DIRT_TRIPLE_H
#define DIRT_TRIPLE_H

#include <string>
#include <vector>
#include <set>
struct Word{

    std::string lexeme;
    std::string pos;
    Word(){}
    Word(std::string,std::string);
    bool operator <(Word other)const{
        if(lexeme!=other.lexeme)return lexeme<other.lexeme;
        else return pos<other.pos;
    }

    bool operator ==(Word other)const {
        return (lexeme==other.lexeme)&&(pos==other.pos);
    }

    bool operator !=(Word other)const{
        return (lexeme!=other.lexeme)||(pos!=other.pos);
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
    std::vector<std::string> rewrite_sentence;
    Slot slot;
//functions
    std::set<Word> getSlot(std::string path);//get another slot

    Triple(Word w,std::string template_path,std::vector<std::string> rewrite_sentence,Slot slot);

    Triple(std::string template_path,Slot slot);

    Triple(Word word, std::string template_path,Slot slot);

    bool operator <(Triple other)const {
        if(w!=other.w){
            return this->w<other.w;
        }else if(template_path!=other.template_path){
            return this->template_path<other.template_path;
        } else{
            return this->slot<other.slot;
        }
    }
};

class Real_Triple{

public:
    Word X;
    std::string template_path;
    Word Y;
    //functions

    Real_Triple(Word wordx,std::string temp_path,Word wordy);

    bool operator <(Real_Triple other)const{
        if(X!=other.X){
            return this->X<other.X;
        }
        else if(template_path!=other.template_path){
            return template_path<other.template_path;
        }
        else{
            return this->Y<other.Y;
        }
    }
};


#endif //DIRT_TRIPLE_H
