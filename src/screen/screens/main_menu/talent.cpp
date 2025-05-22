#include "talent.h"
#include "confirm.h"
#include "../../../screen/manager/screen_manager.h"
#include "../../../database/database.h"
#include "../../../components/character/talent_component.h"
#include "raymath.h"

namespace Aethereal::Screen::MainMenu
{
    Talent::Talent()
        : m_ScreenManager(GetInjection<Aethereal::Screen::ScreenManager>()),
          m_Database(GetInjection<Database>()),
          m_Registry(GetInjection<FECS::Registry>()),
          m_PlayerView(m_Registry->View<Components::Tags::PlayerComponent>())
    {
    }

    void Talent::Render()
    {
        Terminal::SetForegroundColor(WHITE);

        Terminal::DrawBox(0, 0, 25, Terminal::Height(), Terminal::BoxStyle::LIGHT);
        Terminal::DrawBox(26, 0, Terminal::Width() - 26, Terminal::Height(), Terminal::BoxStyle::LIGHT);

        Terminal::Print(1, 0, "Select your Talent");

        // get database info
        auto talentsList = *m_Database->Get("talents");

        for (int i = 0; i < talentsList.size(); i++)
        {
            Color color = WHITE;
            std::string prefix = "";
            if (m_Selected == i)
            {
                color = YELLOW;
                prefix = "> ";
            }
            Terminal::SetForegroundColor(color);
            Terminal::Print(1, 1 + i, prefix + talentsList[i].at("name").get<std::string>());
        }

        std::string name = talentsList[m_Selected].at("name").get<std::string>();
        std::string desc = talentsList[m_Selected].at("description").get<std::string>();
        auto descWrapped = Terminal::WrapText(desc, 80);
        int difficultyRate = talentsList[m_Selected].at("difficulty").get<int>();

        std::string difficulty = "";
        for (int i = 0; i < difficultyRate; i++)
        {
            difficulty += "* ";
        }

        Terminal::SetForegroundColor(WHITE);
        Terminal::Print(27, 1, name);
        Terminal::Print(27, 2, "Difficulty: " + difficulty);

        for (int i = 0; i < descWrapped.num; i++)
        {
            Terminal::Print(27, 4 + i, descWrapped.lines[i]);
        }

        auto flavor = talentsList[m_Selected].at("flavor").get<std::string>();
        auto flavorWrapped = Terminal::WrapText(flavor, 80);

        Terminal::SetForegroundColor(GRAY);
        for (int i = 0; i < flavorWrapped.num; i++)
        {
            Terminal::Print(27, 5 + descWrapped.num + i, flavorWrapped.lines[i]);
        }
    }

    void Talent::Update()
    {
        if (IsKeyPressed(KEY_J))
        {
            m_Selected = Clamp(m_Selected + 1, 0, m_Database->Get("talents")->size() - 1);
        }
        if (IsKeyPressed(KEY_K))
        {
            m_Selected = Clamp(m_Selected - 1, 0, m_Database->Get("talents")->size() - 1);
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            m_ScreenManager->Replace(std::make_shared<Confirm>());
        }
    }
}
