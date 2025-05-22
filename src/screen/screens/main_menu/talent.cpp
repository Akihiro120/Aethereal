#include "talent.h"
#include "confirm.h"
#include "../../../screen/manager/screen_manager.h"
#include "../../../database/database.h"
#include "../../../components/character/talent_component.h"
#include "raylib.h"
#include "raymath.h"
#include "../../../data/ids.h"

namespace Aethereal::Screen::MainMenu
{
    Talent::Talent()
        : m_ScreenManager(GetInjection<Aethereal::Screen::ScreenManager>()),
          m_Database(GetInjection<Database>()),
          m_Registry(GetInjection<FECS::Registry>()),
          m_PlayerView(m_Registry->View<Components::Tags::PlayerComponent>())
    {
        m_TalentList = *m_Database->Get("talents");
    }

    void Talent::Render()
    {
        Terminal::SetForegroundColor(WHITE);

        Terminal::DrawBox(0, 0, 25, Terminal::Height(), Terminal::BoxStyle::LIGHT);
        Terminal::DrawBox(26, 0, Terminal::Width() - 26, Terminal::Height(), Terminal::BoxStyle::LIGHT);

        int selectionPanelOffset = RenderSelectionPanel(0);
        int specificationOffset = RenderSpecification(selectionPanelOffset);
        int strengthOffset = RenderStrengths(specificationOffset);
        int weaknessOffset = RenderWeaknesses(strengthOffset);
        RenderFlavor(weaknessOffset);
    }

    int Talent::RenderSelectionPanel(int offset)
    {
        Terminal::SetForegroundColor(WHITE);

        int numTalents = m_TalentList.size();
        for (int i = 0; i < numTalents; i++)
        {
            auto talent = m_TalentList[i];
            Color color = WHITE;
            std::string prefix = "";

            if (m_Selected == i)
            {
                color = YELLOW;
                prefix = "> ";
            }

            Terminal::SetForegroundColor(color);
            Terminal::Print(1, 1 + i, prefix + talent.at("name").get<std::string>());
        }

        return 1 + numTalents;
    }

    int Talent::RenderSpecification(int offset)
    {
        Terminal::SetForegroundColor(WHITE);

        auto talentSpec = m_TalentList[m_Selected];

        std::string name = talentSpec.at("name");
        Terminal::Print(27, 1, name);

        int diff = talentSpec.at("difficulty");
        std::string difficulty = "";
        for (int i = 0; i < diff; i++)
        {
            difficulty += "* ";
        }

        Terminal::Print(27, 2, "Difficulty: " + difficulty);

        std::string desc = talentSpec.at("description");
        auto wrapDesc = Terminal::WrapText(desc, 80);

        for (int i = 0; i < wrapDesc.num; i++)
        {
            Terminal::Print(27, 4 + i, wrapDesc.lines[i]);
        }

        return 4 + wrapDesc.num;
    }

    int Talent::RenderStrengths(int offset)
    {
        auto talentSpec = m_TalentList[m_Selected];

        Terminal::SetForegroundColor(WHITE);
        Terminal::Print(27, offset + 1, "Strengths");

        auto strengths = talentSpec.at("strengths");
        int y = offset + 2;

        for (const auto& s : strengths)
        {
            Terminal::SetForegroundColor(GREEN);
            Terminal::Print(27 + 4, y, s.at("name"));

            Terminal::SetForegroundColor(GRAY);
            std::string desc = s.at("description");
            auto wrapped = Terminal::WrapText(desc, 60);
            for (int j = 0; j < wrapped.num; ++j)
            {
                Terminal::Print(27 + 4, y + j + 1, wrapped.lines[j]);
            }

            y += 1 + wrapped.num;
        }

        return y;
    }

    int Talent::RenderWeaknesses(int offset)
    {
        auto talentSpec = m_TalentList[m_Selected];

        // Title
        Terminal::SetForegroundColor(WHITE);
        Terminal::Print(27, offset + 1, "Weaknesses");

        auto weaknesses = talentSpec.at("weaknesses");
        int y = offset + 2;

        for (const auto& w : weaknesses)
        {
            // Draw weakness name
            Terminal::SetForegroundColor(RED);
            Terminal::Print(31, y, w.at("name"));

            // Draw its description underneath
            Terminal::SetForegroundColor(GRAY);
            std::string desc = w.at("description");
            auto wrapped = Terminal::WrapText(desc, 50);
            for (int j = 0; j < wrapped.num; ++j)
            {
                Terminal::Print(31, y + j + 1, wrapped.lines[j]);
            }

            // Advance y by lines used (name + description)
            y += 1 + wrapped.num;
        }

        return y;
    }

    int Talent::RenderFlavor(int offset)
    {
        auto talentSpec = m_TalentList[m_Selected];
        Terminal::SetForegroundColor(GRAY);

        auto flavor = talentSpec.at("flavor");
        auto flavorWrapped = Terminal::WrapText(flavor, 80);

        for (int i = 0; i < flavorWrapped.num; i++)
        {
            Terminal::Print(27, offset + 2 + i, flavorWrapped.lines[i]);
        }
        return 0;
    }

    void Talent::Update()
    {
        if (IsKeyPressed(KEY_J))
        {
            m_Selected = Clamp(m_Selected + 1, 0, m_TalentList.size() - 1);
        }
        if (IsKeyPressed(KEY_K))
        {
            m_Selected = Clamp(m_Selected - 1, 0, m_TalentList.size() - 1);
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            m_Registry->Attach(ID::GetPlayerID(), Components::Character::TalentComponent{.talentName = m_TalentList[m_Selected].at("name").get<std::string>()});
            m_ScreenManager->Replace(std::make_shared<Confirm>());
        }
    }
}
