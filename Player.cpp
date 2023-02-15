#pragma once
#include <iostream>
#include "Utils.cpp"
#include "Offsets.cpp"
#include "Memory.cpp"

class Player
{
private:
    int m_entityListIndex;
    float m_lastVisibleTime;
    long m_basePointer = 0;
    long getUnresolvedBasePointer()
    {
        long unresolvedBasePointer = offsets::REGION + offsets::ENTITY_LIST + ((m_entityListIndex + 1) << 5);
        return unresolvedBasePointer;
    }
    long getBasePointer()
    {
        if (m_basePointer == 0)
            m_basePointer = mem::ReadLong(getUnresolvedBasePointer());
        return m_basePointer;
    }

public:
    Player(int entityListIndex)
    {
        m_entityListIndex = entityListIndex;
    }
    void markForPointerResolution()
    {
        m_basePointer = 0;
    }
    bool isDead()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LIFE_STATE;
        short result = mem::ReadShort(ptrLong);
        return result > 0;
    }
    bool isKnocked()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::BLEEDOUT_STATE;
        short result = mem::ReadShort(ptrLong);
        return result > 0;
    }
    std::string getName()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::NAME;
        std::string result = mem::ReadString(ptrLong);
        return result;
    }
    bool isValid()
    {
        return getBasePointer() > 0 && !isDead();
    }
    std::string getInvalidReason()
    {
        if (getBasePointer() == 0)
            return "Unresolved base pointer";
        else if (isDead())
            return "Player is dead";
        else if (getName().empty())
            return "Name is empty";
        else
            return "Player is valid";
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
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN + sizeof(float) + sizeof(float);
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
    int getShieldsValue()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::CURRENT_SHIELDS;
        int result = mem::ReadInt(ptrLong);        
        return result;
    }
    int getGlowEnable()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_ENABLE;
        int result = mem::ReadInt(ptrLong);
        return result;
    }
    void setGlowEnable(int glowEnable)
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_ENABLE;
        mem::WriteInt(ptrLong, glowEnable);
    }
    int getGlowThroughWall()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_THROUGH_WALL;
        int result = mem::ReadInt(ptrLong);
        return result;
    }
    void setGlowThroughWall(int glowThroughWall)
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_THROUGH_WALL;
        mem::WriteInt(ptrLong, glowThroughWall);
    }
    int getGlowColorRed()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_COLOR;
        int result = mem::ReadInt(ptrLong);
        return result;
    }
    void setGlowColorRed(float color)
    {
        if (color > 100)
            color = 100;
        if (color < 0)
            color = 0;
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_COLOR;
        mem::WriteFloat(ptrLong, color);
    }
    void setGlowColorGreen(float color)
    {
        if (color > 100)
            color = 100;
        if (color < 0)
            color = 0;
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_COLOR + sizeof(float);
        mem::WriteFloat(ptrLong, color);
    }
    void setGlowColorBlue(float color)
    {
        if (color > 100)
            color = 100;
        if (color < 0)
            color = 0;
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_COLOR + sizeof(float) + sizeof(float);
        ;
        mem::WriteFloat(ptrLong, color);
    }
    float getLastVisibleTime()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LAST_VISIBLE_TIME;
        float result = mem::ReadFloat(ptrLong);
        return result;
    }
    bool isVisible()
    {
        const float lastVisibleTime = getLastVisibleTime();
        const bool isVisible = lastVisibleTime > m_lastVisibleTime;
        m_lastVisibleTime = lastVisibleTime;
        return isVisible;
    }
    void print()
    {
        std::cout << "Player[" + std::to_string(m_entityListIndex) + "]:\n";
        std::cout << "\tUnresolvedBasePointer:\t\t\t" + mem::convertPointerToHexString(getUnresolvedBasePointer()) + "\n";
        std::cout << "\tBasePointer:\t\t\t\t" + mem::convertPointerToHexString(getBasePointer()) + "\n";
        std::cout << "\tIsValid:\t\t\t\t" + std::to_string(isValid()) + "\n";
        std::cout << "\tInvalidReason:\t\t\t\t" + getInvalidReason() + "\n";
        if (!isValid())
        {
            std::cout << "\tLocationOriginX:\t\t\t" + utils::convertNumberToString(getLocationX()) + "\n";
            std::cout << "\tLocationOriginY:\t\t\t" + utils::convertNumberToString(getLocationY()) + "\n";
            std::cout << "\tLocationOriginZ:\t\t\t" + utils::convertNumberToString(getLocationZ()) + "\n";
            std::cout << "\tTeamNumber:\t\t\t\t" + utils::convertNumberToString(getTeamNumber()) + "\n";
            std::cout << "\tGlowEnable:\t\t\t\t" + utils::convertNumberToString(getGlowEnable()) + "\n";
            std::cout << "\tGlowThroughWall:\t\t\t" + utils::convertNumberToString(getGlowThroughWall()) + "\n";
        }
    }
};
