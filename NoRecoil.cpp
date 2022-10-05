#pragma once
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"
#include "Level.cpp"
#include "X11Utils.cpp"

class NoRecoil
{
private:
    const double m_streangthPitch = 0.5;
    const double m_streangthYaw = 0.8;
    double m_previousPunchPitch = 0;
    double m_previousPunchYaw = 0;

public:
    void update(Level *level, LocalPlayer *localPlayer, X11Utils *x11Utils)
    {
        if (!x11Utils->triggerKeyDown())
            return;
        if (!level->isPlayable())
            return;
        // pitch
        const double punchPitch = localPlayer->getPunchPitch();
        if (punchPitch != 0)
        {
            const double pitch = localPlayer->getPitch();
            const double punchPitchDelta = (punchPitch - m_previousPunchPitch) * m_streangthPitch;
            localPlayer->setPitch(pitch - punchPitchDelta);
            m_previousPunchPitch = punchPitch;
        }
        // yaw
        const double punchYaw = localPlayer->getPunchYaw();
        if (punchYaw != 0)
        {
            const double yaw = localPlayer->getYaw();
            const double punchYawDelta = (punchYaw - m_previousPunchYaw) * m_streangthYaw;
            localPlayer->setYaw(yaw - punchYawDelta);
            m_previousPunchYaw = punchYaw;
        }
    }
};