#include "species.h"
#include "../../../utility/drawing.h"

using namespace Aethereal::Utility::Drawing;

namespace Aethereal::Screen::MainMenu
{
    Species::Species() : m_ScreenManager(*GetInjection<ScreenManager>()),
                         m_ECS(*GetInjection<FECS::Registry>()),
                         m_Database(*GetInjection<Database>())
    {
    }

    void Species::Render()
    {
        Terminal::SetForegroundColor(WHITE);

        // Option Box
        Terminal::SetBackgroundColor(GRAY);
        Box::DrawBox(Box::BoxDimensions{
            .x = 0,
            .y = 0,
            .width = 20,
            .height = (int) Terminal::GetHeight() - 1});

        Terminal::Print(1, 0, "Select your Species");

        // Description Box
        Box::DrawBox(Box::BoxDimensions{
            .x = 21,
            .y = 0,
            .width = (int) Terminal::GetWidth() - 22,
            .height = (int) Terminal::GetHeight() - 1});
    }

    void Species::Update()
    {
    }
}
