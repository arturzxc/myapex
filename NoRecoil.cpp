#pragma once
#include <vector>
#include "LocalPlayer.cpp"

class NoRecoil
{
private:
    const float m_strength = 1;
    float m_vecPunchWeaponAngleY = 0;

public:
    void update(LocalPlayer *localPlayer)
    {
        if (localPlayer->getZooming() != 1)
            return;
        const float vecPunchWeaponAngleY = localPlayer->getVecPunchWeaponAngleY();
        if (vecPunchWeaponAngleY == 0)
            return;
        const float viewAngleY = localPlayer->getViewAngleY();
        const float dVecPunchY = (vecPunchWeaponAngleY - m_vecPunchWeaponAngleY) * 0.9;
        const float newViewAngleY = viewAngleY - dVecPunchY;
        localPlayer->setViewAngleY(newViewAngleY);
        m_vecPunchWeaponAngleY = vecPunchWeaponAngleY;
    }
};