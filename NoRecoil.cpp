#pragma once
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"

class NoRecoil
{
private:
    const float m_streangthPitch = 0.9;
    const float m_streangthYaw = 0.99;
    float m_previousPunchAnglePitch;
    float m_previousPunchAngleYaw;

public:
    void update(LocalPlayer *localPlayer)
    {
        const float viewAnglePitch = localPlayer->getViewAngleX();
        const float viewAngleYaw = localPlayer->getViewAngleY();
        const float punchAnglePitch = localPlayer->getVecPunchWeaponAngleX();
        const float punchAngleYaw = localPlayer->getVecPunchWeaponAngleY();
        if (punchAnglePitch == 0 && punchAngleYaw == 0)
            return;
        const float punchAnglePitchDelta = punchAnglePitch - m_previousPunchAnglePitch;
        const float punchAngleYawDelta = punchAngleYaw - m_previousPunchAngleYaw;
        const float newViewAnglePitch = viewAnglePitch - (punchAnglePitchDelta * m_streangthPitch);
        const float newViewAngleYaw = viewAngleYaw - (punchAngleYawDelta * m_streangthYaw);
        localPlayer->setViewAngleX(newViewAnglePitch);
        localPlayer->setViewAngleY(newViewAngleYaw);
        m_previousPunchAnglePitch = punchAnglePitch;
        m_previousPunchAngleYaw = punchAngleYaw;
    }
};