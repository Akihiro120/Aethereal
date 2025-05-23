#include "confirm.h"
#include "../../manager/screen_manager.h"
#include "../../../components/character/name_component.h"
#include "../../../components/character/species_component.h"
#include "../../../components/character/talent_component.h"
#include "../navigation/navigation.h"
#include "../../../data/enums/unicodes.h"
#include "../../../data/ids.h"

#include "../../../components/character/stats/general_stat_component.h"

namespace Aethereal::Screen::MainMenu
{
    Confirm::Confirm()
        : m_Registry(GetInjection<FECS::Registry>()),
          m_ScreenManager(GetInjection<Aethereal::Screen::ScreenManager>())
    {
    }

    void Confirm::Render()
    {
        Terminal::SetForegroundColor(WHITE);
        Terminal::DrawBox(0, 0, Terminal::Width(), Terminal::Height(), Terminal::BoxStyle::LIGHT);

        Terminal::Print(1, 0, "Confirm");

        // render stats
        auto name = m_Registry->Get<Components::Character::NameComponent>(ID::GetPlayerID()).name;
        auto species = m_Registry->Get<Components::Character::SpeciesComponent>(ID::GetPlayerID()).speciesName;
        auto talent = m_Registry->Get<Components::Character::TalentComponent>(ID::GetPlayerID()).talentName;

        Terminal::Print(1, 1, name);
        Terminal::Print(1, 2, "Species: " + species);
        Terminal::Print(1, 3, "Talent: " + talent);

        for (int i = 0; i < 32; i++)
        {
            Terminal::Put(1 + i, 5, (int) Enum::Unicode::BoxLight::HORIZONTAL);
        }

        Terminal::SetForegroundColor(GRAY);
        Terminal::Print(1, 6, "Press any Button to Confirm.");
    }

    void Confirm::Update()
    {
        if (IsKeyPressed(GetKeyPressed()))
        {
            // attach components
            m_Registry->Attach(ID::GetPlayerID(), Components::Character::Stats::General::HealthComponent(100));
            m_Registry->Attach(ID::GetPlayerID(), Components::Character::Stats::General::StrengthComponent(100));
            m_Registry->Attach(ID::GetPlayerID(), Components::Character::Stats::General::DexterityComponent(100));
            m_Registry->Attach(ID::GetPlayerID(), Components::Character::Stats::General::StaminaComponent(100));

            // switch screen
            m_ScreenManager->Replace(std::make_shared<Navigation>());
        }
    }
}
