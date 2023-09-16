#pragma once
namespace offsets
{
    // buttons
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    constexpr long IN_ATTACK = (0x07473fb8);            // [Buttons] -> in_attack
    // core
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    constexpr long REGION = 0x140000000;              // [Mine]          -> Region
    constexpr long LEVEL = 0x16efe10;                 // [Miscellaneous] -> LevelName
    constexpr long LOCAL_PLAYER = 0x2225648;      // [Miscellaneous] -> AVC_GameMovement+0x8
    constexpr long ENTITY_LIST = 0x1e754c8;           // [Miscellaneous] -> cl_entitylist
    // entity
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    constexpr long LOCAL_ORIGIN = 0x0188; // [DataMap.CBaseViewModel]    -> m_localOrigin
    // player
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    constexpr long GLOW_ENABLE = 0x03f0 + 0x8;              // [RecvTable.DT_HighlightSettings] -> m_highlightServerContextID + 0x8
    constexpr long GLOW_THROUGH_WALL = 0x03f0 + 0x10;               // [RecvTable.DT_HighlightSettings] -> m_highlightServerContextID + 0x10
    constexpr long GLOW_COLOR = 0x200;                  // [Miscellaneous]                  -> glow_color
    constexpr long TEAM_NUMBER = 0x0480;                // [RecvTable.DT_BaseEntity]        -> m_iTeamNum
    constexpr long NAME = 0x05c1;                       // [RecvTable.DT_BaseEntity]        -> m_iName
    constexpr long LIFE_STATE = 0x07d0;                 // [RecvTable.DT_Player]            -> m_lifeState
    constexpr long VEC_PUNCH_WEAPON_ANGLE = 0x24e8;     // [DataMap.C_Player]               -> m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
    constexpr long VIEW_ANGLE = (0x25e4 - 0x14);        // [DataMap.C_Player]               -> m_ammoPoolCapacity - 0x14
    constexpr long BLEEDOUT_STATE = 0x2790;             // [RecvTable.DT_Player]            -> m_bleedoutState
    constexpr long ZOOMING = 0x1c81;                    // [RecvTable.DT_Player]            -> m_bZooming
    constexpr long LAST_VISIBLE_TIME = 0x1aa0;          // [Miscellaneous]                  -> CPlayer!lastVisibleTime
    constexpr long CURRENT_SHIELDS = 0x01a0;            // m_shieldHealth
    constexpr long CURRENT_HEALTH = 0x470;                  // m_iHealth
    constexpr long ARMOR_TYPE = 0x4694;             // m_armorType
    constexpr long OFFSET_ViewModels = 0x2dc0;         // m_hViewModels
    constexpr long thirdperson_override = 0x01e03040;          // m_thirdPersonOverride
    constexpr long m_thirdPersonShoulderView = 0x3728;    // m_thirdPersonShoulderView
}
