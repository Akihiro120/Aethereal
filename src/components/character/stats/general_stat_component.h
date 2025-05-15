#pragma once

namespace Aethereal::Components::Character::Stats::General
{
    struct HealthComponent
    {
        float health;
        float maxHealth;

        HealthComponent(float health)
        {
            this->health = health;
            this->maxHealth = health;
        }
    };

    struct StaminaComponent
    {
        float stamina;
        float maxStamina;

        StaminaComponent(float stamina)
        {
            this->stamina = stamina;
            this->maxStamina = stamina;
        }
    };

    struct StrengthComponent
    {
        float strength;
    };

    struct DexterityComponent
    {
        float dexterity;
    };
}
