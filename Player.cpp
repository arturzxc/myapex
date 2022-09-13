#include <iostream>
#include "Utils.cpp"
#include "Offsets.cpp"

class Player
{
private:
    int m_entityListIndex;

public:
    Player(int entityListIndex)
    {
        m_entityListIndex = entityListIndex;
    }

    long getUnresolvedBasePointer()
    {
        long unresolvedBasePointer = offsets::REGION + offsets::ENTITY_LIST + ((m_entityListIndex + 1) << 5);
        return unresolvedBasePointer;
    }
    long getBasePointer()
    {
        long basePointer = utils::ReadLong(getUnresolvedBasePointer());
        return basePointer;
    }
    short getLifeState()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LIFE_STATE;
        short result = utils::ReadShort(ptrLong);
        return result;
    }
    std::string getName()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::NAME;
        std::string result = utils::ReadString(ptrLong);
        return result;
    }
    bool isValid()
    {
        return getBasePointer() > 0 && getLifeState() == 0 && !getName().empty();
    }
    std::string getInvalidReason()
    {
        if (getBasePointer() == 0)
            return "Unresolved base pointer";
        else if (getLifeState() != 0)
            return "LifeState is not zero";
        else if (getName().empty())
            return "Name is empty";
        else
            return "";
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
    int getGlowEnable()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_ENABLE;
        int result = utils::ReadInt(ptrLong);
        return result;
    }
    int getGlowThroughWall()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_THROUGH_WALL;
        int result = utils::ReadInt(ptrLong);
        return result;
    }
    void print()
    {
        std::cout << "Player[" + std::to_string(m_entityListIndex) + "]:\n";
        std::cout << "\tUnresolvedBasePointer:\t\t\t" + utils::convertPointerToHexString(getUnresolvedBasePointer()) + "\n";
        std::cout << "\tBasePointer:\t\t\t\t" + utils::convertPointerToHexString(getBasePointer()) + "\n";
        std::cout << "\tIsValid:\t\t\t\t" + std::to_string(isValid()) + "\n";
        if (!isValid())
            std::cout << "\tInvalidReason:\t\t\t\t" + getInvalidReason() + "\n";
        else
        {
            std::cout << "\tLocationOriginX:\t\t\t" + utils::convertNumberToString(getLocationOriginX()) + "\n";
            std::cout << "\tLocationOriginY:\t\t\t" + utils::convertNumberToString(getLocationOriginY()) + "\n";
            std::cout << "\tLocationOriginZ:\t\t\t" + utils::convertNumberToString(getLocationOriginZ()) + "\n";
            std::cout << "\tTeamNumber:\t\t\t\t" + utils::convertNumberToString(getTeamNumber()) + "\n";
            std::cout << "\tGlowEnable:\t\t\t\t" + utils::convertNumberToString(getGlowEnable()) + "\n";
            std::cout << "\tGlowThroughWall:\t\t\t" + utils::convertNumberToString(getGlowThroughWall()) + "\n";
        }
    }
};
