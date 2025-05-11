#pragma once
#include <raylib.h>
#include <string>

namespace Aethereal
{
    struct TerminalCreateInfo
    {
        uint32_t width;
        uint32_t height;
        uint32_t fontSize;
        std::string title;
        std::string fontPath;
    };

    class Terminal
    {
    public:
        struct Cell
        {
            int code = ' ';
            Color bgColor = BLACK;
            Color fgColor = WHITE;
        };

        static bool Open(const TerminalCreateInfo& info);
        static bool IsWindowOpen();
        static void Close();

        static void Clear();
        static void Refresh();

        static void Print(int x, int y, const std::string& str);
        static void Put(int x, int y, int codepoint);

        static void SetForegroundColor(Color color);
        static void SetBackgroundColor(Color color);

        static uint32_t GetWidth();
        static uint32_t GetHeight();

    private:
        static void OnWindowResized();
        static void RegenerateAtlas();

        Terminal();
        ~Terminal();
    };
}
