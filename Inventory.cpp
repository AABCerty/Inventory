#include "Inventory.h"

#include "MeleeItem.h"
#include "RangeItem.h"
#include "ArmourItem.h"
#include "Modificator.h"
// STL
#include <iostream>
#include <iomanip>

const int MAX_ITEMS = 200;

Inventory::Inventory() : m_maxItems(MAX_ITEMS), m_numItems(0) {
    m_Items.reserve(m_maxItems);
}

void Inventory::AddItem(Item::Type type, std::string& name, int level, Item::Rarity rarity, double firstValue, double secondValue) {
    switch (type) {
    case Item::MELEE :
        //m_Items.push_back(new MeleeItem(name, level, rarity, firstValue, secondValue));
        m_Items.push_back(std::make_shared<MeleeItem>(name, level, rarity, firstValue, secondValue));
        break;
    case Item::RANGE :
       // m_Items.push_back(new RangeItem(name, level, rarity, firstValue, secondValue));
        m_Items.push_back(std::make_shared<RangeItem>(name, level, rarity, firstValue, secondValue));
        break;
    case Item::ARMOUR:
        //m_Items.push_back(new ArmourItem(name, level, rarity, firstValue));
        m_Items.push_back(std::make_shared<ArmourItem>(name, level, rarity, firstValue));
        break;
    }
}

void Inventory::PrintItems() const {
    std::cout << "Print Items" << std::endl;
    for (const auto& item : m_Items) {
        std::cout << std::left << std::setw(20) << item->GetName() << "\t" << item->GetType() << "\t" << std::setw(4)<< item->GetLevel() << item->GetRarity() << "\t";
        auto value = item->GetValue();
        if (value.second == 0) {
            std::cout << value.first << "\t\t";
        } else {
            std::cout << value.first << "\t" << value.second << "\t";
        }
        for (const auto& mod : item->GetModificators()) {
            std::cout << " " << mod->GetName();
        }
        std::cout << std::endl;
    }
    std::cout << "------------------------------------------------------------" << std::endl;
}




















