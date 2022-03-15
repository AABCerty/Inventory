#include "Inventory.h"


#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>

struct Parse {
    std::string name;
    Item::Type type;
    int level;
    Item::Rarity rarity;
    double damage;
    double speed;
    double protection;
};

void ParseItems(Inventory& inventory, std::istream& is);
void ParseModificators(Inventory& inventory, std::istream& is);
void ParseAfterType(std::istream& is, Parse& parse);

Item::Type StringToType(std::string& str);
Item::Rarity StringToRarity(std::string& str);
Modificator::Type StringToBuff(std::string& str);
void FilterByLevel(const std::vector<std::pair<std::string, int>>& filterLvl, std::vector<std::shared_ptr<Item>>& resultItems);
void FilterByTypes(const std::vector<Item::Type>& filterTypes, std::vector<std::shared_ptr<Item>>& resultItems);
void FilterByRarities(const std::vector<Item::Rarity>& filterRarities, std::vector<std::shared_ptr<Item>>& resultItems);


int main()
{
    std::string str ("{ident: \"axe_01\", type: Melee, level: 3, rarity: Common, damage: 12.0, speed: 0.9 }");
    str += ",\n{ident: \"revolver_01\", type: Range, level: 5, rarity: Common, damage: 42.0, speed: 2.0 }";
    str += ",\n{ident: \"revolver_02\", type: Range, level: 3, rarity: Rare, damage: 50.0, speed: 2.1 }";
    str += ",\n{ident: \"machinegun_01\", type: Range, level: 5, rarity: Epic, damage: 83.1, speed: 10.0 }";
    str += ",\n{ident: \"jacket_01\", type: Armour, level: 2, rarity: Common, protection: 2.0 }";
    str += ",\n{ident: \"bulletprof_vest_01\", type: Armour, level: 5, rarity: Rare, protection: 30.0 }";
    std::istringstream stream(str);
    Inventory inventory;
    ParseItems(inventory, stream);
    inventory.PrintItems();

    /******************************************************/
    std::string modStr ("{ ident: \"eagle_eye\", filters: [{\"level\", \">=\", 4}, {\"type\", Range}], type: DamageBuff, value: 10");
    modStr += ",\n{ ident: \"donatium_steel\", filters: [{\"rarity\", Rare}], type: ProtectionBuff, value: 15";
    modStr += ",\n{ ident: \"rage_drink\", filters: [{\"type\", Range}, {\"type\", Melee}], type: SpeedBuff, value: 0.4";

    std::stringstream modStream(modStr);

    ParseModificators(inventory, modStream);
    inventory.PrintItems();

    return 0;
}


void ParseItems(Inventory& inventory, std::istream& is) {
    char ch;
    std::string str;
    Parse parse;
    do {
        is >> str; // ident
        if (str != "{ident:") {
            std::cerr << "Error! " << "{ident: != " << str << std::endl;
            return;
        }
        is >> str; // name
        parse.name = str.substr(1, str.size() - 3);
        is >> str; // type
        if (str != "type:") {
            std::cerr << "Error! " << "type: != " << str << std::endl;
            return;
        }
        is >> str; // type
        parse.type = StringToType(str);

        ParseAfterType(is, parse);
        // Parse end
        // Add Item
        if (parse.type == Item::MELEE || parse.type == Item::RANGE) {
            inventory.AddItem(parse.type, parse.name, parse.level, parse.rarity, parse.damage, parse.speed);
        } else if (parse.type == Item::ARMOUR) {
            inventory.AddItem(parse.type, parse.name, parse.level, parse.rarity, parse.protection);
        }

        is >> ch;
    } while (is >> ch);
}

