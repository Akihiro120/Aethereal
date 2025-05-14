#include "talent.h"
#include "confirm.h"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include "../../../screen/manager/screen_manager.h"
#include "../../../database/database.h"
#include "../../../components/character/talent_component.h"

using namespace ftxui;

namespace Aethereal::Screen::MainMenu
{
    Talent::Talent()
        : m_ScreenManager(GetInjection<Aethereal::Screen::ScreenManager>()),
          m_Database(GetInjection<Database>()),
          m_Registry(GetInjection<FECS::Registry>()),
          m_PlayerView(m_Registry->View<Components::Tags::PlayerComponent>())
    {
        ConstructSceneRoot();
    }

    ftxui::Component Talent::CreateComponentRoot()
    {
        // load talents
        auto talents = m_Database->Get("talents");
        for (auto& talent : *talents)
        {
            m_TalentSpecification.names.push_back(talent.at("name"));
            m_TalentSpecification.descriptions.push_back(talent.at("description"));
            m_TalentSpecification.difficulties.push_back(talent.at("difficulty"));
        }

        auto talentOptions = ftxui::MenuOption{
            .entries = &m_TalentSpecification.names,
            .selected = &m_Selected,
            .on_enter = [&]
        {
            m_PlayerView.Each([&](FECS::Entity id, Components::Tags::PlayerComponent& _)
            {
                m_Registry->Attach(id, Components::Character::TalentComponent{.talentName = m_TalentSpecification.names[m_Selected]});
            });

            m_ScreenManager->Replace(std::make_shared<Confirm>());
        }};
        m_TalentMenu = ftxui::Menu(talentOptions);

        return Renderer([&]
        {
            std::string difficulty = "";
            for (int i = 0; i < (int) m_TalentSpecification.difficulties[m_Selected]; i++)
            {
                difficulty += "\u2605 ";
            }
            return hbox({window(text("Select your Talent") | bold, vbox({m_TalentMenu->Render()})) | size(WIDTH, EQUAL, 21),
                         window(text("Talent Specification") | bold, vbox({text(m_TalentSpecification.names[m_Selected]),
                                                                           separator(),
                                                                           text(m_TalentSpecification.descriptions[m_Selected]), text("Diffculty: " + difficulty)})) |
                             flex});
        });
    }

    ftxui::Component Talent::CreateComponentContainer()
    {
        return ftxui::Container::Vertical({m_TalentMenu});
    }
}
