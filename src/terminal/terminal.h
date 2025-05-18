#pragma once
#include <string>
#include <raylib.h>

namespace Aethereal
{
    class Terminal
    {
    public:
        struct TerminalConfig
        {
            int windowWidth;
            int windowHeight;
            int columns;
            int rows;
            std::string fontPath;
        };

        struct Cell
        {
            Color fg, bg;
            int codepoint;
        };

        struct GlyphMetrics
        {
            Rectangle srcRect;
            Vector2 offset;
            Vector2 size;
            float advanceX;
        };

        // Terminal Operations.
        static void Open(const TerminalConfig& config);
        static void Close();

        static void Print(int x, int y, const std::string& str);
        static void Put(int x, int y, int code);

        static void Clear();
        static void Refresh();

        static void SetForegroundColor(Color col);
        static void SetBackgroundColor(Color col);

        static int Width();
        static int Height();

        enum class BoxStyle
        {
            LIGHT,
            HEAVY
        };

        // Drawing operations
        static void DrawBox(int x, int y, int width, int height, const BoxStyle& style);

    private:
        static void LoadFont(const std::string& path);
        static void RebuildFont();
        inline static int GetIndex(int x, int y);
    };
}
