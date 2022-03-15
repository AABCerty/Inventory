#pragma once

#include "Item.h"

// STL
#include <vector>
#include <iostream>
#include <memory>


class Inventory {
public:
    Inventory();

    void AddItem(Item::Type type, std::string& name, int level, Item::Rarity rarity, double firstValue, double secondValue = 0);

    void PrintItems() const;

    inline std::vector<std::shared_ptr<Item>> GetItems() const { return m_Items; }

private:
    unsigned int m_maxItems;
    unsigned int m_numItems;
    std::vector<std::shared_ptr<Item>> m_Items;
};
























