#pragma once
#include <iostream>
#include "Utils.cpp"
#include "Memory.cpp"
#include "Offsets.cpp"

class LocalPlayer
{
private:
    long m_basePointer = 0;

    long getUnresolvedBasePointer()
    {
        long unresolvedBasePointer = offsets::REGION + offsets::LOCAL_PLAYER;
        return unresolvedBasePointer;
    }

    long getBasePointer()
    {
        if (m_basePointer == 0)
            m_basePointer = mem::ReadMemory<long>(getUnresolvedBasePointer());
        return m_basePointer;
    }

public:
    float getLocationX()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN;
        return mem::ReadMemory<float>(ptrLong);
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
        long ptrLong = basePointer + offsets::LOCAL_ORIGIN + (sizeof(float) * 2);
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

    bool isInAttack()
    {
        long basePointer = getBasePointer();
        long ptrLong = offsets::REGION + offsets::IN_ATTACK;
        int result = mem::ReadMemory<int>(ptrLong);
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
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::BLEEDOUT_STATE;
        short result = mem::ReadMemory<short>(ptrLong);
        return result > 0;
    }

    bool isDead()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::LIFE_STATE;
        short result = mem::ReadMemory<short>(ptrLong);
        return result > 0;
    }

    float getPunchPitch()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VEC_PUNCH_WEAPON_ANGLE;
        return mem::ReadMemory<float>(ptrLong);
    }

    float getPunchYaw()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VEC_PUNCH_WEAPON_ANGLE + sizeof(float);
        return mem::ReadMemory<float>(ptrLong);
    }

    float getPitch()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VIEW_ANGLE;
        float result = mem::ReadMemory<float>(ptrLong);
        return result;
    }

    void setPitch(float angle)
    {
        if (angle > 90 || angle < -90)
            return;
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VIEW_ANGLE;
        mem::WriteMemory<float>(ptrLong, angle);
    }

    float getYaw()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VIEW_ANGLE + sizeof(float);
        float result = mem::ReadMemory<float>(ptrLong);
        return result;
    }

    void setYaw(float angle)
    {
        if (angle > 180 || angle < -180)
            return;
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::VIEW_ANGLE + sizeof(float);
        mem::WriteMemory<float>(ptrLong, angle);
    }

    bool isZooming()
    {
        long basePointer = getBasePointer();
        long ptrLong = basePointer + offsets::ZOOMING;
        short result = mem::ReadMemory<short>(ptrLong);
        return result > 0;
    }
};