#include "terminal.h"
#include "../utility/logging.h"
#include "../data/enums/unicodes.h"
#include "raylib.h"
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <iostream>

namespace Aethereal
{

    // Terminal state variables
    static int s_WindowWidth = 0;
    static int s_WindowHeight = 0;
    static int s_Columns = 0;
    static int s_Rows = 0;
    static int s_CellWidth = 0;
    static int s_CellHeight = 0;
    static float s_FontSize = 0.0f;
    static bool s_UseDPIScaling = false;

    static Color s_BackgroundColor = BLACK;
    static Color s_ForegroundColor = WHITE;

    static Font s_Font;
    static Texture2D s_Atlas;
    static std::string s_FontPath;
    static std::vector<int> s_Codepoints;
    static std::vector<int> s_NewCodepoints;
    static std::vector<Terminal::Cell> s_Cells;
    static std::unordered_map<int, Terminal::GlyphMetrics> s_GlyphCache;
    static std::unordered_map<int, int> s_CodepointToIndex;
    static float s_BaselineOffset = 0.0f;
    static bool s_Built = false;

    // Internal utility
    inline int Terminal::GetIndex(int x, int y)
    {
        return y * s_Columns + x;
    }

    // Terminal initialization
    void Terminal::Open(const TerminalConfig& config)
    {
        s_WindowWidth = config.windowWidth;
        s_WindowHeight = config.windowHeight;
        s_Columns = config.columns;
        s_Rows = config.rows;
        s_FontPath = config.fontPath;

        if (s_UseDPIScaling)
            SetConfigFlags(FLAG_WINDOW_HIGHDPI);

        SetTraceLogLevel(TraceLogLevel::LOG_NONE);
        InitWindow(s_WindowWidth, s_WindowHeight, "Aethereal");
        SetTargetFPS(60);

        // Estimate an initial font size to fill the window
        int fontSizeX = s_WindowWidth / s_Columns;
        int fontSizeY = s_WindowHeight / s_Rows;
        s_FontSize = std::min(fontSizeX, fontSizeY);

        // Preload ASCII characters
        s_Codepoints.clear();
        for (int i = 0; i < 127; ++i)
        {
            s_Codepoints.push_back(i);
        }
        // s_Codepoints.push_back(0x20);

        LoadFont(s_FontPath);

        // Adjust font size to fit window exactly
        float scaleX = (float) s_WindowWidth / (s_CellWidth * s_Columns);
        float scaleY = (float) s_WindowHeight / (s_CellHeight * s_Rows);
        float scale = std::min(scaleX, scaleY);
        s_FontSize = std::max(1, (int) std::floor(s_FontSize * scale));

        s_Built = false;
        LoadFont(s_FontPath); // Reload to apply scale

        // Resize window to match exact terminal grid
        int perfectW = s_Columns * s_CellWidth;
        int perfectH = s_Rows * s_CellHeight;
        SetWindowSize(perfectW, perfectH);
        s_WindowWidth = perfectW;
        s_WindowHeight = perfectH;

        s_Cells.assign(s_Columns * s_Rows, {' '});
    }

    // Shutdown and cleanup
    void Terminal::Close()
    {
        s_Cells.clear();
        UnloadFont(s_Font);
        CloseWindow();
    }

    // Print a string starting at (x, y)
    void Terminal::Print(int x, int y, const std::string& str)
    {
        int cx = x;
        const char* text = str.c_str();
        int length = (int) str.size();
        int offset = 0;

        while (offset < length)
        {
            int bytesConsumed = 0;
            int codepoint = GetCodepoint(text + offset, &bytesConsumed);

            // safety guard against malformed UTF-8
            if (bytesConsumed <= 0)
                break;

            Put(cx++, y, codepoint);
            offset += bytesConsumed;
        }
    }

