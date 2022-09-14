#pragma once
#include <iostream>
#include "Utils.cpp"
#include "Offsets.cpp"

class Level
{
public:
    long getBasePointer()
    {
        long basePointer = offsets::REGION + offsets::LEVEL;
        return basePointer;
    }
    std::string getName()
    {
        long basePointer = getBasePointer();
        std::string result = utils::ReadString(basePointer);
        return result;
    }
    void print()
    {
        std::string str;
        str += "Level:\n";
        str += "\tBasePointer:\t\t\t\t" + utils::convertPointerToHexString(getBasePointer()) + "\n";
        str += "\tName:\t\t\t\t\t" + getName() + "\n";
        std::cout << str;
    }
};