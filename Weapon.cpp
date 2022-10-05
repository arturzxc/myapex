#pragma once
#include <iostream>
#include "Utils.cpp"
#include "Memory.cpp"
#include "Offsets.cpp"

class Weapon
{
public:
    long getUnresolvedBasePointer()
    {
        long unresolvedBasePointer = offsets::REGION + offsets::WEAPON;
        return unresolvedBasePointer;
    }
    long getBasePointer()
    {
        long basePointer = mem::ReadLong(getUnresolvedBasePointer());
        return basePointer;
    }
    int ammo()
    {
        long basePointer = getUnresolvedBasePointer();
        long ptrLong = basePointer + offsets::WEAPON_AMMO_IN_CLIP;
        int result = mem::ReadInt(ptrLong);
        return result;
    }
};