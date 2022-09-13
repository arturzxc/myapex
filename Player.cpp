#include <iostream>
#include "Utils.cpp"
#include "Offsets.cpp"

class LocalPlayer
{
public:
    long getBasePointer()
    {
        long basePointer = utils::ReadLong(offsets::REGION + offsets::LOCAL_PLAYER);
        return basePointer;
    }
    float getLocationOriginX()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN;
        float result = utils::ReadFloat(ptrLong);
        return result;
    }
    float getLocationOriginY()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN + sizeof(float);
        float result = utils::ReadFloat(ptrLong);
        return result;
    }
    float getLocationOriginZ()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN + sizeof(float) + sizeof(float);
        float result = utils::ReadFloat(ptrLong);
        return result;
    }
    int getTeamNumber()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::TEAM_NUMBER;
        int result = utils::ReadInt(ptrLong);
        return result;
    }
    std::string getName()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::NAME;
        std::string result = utils::ReadString(ptrLong);
        return result;
    }
    short getLifeState()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LIFE_STATE;
        short result = utils::ReadShort(ptrLong);
        return result;
    }
    float getPunchWeaponAngleX()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VEC_PUNCH_WEAPON_ANGLE;
        float result = utils::ReadFloat(ptrLong);
        return result;
    }
    float getPunchWeaponAngleY()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VEC_PUNCH_WEAPON_ANGLE + sizeof(float);
        float result = utils::ReadFloat(ptrLong);
        return result;
    }
    float getViewAngleX()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VIEW_ANGLE;
        float result = utils::ReadFloat(ptrLong);
        return result;
    }
    float getViewAngleY()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VIEW_ANGLE + sizeof(float);
        float result = utils::ReadFloat(ptrLong);
        return result;
    }
    short getBleedoutState()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::BLEEDOUT_STATE;
        short result = utils::ReadShort(ptrLong);
        return result;
    }
    void print()
    {
        std::string str;
        str += "LocalPlayer:\n";
        str += "\tBasePointer:\t\t\t" + utils::convertPointerToHexString(getBasePointer()) + "\n";
        str += "\tLocationOriginX:\t\t" + utils::tStringWithPrecission(getLocationOriginX()) + "\n";
        str += "\tLocationOriginY:\t\t" + utils::tStringWithPrecission(getLocationOriginY()) + "\n";
        str += "\tLocationOriginZ:\t\t" + utils::tStringWithPrecission(getLocationOriginZ()) + "\n";
        str += "\tTeamNumber:\t\t\t" + utils::tStringWithPrecission(getTeamNumber()) + "\n";
        str += "\tName:\t\t\t\t" + getName() + "\n";
        str += "\tLifeState:\t\t\t" + utils::tStringWithPrecission(getLifeState()) + "\n";
        str += "\tPunchWeaponAngleX:\t\t" + utils::tStringWithPrecission(getPunchWeaponAngleX()) + "\n";
        str += "\tPunchWeaponAngleY:\t\t" + utils::tStringWithPrecission(getPunchWeaponAngleY()) + "\n";
        str += "\tViewAngleX:\t\t\t" + utils::tStringWithPrecission(getViewAngleX()) + "\n";
        str += "\tViewAngleY:\t\t\t" + utils::tStringWithPrecission(getViewAngleY()) + "\n";
        str += "\tBleedoutState:\t\t\t" + utils::tStringWithPrecission(getBleedoutState()) + "\n";
        std::cout << str;
    }
};