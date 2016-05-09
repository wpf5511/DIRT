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

};
enum Slot{
    SlotX,
    SlotY
};
class Triple {
private:
    Word w;
    std::string md5_path;
    Slot slot;
public:
    std::vector<Word> getSlot(std::string path);//get another slot
};


#endif //DIRT_TRIPLE_H
