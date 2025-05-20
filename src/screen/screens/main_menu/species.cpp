#include "species.h"
#include "../../manager/screen_manager.h"
#include "../../../database/database.h"
#include "../../../components/character/species_component.h"
#include "../../../data/enums/unicodes.h"
#include "raylib.h"
#include "raymath.h"
#include "talent.h"

namespace Aethereal::Screen::MainMenu
{
    Species::Species() : m_ScreenManager(GetInjection<ScreenManager>()),
                         m_Registry(GetInjection<FECS::Registry>()),
                         m_Database(GetInjection<Database>()),
                         m_PlayerView(m_Registry->View<Components::Tags::PlayerComponent>())

    {
    }

    void Species::Render()
    {
        Terminal::SetForegroundColor(WHITE);

        // Draw boxes
        Terminal::DrawBox(0, 0, 25, Terminal::Height(), Terminal::BoxStyle::LIGHT);
        Terminal::DrawBox(26, 0, Terminal::Width() - 26, Terminal::Height(), Terminal::BoxStyle::LIGHT);

        Terminal::Print(1, 0, "Select your Species");

        // get database info
        auto speciesList = *m_Database->Get("species");

        for (int i = 0; i < speciesList.size(); i++)
        {
            Color color = WHITE;
            std::string prefix = "";
            if (m_Selected == i)
            {
                color = YELLOW;
                prefix = "> ";
            }
            Terminal::SetForegroundColor(color);
            Terminal::Print(1, 1 + i, prefix + speciesList[i].at("name").get<std::string>());
        }

        // Print specification
        std::string speciesName = speciesList[m_Selected].at("name").get<std::string>();
        std::string speciesDesc = speciesList[m_Selected].at("description").get<std::string>();
        auto wrappedDesc = Terminal::WrapText(speciesDesc, 80);
        int difficultyRate = speciesList[m_Selected].at("difficulty").get<int>();

        Terminal::SetForegroundColor(WHITE);

        std::string difficulty = "";
        for (int i = 0; i < difficultyRate; i++)
        {
            difficulty += "\u2605";
        }

        Terminal::Print(27, 1, speciesName);
        Terminal::Print(27, 2, "Difficulty: " + difficulty);

        for (int i = 0; i < wrappedDesc.num; i++)
        {
            Terminal::Print(27, 4 + i, wrappedDesc.lines[i]);
        }
    }

    void Species::Update()
    {
        if (IsKeyPressed(KEY_K))
        {
            m_Selected = Clamp(m_Selected - 1, 0, m_Database->Get("species")->size() - 1);
        }

        if (IsKeyPressed(KEY_J))
        {
            m_Selected = Clamp(m_Selected + 1, 0, m_Database->Get("species")->size() - 1);
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            m_PlayerView.Each([&](FECS::Entity id, Components::Tags::PlayerComponent& _)
            {
                auto speciesList = *m_Database->Get("species");
                std::string name = speciesList[m_Selected].at("name").get<std::string>();
                m_Registry->Attach(id, Components::Character::SpeciesComponent{.speciesName = name});
            });

            m_ScreenManager->Replace(std::make_shared<Talent>());
        }
    }
}
