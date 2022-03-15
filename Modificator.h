#pragma once

#include <string>


class Modificator {
public:
    enum Type {
        DAMAGE_BUFF,
        PROTECTION_BUFF,
        SPEED_BUFF
    };

    Modificator(std::string& name, Type type, double value);

    inline std::string GetName() const {return m_name;};

private:
    std::string m_name;
    Type m_type;
    double m_value;
};
