    // Put a single character/codepoint at (x, y)
    void Terminal::Put(int x, int y, int code)
    {
        if (x < 0 || y < 0 || x >= s_Columns || y >= s_Rows)
            return;

        if (s_GlyphCache.find(code) == s_GlyphCache.end() &&
            std::find(s_NewCodepoints.begin(), s_NewCodepoints.end(), code) == s_NewCodepoints.end())
        {
            s_NewCodepoints.push_back(code);
        }

        s_Cells[GetIndex(x, y)] = {
            .fg = s_ForegroundColor,
            .bg = s_BackgroundColor,
            .codepoint = code,
        };
    }

    // Clear all terminal cells
    void Terminal::Clear()
    {
        s_BackgroundColor = BLACK;
        s_ForegroundColor = WHITE;
        for (auto& cell : s_Cells)
        {
            cell = {' '};
        }
    }

    // Set the default background color
    void Terminal::SetBackgroundColor(Color color)
    {
        s_BackgroundColor = color;
    }

    // Set the default foreground (text) color
    void Terminal::SetForegroundColor(Color col)
    {
        s_ForegroundColor = col;
    }

    // Draw all terminal cells
    void Terminal::Refresh()
    {
        RebuildFont();

        BeginDrawing();
        ClearBackground(BLACK);

        Vector2 dpi = s_UseDPIScaling ? GetWindowScaleDPI() : Vector2{1.0f, 1.0f};
        float dpiscale = std::max(dpi.x, dpi.y);
        float invScale = 1.0f / dpiscale;

        for (int y = 0; y < s_Rows; ++y)
        {
            for (int x = 0; x < s_Columns; ++x)
            {
                Cell cell = s_Cells[GetIndex(x, y)];
                int cellX = x * s_CellWidth;
                int cellY = y * s_CellHeight;

                DrawRectangle(cellX, cellY, s_CellWidth, s_CellHeight, cell.bg);

                if (cell.codepoint == 0)
                    continue;

                int cp = cell.codepoint;
                auto it = s_GlyphCache.find(cp);
                if (it == s_GlyphCache.end())
                    it = s_GlyphCache.find('?');
                if (it == s_GlyphCache.end())
                    continue;

                const GlyphMetrics& m = it->second;

                float penX = cellX + (s_CellWidth - m.advanceX * invScale) * 0.5f;
                float penY = cellY + s_BaselineOffset;

                Rectangle dest = {
                    penX + m.offset.x * invScale,
                    penY + m.offset.y * invScale,
                    m.size.x * invScale,
                    m.size.y * invScale};

                DrawTexturePro(s_Atlas, m.srcRect, dest, {0, 0}, 0.0f, cell.fg);
            }
        }

        EndDrawing();
    }

    // Terminal dimensions
    int Terminal::Width()
    {
        return s_Columns - 1;
    }
    int Terminal::Height()
    {
        return s_Rows - 1;
    }

