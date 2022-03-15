#pragma once

#include "Modificator.h"

#include <string>
#include <vector>
#include <iostream>
#include <memory>

class Item {
public:
    enum Type {
        MELEE,
        RANGE,
        ARMOUR
    };
    enum Rarity {
        COMMON,
        RARE,
        EPIC
    };

    Item(std::string& name, Type type, int level, Rarity rarity);

    inline std::string GetName() const { return m_name; }
    inline Type GetType() const { return m_type; }
    inline Rarity GetRarity() const { return m_rarity; }
    inline int GetLevel() const { return m_level; }

    inline std::vector<std::shared_ptr<Modificator>> GetModificators() const { return m_modificators; }

    // pair <double, optional>
    virtual std::pair<double, double> GetValue() const = 0;
    virtual void AddModificator(std::string& name, Modificator::Type type, double value) = 0;


protected:
    //std::vector<Modificator*> m_modificators;
    std::vector<std::shared_ptr<Modificator>> m_modificators;
private:
    std::string m_name;
    Type m_type;
    int m_level;
    Rarity m_rarity;

};

std::ostream& operator<< (std::ostream& os, Item::Type type);

std::ostream& operator<< (std::ostream& os, Item::Rarity rarity);






