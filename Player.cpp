#pragma once
#include <iostream>
#include "Utils.cpp"
#include "Offsets.cpp"
#include "Memory.cpp"
#include "CachedValue.cpp"

class Player
{
private:
    CachedValue<float> m_locationX;
    CachedValue<float> m_locationY;
    CachedValue<float> m_locationZ;
    CachedValue<int> m_teamNumber;
    CachedValue<bool> m_dead;
    CachedValue<bool> m_knocked;

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
    void invalidateCache()
    {
        m_locationX.invalidate();
        m_locationY.invalidate();
        m_locationZ.invalidate();
        m_teamNumber.invalidate();
        m_dead.invalidate();
        m_knocked.invalidate();
    }
    void markForPointerResolution()
    {
        m_basePointer = 0;
    }
    bool isKnocked()
    {
        if (m_knocked.isValid())
            return m_knocked.getValue();
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::BLEEDOUT_STATE;
        short result = mem::ReadShort(ptrLong);
        m_knocked.setValue(result > 0);
        return m_knocked.getValue();
    }
    bool isDead()
    {
        if (m_dead.isValid())
            return m_dead.getValue();
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LIFE_STATE;
        short result = mem::ReadShort(ptrLong);
        m_dead.setValue(result > 0);
        return m_dead.getValue();
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
    float getLocationX()
    {
        if (m_locationX.isValid())
            return m_locationX.getValue();
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN;
        float result = mem::ReadFloat(ptrLong);
        m_locationX.setValue(result);
        return m_locationX.getValue();
    }
    float getLocationY()
    {
        if (m_locationY.isValid())
            return m_locationY.getValue();
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN + sizeof(float);
        float result = mem::ReadFloat(ptrLong);
        m_locationY.setValue(result);
        return m_locationY.getValue();
    }
    float getLocationZ()
    {
        if (m_locationZ.isValid())
            return m_locationZ.getValue();
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN + (sizeof(float) * 2);
        float result = mem::ReadFloat(ptrLong);
        m_locationZ.setValue(result);
        return m_locationZ.getValue();
    }
    int getTeamNumber()
    {
        if (m_teamNumber.isValid())
            return m_teamNumber.getValue();
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::TEAM_NUMBER;
        int result = mem::ReadInt(ptrLong);
        m_teamNumber.setValue(result);
        return m_teamNumber.getValue();
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
};
