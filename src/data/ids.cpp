#include "ids.h"

namespace Aethereal::ID
{
    static FECS::Entity s_PlayerID;

    void SetPlayerID(FECS::Entity id)
    {
        s_PlayerID = id;
    }

    FECS::Entity GetPlayerID()
    {
        return s_PlayerID;
    }
}
