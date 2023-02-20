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
            m_basePointer = mem::ReadMemory<long>(getUnresolvedBasePointer());
        return m_basePointer;
    }

public:
    Player(int entityListIndex)
    {
        m_entityListIndex = entityListIndex;
    }

    bool isValid()
    {
        return getBasePointer() > 0 && !isDead();
    }

    bool isDead()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LIFE_STATE;
        short result = mem::ReadMemory<short>(ptrLong);
        return result > 0;
    }

    bool isKnocked()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::BLEEDOUT_STATE;
        short result = mem::ReadMemory<short>(ptrLong);
        return result > 0;
    }
    bool isVisible()
    {
        const float lastVisibleTime = getLastVisibleTime();
        const bool isVisible = lastVisibleTime > m_lastVisibleTime;
        m_lastVisibleTime = lastVisibleTime;
        return isVisible;
    }

    std::string getName()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::NAME;
        std::string result = mem::ReadString(ptrLong);
        return result;
    }

    float getLocationX()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN;
        float result = mem::ReadMemory<float>(ptrLong);
        return result;
    }

    float getLocationY()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN + sizeof(float);
        float result = mem::ReadMemory<float>(ptrLong);
        return result;
    }

    float getLocationZ()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN + sizeof(float) + sizeof(float);
        float result = mem::ReadMemory<float>(ptrLong);
        return result;
    }

    int getTeamNumber()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::TEAM_NUMBER;
        int result = mem::ReadMemory<int>(ptrLong);
        return result;
    }

    int getShieldsValue()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::CURRENT_SHIELDS;
        int result = mem::ReadMemory<int>(ptrLong);
        return result;
    }

    int getGlowEnable()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_ENABLE;
        int result = mem::ReadMemory<int>(ptrLong);
        return result;
    }

    void setGlowEnable(int glowEnable)
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_ENABLE;
        mem::WriteMemory<int>(ptrLong, glowEnable);
    }

    int getGlowThroughWall()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_THROUGH_WALL;
        int result = mem::ReadMemory<int>(ptrLong);
        return result;
    }

    void setGlowThroughWall(int glowThroughWall)
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_THROUGH_WALL;
        mem::WriteMemory<int>(ptrLong, glowThroughWall);
    }

    int getGlowColorRed()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_COLOR;
        int result = mem::ReadMemory<int>(ptrLong);
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
        mem::WriteMemory<float>(ptrLong, color);
    }

    void setGlowColorGreen(float color)
    {
        if (color > 100)
            color = 100;
        if (color < 0)
            color = 0;
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::GLOW_COLOR + sizeof(float);
        mem::WriteMemory<float>(ptrLong, color);
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
        mem::WriteMemory<float>(ptrLong, color);
    }

    float getLastVisibleTime()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LAST_VISIBLE_TIME;
        float result = mem::ReadMemory<float>(ptrLong);
        return result;
    }

    std::string getSignifierName()
    {
        try
        {
            long basePointer = getBasePointer();
            long sigOff = offsets::SIGNIFIER_NAME;
            long sigPointer = mem::ReadMemory<long>(basePointer + sigOff);
            return mem::ReadString(sigPointer);
        }
        catch (...)
        {
            return "";
        }
    }
    
};
