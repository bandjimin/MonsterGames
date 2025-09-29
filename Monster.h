#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <iostream>

class Monster{
    public:
        Monster(std::string name, int s);
        Monster();
        ~Monster();
        /** Code written by ChatGPT below this line*/
        friend bool operator<(const Monster& lhs, const Monster& rhs);
        /** Code written by ChatGPT above this line*/
        std::string getName();
        int getSPL();
        std::string m_name;
        int m_spl;
};

#endif