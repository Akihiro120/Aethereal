#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <raylib.h>

namespace Aethereal
{
    class Terminal
    {
    public:
        // Configuration for terminal setup
        struct Config
        {
            int windowWidth = 800;
            int windowHeight = 600;
            int columns = 80;
            int rows = 25;
            std::string fontPath;
        };

        // Terminal cell data
        struct Cell
        {
            Color fg = WHITE;
            Color bg = BLACK;
            int codepoint = ' ';
        };

        // Glyph rendering data
        struct GlyphMetrics
        {
            Rectangle srcRect{};
            Vector2 offset{};
            Vector2 size{};
            float advanceX = 0.0f;
        };

        // Text wrapping result
        struct TextWrap
        {
            std::vector<std::string> lines;
            int num = 0;
        };

        // Box drawing styles
        enum class BoxStyle
        {
            LIGHT,
            HEAVY
        };

    public:
        // Terminal operations
        void Open(const Config& config);
        void Close();

        void Clear();
        void Refresh();

        void Print(int x, int y, const std::string& str);
        void Put(int x, int y, int code);

        void SetForegroundColor(Color color);
        void SetBackgroundColor(Color color);
        void ToggleDPIScaling(bool enabled);

        int Width() const;
        int Height() const;

        TextWrap WrapText(const std::string& str, int wrap) const;
        void DrawBox(int x, int y, int width, int height, BoxStyle style);

    private:
        // Internal helpers
        void LoadFont(const std::string& path);
        void RebuildFont();
        int GetIndex(int x, int y) const;

    private:
        // Configuration and layout
        int m_WindowWidth = 0;
        int m_WindowHeight = 0;
        int m_Columns = 0;
        int m_Rows = 0;
        int m_CellWidth = 0;
        int m_CellHeight = 0;
        float m_FontSize = 0.0f;
        float m_BaselineOffset = 0.0f;
        bool m_UseDPIScaling = true;
        bool m_Built = false;

        // State
        Color m_ForegroundColor = WHITE;
        Color m_BackgroundColor = BLACK;

        std::string m_FontPath;
        Font m_Font{};
        Texture2D m_Atlas{};

        std::vector<Cell> m_Cells;
        std::vector<int> m_Codepoints;
        std::vector<int> m_NewCodepoints;

        std::unordered_map<int, GlyphMetrics> m_GlyphCache;
        std::unordered_map<int, int> m_CodepointToIndex;
    };
}
