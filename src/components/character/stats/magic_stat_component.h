#pragma once

namespace Aethereal::Components::Character::Stats::Magic
{
    struct ManaPotencyComponent
    {
        float manaPotency;
    };

    struct ManaCapacityComponent
    {
        float manaCapacity;
    };

    struct CastingEfficiency
    {
        float efficiency;
    };

    enum class ManaTechnique
    {
        MANA_TECHNIQUE_CIRCLE,
        MANA_TECHNIQUE_AURA,
        MANA_TECHNIQUE_SIPHON,
    };

    struct ManaTechniqueComponent
    {
        ManaTechnique technique;
    };
}
