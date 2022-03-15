#include "ArmourItem.h"


ArmourItem::ArmourItem(std::string& name, int level, Item::Rarity rarity, double protection)
    : Item(name, ARMOUR, level, rarity), m_protection(protection) { };


void ArmourItem::AddModificator(std::string& name, Modificator::Type type, double value) {
    //m_modificators.push_back(new Modificator(name, type, value));
    if (type == Modificator::PROTECTION_BUFF) {
        m_modificators.push_back(std::make_shared<Modificator>(name, type, value));
        m_protection += value;
    }
}


















