#pragma once

#include "Item.h"

#include <string>

class RangeItem : public Item {
public:
    RangeItem(std::string& name, int level, Item::Rarity rarity, double damage, double speed);

    void AddModificator(std::string& name, Modificator::Type type, double value) override;

    inline std::pair<double, double> GetValue() const { return {m_damage, m_speed}; };

private:
    double m_damage;
    double m_speed;
};




