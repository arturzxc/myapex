#pragma once
namespace offsets
{
    // buttons
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const long IN_ATTACK = 0x0759bff8; // [Buttons]          -> in_attack
    // core
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const long REGION = 0x140000000;     // [Mine]           -> Region
    const long LEVEL = 0x13a17b8;        // [Miscellaneous]  -> LevelName
    const long LOCAL_PLAYER = 0x1e25418; // [Miscellaneous]  -> LocalPlayer
    const long ENTITY_LIST = 0x1a75038;  // [Miscellaneous]  -> cl_entitylist
    // entity
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const long LOCAL_ORIGIN = 0x158; // [DataMap.CBaseViewModel]    -> m_localOrigin
    // player
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const long GLOW_ENABLE = 0x3c8;             // [RecvTable.DT_HighlightSettings] -> m_highlightServerContextID + 0x8
    const long GLOW_THROUGH_WALL = 0x3d0;       // [RecvTable.DT_HighlightSettings] -> m_highlightServerContextID + 0x10
    const long TEAM_NUMBER = 0x448;             // [RecvTable.DT_BaseEntity]        -> m_iTeamNum
    const long NAME = 0x589;                    // [RecvTable.DT_BaseEntity]        -> m_iName
    const long LIFE_STATE = 0x798;              // [RecvTable.DT_Player]            -> m_lifeState
    const long VEC_PUNCH_WEAPON_ANGLE = 0x23f8; // [DataMap.C_Player]               -> m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
    const long VIEW_ANGLE = 0x24e0;             // [DataMap.C_Player]               -> m_ammoPoolCapacity - 0x14
    const long BLEEDOUT_STATE = 0x2688;         // [RecvTable.DT_Player]            -> m_bleedoutState
    const long ZOOMING = 0x1bc1;                // [RecvTable.DT_Player]            -> m_bZooming
    const long LAST_VISIBLE_TIME = 0x1a44;      // [Miscellaneous]                  -> CPlayer!lastVisibleTime
}