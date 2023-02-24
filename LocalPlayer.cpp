#pragma once
#include <iostream>
#include "Utils.cpp"
#include "Memory.cpp"
#include "Offsets.cpp"
#include "CachedValue.cpp"

class LocalPlayer
{
private:
    CachedValue<float> m_locationX;
    CachedValue<float> m_locationY;
    CachedValue<float> m_locationZ;
    CachedValue<int> m_teamNumber;
    CachedValue<bool> m_dead;
    CachedValue<bool> m_knocked;

    long m_basePointer = 0;
    long getUnresolvedBasePointer()
    {
        long unresolvedBasePointer = offsets::REGION + offsets::LOCAL_PLAYER;
        return unresolvedBasePointer;
    }
    long getBasePointer()
    {
        if (m_basePointer == 0)
            m_basePointer = mem::ReadLong(getUnresolvedBasePointer());
        return m_basePointer;
    }

public:
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
    bool isZooming()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::ZOOMING;
        short result = mem::ReadShort(ptrLong);
        return result > 0;
    }
};