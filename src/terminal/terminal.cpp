#include "terminal.h"
#include <vector>
#include <string>
#include "../utility/logging.h"

// STATIC MEMBERS
static int s_ConsoleWidth = 160;
static int s_ConsoleHeight = 50;

// IMPLEMENTATION
namespace Aethereal
{
    void Terminal::Open()
    {
<<<<<<< HEAD
        Utility::Logging::LOG("Aethereal Terminal Began Instance");
=======
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
>>>>>>> parent of 4452e5f (did some stuff)
    }

    void Terminal::Close()
    {
<<<<<<< HEAD
=======
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
>>>>>>> parent of 4452e5f (did some stuff)
    }

    void Terminal::Print(int x, int y, const std::string& str)
    {
    }

    void Terminal::Put(int x, int y, int code)
    {
    }

    void Terminal::Poll()
    {
    }

    void Terminal::Clear()
    {
    }

    void Terminal::Refresh()
    {
    }
}
