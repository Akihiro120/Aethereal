#include "confirm.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include "../../manager/screen_manager.h"
#include "../../../components/tags/player_component.h"
#include "../../../components/character/name_component.h"
#include "../../../components/character/species_component.h"
#include "../../../components/character/talent_component.h"

namespace Aethereal::Screen::MainMenu
{
    Confirm::Confirm()
        : m_Registry(GetInjection<FECS::Registry>()),
          m_ScreenManager(GetInjection<Aethereal::Screen::ScreenManager>())
    {
        ConstructSceneRoot();
    }

    using namespace ftxui;

    ftxui::Component Confirm::CreateComponentRoot()
    {
        m_Registry->View<Components::Tags::PlayerComponent>().Each([&](FECS::Entity id, Components::Tags::PlayerComponent& _)
        {
            m_PlayerID = id;
        });

        auto root = Renderer([&]
        {
            return vbox({text("Confirmation") | bold,
                         separator(),
                         text("Name: " + m_Registry->Get<Components::Character::NameComponent>(m_PlayerID).name),
                         text("Species: " + m_Registry->Get<Components::Character::SpeciesComponent>(m_PlayerID).speciesName),
                         text("Talent: " + m_Registry->Get<Components::Character::TalentComponent>(m_PlayerID).talentName),
                         separator(),
                         text("Press any Button to Continue.")});
        });

        root |= CatchEvent([&](Event event)
        {
            if (event.is_character())
            {
                // Switch to main game

                return true;
            }

            return false;
        });

        return root;
    }

    ftxui::Component Confirm::CreateComponentContainer()
    {
        return Container::Vertical({

        });
    }
}
