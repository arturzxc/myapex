#include <iostream>
#include "Utils.cpp"
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
        long basePointer = utils::ReadLong(getUnresolvedBasePointer());
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
        std::cout << "LocalPlayer:\n";
        std::cout << "\tUnresolvedBasePointer:\t\t\t" + utils::convertPointerToHexString(getUnresolvedBasePointer()) + "\n";
        std::cout << "\tBasePointer:\t\t\t\t" + utils::convertPointerToHexString(getBasePointer()) + "\n";
        std::cout << "\tLocationOriginX:\t\t\t" + utils::convertNumberToString(getLocationOriginX()) + "\n";
        std::cout << "\tLocationOriginY:\t\t\t" + utils::convertNumberToString(getLocationOriginY()) + "\n";
        std::cout << "\tLocationOriginZ:\t\t\t" + utils::convertNumberToString(getLocationOriginZ()) + "\n";
        std::cout << "\tTeamNumber:\t\t\t\t" + utils::convertNumberToString(getTeamNumber()) + "\n";
        std::cout << "\tName:\t\t\t\t\t" + getName() + "\n";
        std::cout << "\tLifeState:\t\t\t\t" + utils::convertNumberToString(getLifeState()) + "\n";
        std::cout << "\tPunchWeaponAngleX:\t\t\t" + utils::convertNumberToString(getPunchWeaponAngleX()) + "\n";
        std::cout << "\tPunchWeaponAngleY:\t\t\t" + utils::convertNumberToString(getPunchWeaponAngleY()) + "\n";
        std::cout << "\tViewAngleX:\t\t\t\t" + utils::convertNumberToString(getViewAngleX()) + "\n";
        std::cout << "\tViewAngleY:\t\t\t\t" + utils::convertNumberToString(getViewAngleY()) + "\n";
        std::cout << "\tBleedoutState:\t\t\t\t" + utils::convertNumberToString(getBleedoutState()) + "\n";
    }
};