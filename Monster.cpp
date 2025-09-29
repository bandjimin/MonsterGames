#include "Monster.h"

Monster::Monster(std::string name, int spl){
    m_name = name;
    m_spl = spl;
}

Monster::Monster(){
    
}

Monster::~Monster(){
    
}

std::string Monster::getName(){
    return m_name;
}

int Monster::getSPL(){
    return m_spl;
}

bool operator<(const Monster& lhs, const Monster& rhs){
    if (lhs.m_spl < rhs.m_spl){
        return true;
    } else{
        // assumes Monsters in a tournament do not have the same SPL
        // favors the left hand side
        return false;
    }
}