void ParseModificators(Inventory& inventory, std::istream& is) {
    char ch;
    std::string str;
    std::string name;

    do {
        Modificator::Type modType;
        double value;
        is >> ch;
        if (ch != '{') {
            std:: cout << "Mod Error! { != " << ch << std::endl;
            return;
        }
        is >> str; // ident
        if (str != "ident:") {
            std:: cout << "Mod Error! {ident != " << str << std::endl;
            return;
        }
        is >> str; // name
        name = str.substr(1, str.size() - 3);
        /************************************/
        // Parse Filter
        is >> str >> ch; // filters: [
        // vector?
        std::vector<std::string> vec_filters;
        std::vector<Item::Type> filterTypes;
        std::vector<Item::Rarity> filterRarities;
        std::vector<std::pair<std::string, int>> filterLevels;
        do {
            is >> str;
            if (str == "{\"level\",") {
                int level;
                is >> str >> level;
                filterLevels.push_back({str.substr(1, str.size() - 3), level});
            } else if (str == "{\"type\",") {
                is >> str;
                filterTypes.push_back(StringToType(str));
            } else if (str == "{\"rarity\",") {
                is >> str;
                filterRarities.push_back(StringToRarity(str));
            }
        } while (str[str.size()-2] != ']');
        is >> ch; // ]
        /******************************************/
        // Parse type && value
        std::string typeStr;
        is >> str >> typeStr >> str >> value;
        modType = StringToBuff(typeStr);
        /*******************************/
        // Filter
        // bool first;  resultItems - empty; list
        std::vector<std::shared_ptr<Item>> resultItems = inventory.GetItems();
        if (filterLevels.size() > 0) {
            FilterByLevel(filterLevels, resultItems);
        }
        if (filterTypes.size() > 0) {
            FilterByTypes(filterTypes, resultItems);
        }
        if (filterRarities.size() > 0) {
            FilterByRarities(filterRarities, resultItems);
        }
        /*********************************************/
        // Add Modifcators
        for (const auto& item : resultItems) {
            item.get()->AddModificator(name, modType, value);
        }
    } while (is >> ch);
}

void ParseAfterType(std::istream& is, Parse& parse) {
    std::string str;
    char ch;
    is >> str >> parse.level; // level
    is >> ch >> str >> str; // rarity
    parse.rarity = StringToRarity(str);
    if (parse.type == Item::MELEE || parse.type == Item::RANGE) {
        is >> str >> parse.damage; // damage
        is >> ch >> str >> parse.speed; // speed
    } else if (parse.type == Item::ARMOUR) {
        is >> str >> parse.protection; // sprotection
    }
}


Item::Type StringToType(std::string& str) {
    if (str.find("Melee") == 0) {
        return Item::MELEE;
    } else if (str.find("Range") == 0) {
        return Item::RANGE;
    } else if (str.find("Armour") == 0) {
        return Item::ARMOUR;
    }
}

Item::Rarity StringToRarity(std::string& str) {
    if (str.find("Common") == 0) {
        return Item::COMMON;
    } else if (str.find("Rare") == 0) {
        return Item::RARE;
    } else if (str.find("Epic") == 0) {
        return Item::EPIC;
    }
}

Modificator::Type StringToBuff(std::string& str) {
    if (str.find("DamageBuff") == 0) {
        return Modificator::DAMAGE_BUFF;
    } else if (str.find("ProtectionBuff") == 0) {
        return Modificator::PROTECTION_BUFF;
    } else if (str.find("SpeedBuff") == 0){
        return Modificator::SPEED_BUFF;
    }
}

void FilterByLevel(const std::vector<std::pair<std::string, int>>& filterLvl, std::vector<std::shared_ptr<Item>>& resultItems) {
    auto end = std::remove_if(resultItems.begin(), resultItems.end(), [&filterLvl](const std::shared_ptr<Item> item){
                    bool result = true;
                    for (const auto& [operand, level] : filterLvl) {
                        if (operand == ">=") {
                            result = result && item->GetLevel() >= level;
                        } else if (operand == ">") {
                            result = result && item->GetLevel() > level;
                        } else if (operand == "<") {
                            result = result && item->GetLevel() < level;
                        } else if (operand == "<=") {
                            result = result && item->GetLevel() <= level;
                        } else if (operand == "=") {
                            result = result && item->GetLevel() == level;
                        }
                    }
                    return !result;});
    resultItems.erase(end, resultItems.end());
};

void FilterByTypes(const std::vector<Item::Type>& filterTypes, std::vector<std::shared_ptr<Item>>& resultItems) {
    auto end = std::remove_if(resultItems.begin(), resultItems.end(), [&filterTypes](const std::shared_ptr<Item> item){
                    if (filterTypes.size() == 1) {
                        return !(item->GetType() == filterTypes[0]);
                    } else {
                        return !(item->GetType() == filterTypes[0] || item->GetType() == filterTypes[1]);
                    } });
    resultItems.erase(end, resultItems.end());
}

void FilterByRarities(const std::vector<Item::Rarity>& filterRarities, std::vector<std::shared_ptr<Item>>& resultItems) {
    auto end = std::remove_if(resultItems.begin(), resultItems.end(), [&filterRarities](const std::shared_ptr<Item> item){
                    if (filterRarities.size() == 1) {
                        return !(item->GetRarity() == filterRarities[0]);
                    } else {
                        return !(item->GetRarity() == filterRarities[0] || item->GetRarity() == filterRarities[1]);
                    } });
    resultItems.erase(end, resultItems.end());
};












