#include "species.h"
#include "../../manager/screen_manager.h"
#include "../../../database/database.h"
#include <ftxui/dom/elements.hpp>
#include "../../../components/character/species_component.h"
#include "talent.h"

namespace Aethereal::Screen::MainMenu
{
    Species::Species() : m_ScreenManager(GetInjection<ScreenManager>()),
                         m_Registry(GetInjection<FECS::Registry>()),
                         m_Database(GetInjection<Database>()),
                         m_PlayerView(m_Registry->View<Components::Tags::PlayerComponent>())

    {
        ConstructSceneRoot();
    }

    ftxui::Component Species::CreateComponentRoot()
    {
        // construct the specification
        auto species = m_Database->Get("species");

        for (auto& spec : *species)
        {
            m_Specification.names.push_back(spec.at("name"));
            m_Specification.descriptions.push_back(spec.at("description"));
            m_Specification.difficulty.push_back(spec.at("difficulty"));
        }

        m_SpeciesMenu = ftxui::Menu(ftxui::MenuOption{
            .entries = &m_Specification.names,
            .selected = &m_Selected,
            .on_enter = [&]
        {
            // Attach species component to player
            m_PlayerView.Each([&](FECS::Entity id, Components::Tags::PlayerComponent& _)
            {
                m_Registry->Attach(id, Components::Character::SpeciesComponent{.speciesName = m_Specification.names[m_Selected]});
            });

            // Goto next screen
            m_ScreenManager->Replace(std::make_shared<Talent>());
        }});

        return ftxui::Renderer([this]
        {
            std::string difficulty = "";
            for (int i = 0; i < (int) m_Specification.difficulty[m_Selected]; i++)
            {
                difficulty += "\u2605 ";
            }

            return ftxui::hbox({ftxui::window(ftxui::text("Select your Species") | ftxui::bold,
                                              ftxui::vbox({
                                                  m_SpeciesMenu->Render(),
                                              })) |
                                    ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 21),
                                ftxui::window(ftxui::text("Specification") | ftxui::bold,
                                              ftxui::vbox({ftxui::text(m_Specification.names[m_Selected]),
                                                           ftxui::separator(),
                                                           ftxui::paragraph(m_Specification.descriptions[m_Selected]) | size(ftxui::WIDTH, ftxui::EQUAL, 100),
                                                           ftxui::separatorEmpty(),
                                                           ftxui::text("Difficulty: " + difficulty)}) |
                                                  ftxui::flex)});
        });
    }

    ftxui::Component Species::CreateComponentContainer()
    {
        return ftxui::Container::Vertical({m_SpeciesMenu});
    }
}
