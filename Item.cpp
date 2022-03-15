#include "Item.h"

Item::Item(std::string& name, Type type, int level, Rarity rarity)
    : m_name(name), m_type(type), m_level(level), m_rarity(rarity) { };


std::ostream& operator<< (std::ostream& os, Item::Type type) {
    std::string str;
    if (type == Item::MELEE) {
        str = "Melee";
    } else if (type == Item::RANGE) {
        str = "Range";
    } else if (type == Item::ARMOUR) {
        str = "Armour";
    }
    return os << str;
}

std::ostream& operator<< (std::ostream& os, Item::Rarity rarity) {
    std::string str;
    if (rarity == Item::COMMON) {
        str = "Common";
    } else if (rarity == Item::RARE) {
        str = "Rare";
    } else if (rarity == Item::EPIC) {
        str = "Epic";
    }
    return os << str;
}

















