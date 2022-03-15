#include "RangeItem.h"


RangeItem::RangeItem(std::string& name, int level, Item::Rarity rarity, double damage, double speed)
    : Item(name, RANGE, level, rarity), m_damage(damage), m_speed(speed) { };


void RangeItem::AddModificator(std::string& name, Modificator::Type type, double value) {
    //m_modificators.push_back(new Modificator(name, type, value));
    if (type == Modificator::DAMAGE_BUFF) {
        m_damage += value;
        m_modificators.push_back(std::make_shared<Modificator>(name, type, value));
    } else if(type == Modificator::SPEED_BUFF) {
        m_speed += value;
        m_modificators.push_back(std::make_shared<Modificator>(name, type, value));
    }
}



























