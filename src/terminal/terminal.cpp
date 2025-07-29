#include "terminal.h"
#include "../data/enums/unicodes.h"
#include "raylib.h"
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace Aethereal
{
    // Config::Builder implementation (outside the struct to avoid incomplete type issues)
    int Terminal::GetIndex(int x, int y) const
    {
        return y * m_Columns + x;
    }

    void Terminal::Open(const Config& config)
    {
        m_WindowWidth = config.windowWidth;
        m_WindowHeight = config.windowHeight;
        m_Columns = config.columns;
        m_Rows = config.rows;
        m_FontPath = config.fontPath;

        int fontSizeX = m_WindowWidth / m_Columns;
        int fontSizeY = m_WindowHeight / m_Rows;
        m_FontSize = std::min(fontSizeX, fontSizeY);

        m_Codepoints.clear();
        for (int i = 0; i < 127; ++i)
        {
            m_Codepoints.push_back(i);
        }

        LoadFont(m_FontPath);

        float scaleX = (float) m_WindowWidth / (m_CellWidth * m_Columns);
        float scaleY = (float) m_WindowHeight / (m_CellHeight * m_Rows);
        float scale = std::min(scaleX, scaleY);
        m_FontSize = std::max(1, (int) std::floor(m_FontSize * scale));

        m_Built = false;
        LoadFont(m_FontPath); // Rebuild with scaled font size

        int perfectW = m_Columns * m_CellWidth;
        int perfectH = m_Rows * m_CellHeight;
        SetWindowSize(perfectW, perfectH);
        m_WindowWidth = perfectW;
        m_WindowHeight = perfectH;

        m_Cells.assign(m_Columns * m_Rows, {' '});
    }

    void Terminal::Close()
    {
        m_Cells.clear();
        UnloadFont(m_Font);
    }

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

            if (bytesConsumed <= 0)
                break;

            Put(cx++, y, codepoint);
            offset += bytesConsumed;
        }
    }

    void Terminal::Put(int x, int y, int code)
    {
        if (x < 0 || y < 0 || x >= m_Columns || y >= m_Rows)
            return;

        if (m_GlyphCache.find(code) == m_GlyphCache.end() &&
            std::find(m_NewCodepoints.begin(), m_NewCodepoints.end(), code) == m_NewCodepoints.end())
        {
            m_NewCodepoints.push_back(code);
        }

        m_Cells[GetIndex(x, y)] = {
            .fg = m_ForegroundColor,
            .bg = m_BackgroundColor,
            .codepoint = code,
        };
    }

    void Terminal::Clear()
    {
        m_BackgroundColor = BLACK;
        m_ForegroundColor = WHITE;

        for (auto& cell : m_Cells)
        {
            cell = {' '};
        }
    }

    void Terminal::SetBackgroundColor(Color color)
    {
        m_BackgroundColor = color;
    }

    void Terminal::SetForegroundColor(Color color)
    {
        m_ForegroundColor = color;
    }

    void Terminal::Refresh()
    {
        RebuildFont();

        Vector2 dpi = m_UseDPIScaling ? GetWindowScaleDPI() : Vector2{1.0f, 1.0f};
        float dpiscale = std::max(dpi.x, dpi.y);
        float invScale = 1.0f / dpiscale;

        for (int y = 0; y < m_Rows; ++y)
        {
            for (int x = 0; x < m_Columns; ++x)
            {
                Cell cell = m_Cells[GetIndex(x, y)];
                int cellX = x * m_CellWidth;
                int cellY = y * m_CellHeight;

                DrawRectangle(cellX, cellY, m_CellWidth, m_CellHeight, cell.bg);

                if (cell.codepoint == 0)
                    continue;

                int cp = cell.codepoint;
                auto it = m_GlyphCache.find(cp);
                if (it == m_GlyphCache.end())
                    it = m_GlyphCache.find('?');
                if (it == m_GlyphCache.end())
                    continue;

                const GlyphMetrics& m = it->second;

                float penX = cellX + (m_CellWidth - m.advanceX * invScale) * 0.5f;
                float penY = cellY + m_BaselineOffset;

                Rectangle dest = {
                    penX + m.offset.x * invScale,
                    penY + m.offset.y * invScale,
                    m.size.x * invScale,
                    m.size.y * invScale};

                DrawTexturePro(m_Atlas, m.srcRect, dest, {0, 0}, 0.0f, cell.fg);
            }
        }
    }

    int Terminal::Width() const
    {
        return m_Columns;
    }
    int Terminal::Height() const
    {
        return m_Rows;
    }

    void Terminal::LoadFont(const std::string& fontPath)
    {
        for (int cp : m_NewCodepoints)
        {
            if (std::find(m_Codepoints.begin(), m_Codepoints.end(), cp) == m_Codepoints.end())
                m_Codepoints.push_back(cp);
        }

        Vector2 dpi = m_UseDPIScaling ? GetWindowScaleDPI() : Vector2{1.0f, 1.0f};
        float dpiScale = std::max(dpi.x, dpi.y);

        m_Font = LoadFontEx(fontPath.c_str(), std::ceil(m_FontSize * dpiScale), m_Codepoints.data(), m_Codepoints.size());
        SetTextureFilter(m_Font.texture, TEXTURE_FILTER_POINT);
        m_Atlas = m_Font.texture;

        m_GlyphCache.clear();
        float maxAdvance = 0.0f, maxAscent = 0.0f, maxDescent = 0.0f;

        for (int i = 0; i < m_Codepoints.size(); ++i)
        {
            GlyphInfo& g = m_Font.glyphs[i];
            int cp = g.value;

            GlyphMetrics m;
            m.srcRect = GetGlyphAtlasRec(m_Font, cp);
            m.offset = {(float) g.offsetX, (float) g.offsetY};
            m.size = {m.srcRect.width, m.srcRect.height};
            m.advanceX = (float) g.advanceX;

            m_GlyphCache[cp] = m;
            m_CodepointToIndex[cp] = i;

            maxAdvance = std::max(maxAdvance, m.advanceX);
            maxAscent = std::max(maxAscent, -m.offset.y);
            maxDescent = std::max(maxDescent, m.srcRect.height + m.offset.y);
        }

        if (m_NewCodepoints.empty() && !m_Built)
        {
            m_CellWidth = (int) std::ceil(maxAdvance / dpiScale);
            m_CellHeight = (int) std::ceil((maxAscent + maxDescent) / dpiScale);
            m_BaselineOffset = std::ceil(maxAscent / dpiScale);
            m_Built = true;
        }

        m_NewCodepoints.clear();
    }

    void Terminal::RebuildFont()
    {
        if (!m_NewCodepoints.empty())
        {
            UnloadFont(m_Font);
            LoadFont(m_FontPath);
        }
    }

    using namespace Enum::Unicode;

    void Terminal::DrawBox(int x, int y, int width, int height, BoxStyle style)
    {
        int codeHorizontal = style == BoxStyle::HEAVY ? (int) BoxHeavy::HORIZONTAL : (int) BoxLight::HORIZONTAL;
        int codeVertical = style == BoxStyle::HEAVY ? (int) BoxHeavy::VERTICAL : (int) BoxLight::VERTICAL;

        for (int bx = 0; bx < width; ++bx)
        {
            Put(x + bx, y, codeHorizontal);
            Put(x + bx, y + height, codeHorizontal);
        }

        for (int by = 0; by < height; ++by)
        {
            Put(x, y + by, codeVertical);
            Put(x + width, y + by, codeVertical);
        }

        int topLeft = style == BoxStyle::HEAVY ? (int) BoxHeavy::TOP_LEFT : (int) BoxLight::TOP_LEFT;
        int topRight = style == BoxStyle::HEAVY ? (int) BoxHeavy::TOP_RIGHT : (int) BoxLight::TOP_RIGHT;
        int bottomLeft = style == BoxStyle::HEAVY ? (int) BoxHeavy::BOTTOM_LEFT : (int) BoxLight::BOTTOM_LEFT;
        int bottomRight = style == BoxStyle::HEAVY ? (int) BoxHeavy::BOTTOM_RIGHT : (int) BoxLight::BOTTOM_RIGHT;

        Put(x, y, topLeft);
        Put(x + width, y, topRight);
        Put(x, y + height, bottomLeft);
        Put(x + width, y + height, bottomRight);
    }

    Terminal::TextWrap Terminal::WrapText(const std::string& s, int wrapSize) const
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
                line += ' ';
            line += word;
        }

        if (!line.empty())
            wrap.lines.push_back(line);

        wrap.num = (int) wrap.lines.size();
        return wrap;
    }

    void Terminal::ToggleDPIScaling(bool active)
    {
        m_UseDPIScaling = active;
    }

} // namespace Aethereal
