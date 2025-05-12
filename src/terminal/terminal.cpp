#include "terminal.h"
#include <iostream>
#include "raylib.h"
#include <algorithm>
#include <numeric>
#include <vector>
#include <unordered_map>
#include <cstdint>

namespace Aethereal
{
    // GLOBAL DEFINITIONS -------------------------------------
    static Font s_Font;
    static std::uint32_t s_Width, s_Height;
    static std::uint32_t s_FontSize;
    static std::uint32_t s_InitialFontSize;
    static std::string s_FontPath;
    static std::uint32_t s_InitialWidth, s_InitialHeight;

    static std::uint32_t s_CellWidth, s_CellHeight;

    // Codepoints
    static std::vector<int> s_Codepoints;
    static std::vector<int> s_NewCodepoints;
    static std::unordered_map<int, int> s_CodepointIndex;
    static bool s_Regenerate = false;

    // Buffers
    static std::vector<Terminal::Cell> s_Cells;
    static Color s_CurrentFGColor, s_CurrentBGColor;

    // TERMINAL -----------------------------------------------
    Terminal::Terminal()
    {
    }

    Terminal::~Terminal()
    {
    }

    bool Terminal::Open(const TerminalCreateInfo& info)
    {
        // Set the default colors for the Terminal
        s_CurrentBGColor = BLACK;
        s_CurrentFGColor = WHITE;

        s_Width = info.width;
        s_Height = info.height;
        s_FontPath = info.fontPath;
        s_FontSize = info.fontSize;

        // Init
        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
        InitWindow(1, 1, info.title.c_str());

        s_Codepoints.resize(256);
        std::iota(s_Codepoints.begin(), s_Codepoints.end(), 0);
        s_CodepointIndex.clear();
        for (int i = 0; i < 256; i++)
        {
            s_CodepointIndex[s_Codepoints[i]] = i;
        }
        int glyphCount = 256;

        s_Font = LoadFontEx(info.fontPath.c_str(), info.fontSize, s_Codepoints.data(), glyphCount);

        s_CellWidth = 0;
        s_CellHeight = 0;
        for (int i = 0; i < glyphCount; i++)
        {
            Rectangle r = s_Font.recs[i];
            auto& g = s_Font.glyphs[i];
            s_CellWidth = std::max((int) s_CellWidth, (int) g.advanceX);
            s_CellHeight = std::max((int) s_CellHeight, (int) r.height);
        }

        SetWindowSize(s_Width * s_CellWidth, s_Height * s_CellHeight);
        SetWindowPosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
        SetTargetFPS(60);

        s_InitialWidth = GetScreenWidth();
        s_InitialHeight = GetScreenHeight();
        s_InitialFontSize = info.fontSize;

        // Initialize buffers
        s_Cells.assign(s_Width * s_Height, Cell{});

        return true;
    }

    bool Terminal::IsWindowOpen()
    {
        return !WindowShouldClose();
    }

    void Terminal::Close()
    {
        UnloadFont(s_Font);
        CloseWindow();

        s_Cells.clear();
        s_Codepoints.clear();
        s_CodepointIndex.clear();
    }

    void Terminal::Clear()
    {
        // Clear the buffer
        for (auto& cell : s_Cells)
        {
            cell.code = ' ';
            cell.bgColor = BLACK;
            cell.fgColor = WHITE;
        }
    }

    void Terminal::Refresh()
    {
        if (IsWindowResized())
        {
            OnWindowResized();
        }

        // regenerate if needed
        RegenerateAtlas();

        BeginDrawing();
        ClearBackground(BLACK);

        for (int y = 0; y < s_Height; y++)
        {
            for (int x = 0; x < s_Width; x++)
            {
                int idx = y * s_Width + x;
                const Cell& cell = s_Cells[idx];

                // Background
                DrawRectangle(x * s_CellWidth, y * s_CellHeight, s_CellWidth, s_CellHeight, cell.bgColor);

                auto it = s_CodepointIndex.find(cell.code);
                if (it != s_CodepointIndex.end())
                {
                    Rectangle src = s_Font.recs[it->second];
                    auto& info = s_Font.glyphs[it->second];

                    float glyphWidth = src.width;
                    float glyphHeight = src.height;

                    float baselineY = y * s_CellHeight + (s_CellHeight - s_Font.baseSize) * 0.5f;
                    float dstY = baselineY + info.offsetY;

                    float dstX = x * s_CellWidth + (s_CellWidth - glyphWidth) * 0.5f;

                    Rectangle dst = {(float) dstX,
                                     (float) dstY,
                                     (float) glyphWidth,
                                     (float) glyphHeight};

                    DrawTexturePro(s_Font.texture, src, dst, {0, 0}, 0.0f, cell.fgColor);
                }
            }
        }

        EndDrawing();
    }

    void Terminal::RegenerateAtlas()
    {
        if (s_Regenerate)
        {
            // TODO: Optimize by allowing batching of codepoints: DONE!!!
            if (!s_NewCodepoints.empty())
            {
                for (int& code : s_NewCodepoints)
                {
                    s_Codepoints.push_back(code);
                }
            }

            // Regnerate atlas
            UnloadFont(s_Font);
            s_Font = LoadFontEx(s_FontPath.c_str(), s_FontSize, s_Codepoints.data(), (int) s_Codepoints.size());

            s_CodepointIndex.clear();
            for (int i = 0; i < (int) s_Codepoints.size(); i++)
            {
                s_CodepointIndex[s_Codepoints[i]] = i;
            }

            s_CellWidth = 0;
            s_CellHeight = 0;
            for (int i = 0; i < s_Codepoints.size(); i++)
            {
                Rectangle r = s_Font.recs[i];
                auto& g = s_Font.glyphs[i];
                s_CellWidth = std::max((int) s_CellWidth, (int) g.advanceX);
                s_CellHeight = std::max((int) s_CellHeight, (int) r.height);
            }

            s_Regenerate = false;
        }
    }

    void Terminal::Print(int x, int y, const std::string& str)
    {
        for (size_t i = 0; i < str.size(); i++)
        {
            unsigned char c = static_cast<unsigned char>(str[i]);
            Put(x + (int) i, y, c);
        }
    }

    void Terminal::Put(int x, int y, int codepoint)
    {
        if (x < 0 || x >= s_Width || y < 0 || y >= s_Height)
            return;
        int idx = y * s_Width + x;

        auto it = s_CodepointIndex.find(codepoint);
        if (it == s_CodepointIndex.end())
        {
            s_NewCodepoints.push_back(codepoint);
            s_Regenerate = true;
        }

        Cell& cell = s_Cells[idx];
        cell.code = codepoint;
        cell.bgColor = s_CurrentBGColor;
        cell.fgColor = s_CurrentFGColor;
    }

    void Terminal::SetBackgroundColor(Color color)
    {
        s_CurrentBGColor = color;
    }

    void Terminal::SetForegroundColor(Color color)
    {
        s_CurrentFGColor = color;
    }

    uint32_t Terminal::GetWidth()
    {
        return s_Width;
    }

    uint32_t Terminal::GetHeight()
    {
        return s_Height;
    }

    void Terminal::OnWindowResized()
    {
        // compute new font size relative to base
        int winW = GetScreenWidth();
        int winH = GetScreenHeight();
        float scale = std::min((float) winW / s_InitialWidth, (float) winH / s_InitialHeight);
        int newFontSize = std::max(1, (int) std::floor(s_InitialFontSize * scale));

        if (newFontSize != s_FontSize)
        {
            s_FontSize = newFontSize;
            s_Regenerate = true;
            RegenerateAtlas();
        }
    }
}
