#pragma once

#include "Item.h"

class ArmourItem : public Item {
public:
    ArmourItem(std::string& name, int level, Item::Rarity rarity, double protection);

    void AddModificator(std::string& name, Modificator::Type type, double value) override;

    inline std::pair<double, double> GetValue() const { return {m_protection, 0.0}; };

private:
    double m_protection;
};