    // Load the font and cache glyph metrics
    void Terminal::LoadFont(const std::string& fontPath)
    {
        for (int cp : s_NewCodepoints)
        {
            if (std::find(s_Codepoints.begin(), s_Codepoints.end(), cp) == s_Codepoints.end())
            {
                s_Codepoints.push_back(cp);
                Utility::Logging::LOG("Added codepoint " + std::to_string(cp));
            }
        }

        Vector2 dpi = s_UseDPIScaling ? GetWindowScaleDPI() : Vector2{1.0f, 1.0f};
        float dpiScale = std::max(dpi.x, dpi.y);
        s_Font = LoadFontEx(fontPath.c_str(), std::ceil(s_FontSize * dpiScale), s_Codepoints.data(), s_Codepoints.size());
        SetTextureFilter(s_Font.texture, TEXTURE_FILTER_POINT);
        s_Atlas = s_Font.texture;

        s_GlyphCache.clear();
        float maxAdvance = 0.0f, maxAscent = 0.0f, maxDescent = 0.0f;

        for (int i = 0; i < s_Codepoints.size(); ++i)
        {
            GlyphInfo& g = s_Font.glyphs[i];
            int cp = g.value;

            GlyphMetrics m;
            m.srcRect = GetGlyphAtlasRec(s_Font, cp);
            m.offset = {(float) g.offsetX, (float) g.offsetY};
            m.size = {m.srcRect.width, m.srcRect.height};
            m.advanceX = (float) g.advanceX;

            s_GlyphCache[cp] = m;
            s_CodepointToIndex[cp] = i;

            maxAdvance = std::max(maxAdvance, m.advanceX);
            maxAscent = std::max(maxAscent, -m.offset.y);
            maxDescent = std::max(maxDescent, m.srcRect.height + m.offset.y);
        }

        if (s_NewCodepoints.empty() && !s_Built)
        {
            s_CellWidth = (int) std::ceil(maxAdvance / dpiScale);
            s_CellHeight = (int) std::ceil((maxAscent + maxDescent) / dpiScale);
            s_BaselineOffset = std::ceil(maxAscent / dpiScale);
            Utility::Logging::LOG("Rebuilt Cell Dimensions");
            s_Built = true;
        }
        s_NewCodepoints.clear();
    }

    // Rebuild font if new glyphs were added
    void Terminal::RebuildFont()
    {
        if (!s_NewCodepoints.empty())
        {
            UnloadFont(s_Font);
            LoadFont(s_FontPath);
        }
    }

    using namespace Enum::Unicode;
    void Terminal::DrawBox(int x, int y, int width, int height, const BoxStyle& style)
    {
        // horizontal lines
        auto codeHorizontal = style == BoxStyle::HEAVY ? (int) BoxHeavy::HORIZONTAL : (int) BoxLight::HORIZONTAL;
        for (int bx = 0; bx < width; bx++)
        {
            Terminal::Put(x + bx, y, (int) codeHorizontal);
            Terminal::Put(x + bx, y + height, (int) codeHorizontal);
        }

        // vertical lines
        auto codeVertical = style == BoxStyle::HEAVY ? (int) BoxHeavy::VERTICAL : (int) BoxLight::VERTICAL;
        for (int by = 0; by < height; by++)
        {
            Terminal::Put(x, y + by, (int) codeVertical);
            Terminal::Put(x + width, y + by, (int) codeVertical);
        }

        // Choose the correct corner characters for the current style.
        int topLeft = style == BoxStyle::HEAVY ? (int) BoxHeavy::TOP_LEFT : (int) BoxLight::TOP_LEFT;
        int topRight = style == BoxStyle::HEAVY ? (int) BoxHeavy::TOP_RIGHT : (int) BoxLight::TOP_RIGHT;
        int bottomLeft = style == BoxStyle::HEAVY ? (int) BoxHeavy::BOTTOM_LEFT : (int) BoxLight::BOTTOM_LEFT;
        int bottomRight = style == BoxStyle::HEAVY ? (int) BoxHeavy::BOTTOM_RIGHT : (int) BoxLight::BOTTOM_RIGHT;

        // Draw corners using Terminal::Put.
        Terminal::Put(x, y, topLeft);
        Terminal::Put(x + width, y, topRight);
        Terminal::Put(x, y + height, bottomLeft);
        Terminal::Put(x + width, y + height, bottomRight);
    }

    Terminal::TextWrap Terminal::WrapText(const std::string& s, int wrapSize)
    {
        std::istringstream iss(s);
        std::string word, line;
        TextWrap wrap;

        while (iss >> word)
        {
            if (line.size() + word.size() + (line.empty() ? 0 : 1) > wrapSize)
            {
                wrap.lines.push_back(line);
                line.clear();
            }

            if (!line.empty())
            {
                line += ' ';
            }
            line += word;
        }

        if (!line.empty())
        {
            wrap.lines.push_back(line);
        }
        wrap.num = wrap.lines.size();

        return wrap;
    }
} // namespace Aethereal
