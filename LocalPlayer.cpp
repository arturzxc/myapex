#pragma once
#include <iostream>
#include "Utils.cpp"
#include "Memory.cpp"
#include "Offsets.cpp"

class LocalPlayer
{
public:
    long getUnresolvedBasePointer()
    {
        long unresolvedBasePointer = offsets::REGION + offsets::LOCAL_PLAYER;
        return unresolvedBasePointer;
    }
    long getBasePointer()
    {
        long basePointer = mem::ReadLong(getUnresolvedBasePointer());
        return basePointer;
    }
    float getLocationX()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN;
        float result = mem::ReadFloat(ptrLong);
        return result;
    }
    float getLocationY()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN + sizeof(float);
        float result = mem::ReadFloat(ptrLong);
        return result;
    }
    float getLocationZ()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN + (sizeof(float) * 2);
        float result = mem::ReadFloat(ptrLong);
        return result;
    }
    int getTeamNumber()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::TEAM_NUMBER;
        int result = mem::ReadInt(ptrLong);
        return result;
    }
    bool isInAttack()
    {
        long basePointer = getBasePointer();
        long ptrLong = offsets::REGION + offsets::IN_ATTACK;
        int result = mem::ReadInt(ptrLong);
        return result > 0;
    }
    std::string getName()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::NAME;
        std::string result = mem::ReadString(ptrLong);
        return result;
    }
    short getLifeState()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LIFE_STATE;
        short result = mem::ReadShort(ptrLong);
        return result;
    }
    float getPunchPitch()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VEC_PUNCH_WEAPON_ANGLE;
        float result = mem::ReadFloat(ptrLong);
        return result;
    }
    float getPunchYaw()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VEC_PUNCH_WEAPON_ANGLE + sizeof(float);
        float result = mem::ReadFloat(ptrLong);
        return result;
    }
    float getPitch()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VIEW_ANGLE;
        float result = mem::ReadFloat(ptrLong);
        return result;
    }
    void setPitch(float angle)
    {
        if (angle > 90 || angle < -90)
            return;
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VIEW_ANGLE;
        mem::WriteFloat(ptrLong, angle);
    }
    float getYaw()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VIEW_ANGLE + sizeof(float);
        float result = mem::ReadFloat(ptrLong);
        return result;
    }
    void setYaw(float angle)
    {
        if (angle > 180 || angle < -180)
            return;
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VIEW_ANGLE + sizeof(float);
        mem::WriteFloat(ptrLong, angle);
    }
    short getBleedoutState()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::BLEEDOUT_STATE;
        short result = mem::ReadShort(ptrLong);
        return result;
    }
    bool isZooming()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::ZOOMING;
        short result = mem::ReadShort(ptrLong);
        return result > 0;
    }
    void print()
    {
        std::cout << "LocalPlayer:\n";
        std::cout << "\tUnresolvedBasePointer:\t\t\t" + mem::convertPointerToHexString(getUnresolvedBasePointer()) + "\n";
        std::cout << "\tBasePointer:\t\t\t\t" + mem::convertPointerToHexString(getBasePointer()) + "\n";
        std::cout << "\tLocationOriginX:\t\t\t" + utils::convertNumberToString(getLocationX()) + "\n";
        std::cout << "\tLocationOriginY:\t\t\t" + utils::convertNumberToString(getLocationY()) + "\n";
        std::cout << "\tLocationOriginZ:\t\t\t" + utils::convertNumberToString(getLocationZ()) + "\n";
        std::cout << "\tTeamNumber:\t\t\t\t" + utils::convertNumberToString(getTeamNumber()) + "\n";
        std::cout << "\tName:\t\t\t\t\t" + getName() + "\n";
        std::cout << "\tLifeState:\t\t\t\t" + utils::convertNumberToString(getLifeState()) + "\n";
        std::cout << "\tPunchWeaponAngleX:\t\t\t" + utils::convertNumberToString(getPunchPitch()) + "\n";
        std::cout << "\tPunchWeaponAngleY:\t\t\t" + utils::convertNumberToString(getPunchYaw()) + "\n";
        std::cout << "\tViewAngleX:\t\t\t\t" + utils::convertNumberToString(getPitch()) + "\n";
        std::cout << "\tViewAngleY:\t\t\t\t" + utils::convertNumberToString(getYaw()) + "\n";
        std::cout << "\tBleedoutState:\t\t\t\t" + utils::convertNumberToString(getBleedoutState()) + "\n";
        std::cout << "\tZooming:\t\t\t\t" + utils::convertNumberToString(isZooming()) + "\n";
    }
};