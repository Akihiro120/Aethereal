#pragma once
#include "../terminal/terminal.h"
#include "../data/enums/unicodes.h"
#include <vector>
#include <string>
#include <sstream>

using namespace Aethereal::Enum::Unicode;

namespace Aethereal::Utility::Drawing
{
    // BOX OPERATIONS -----------------------------------------------------------------------
    namespace Box
    {
        struct BoxDimensions
        {
            int x;
            int y;
            int width;
            int height;
        };

        enum class BoxFillMode
        {
            FILL,
            LINE
        };

        enum class BoxLineStyle
        {
            LIGHT,
            HEAVY
        };

        struct BoxStyle
        {
            BoxFillMode fillMode = BoxFillMode::LINE;
            BoxLineStyle lineStyle = BoxLineStyle::HEAVY;
        };

        // Draw box
        inline void DrawBox(const BoxDimensions& box, const BoxStyle& style = {})
        {
            if (style.fillMode == BoxFillMode::FILL)
            {
                // draw empty box
                for (int y = 0; y < box.height; y++)
                {
                    for (int x = 0; x < box.width; x++)
                    {
                        Terminal::Put(box.x + x, box.y + y, ' ');
                    }
                }
            }
            else
            {
                // horizontal lines
                auto codeHorizontal = style.lineStyle == BoxLineStyle::HEAVY ? (int) BoxHeavy::HORIZONTAL : (int) BoxLight::HORIZONTAL;
                for (int x = 0; x < box.width; x++)
                {
                    Terminal::Put(x + box.x, box.y, (int) codeHorizontal);
                    Terminal::Put(x + box.x, box.y + box.height, (int) codeHorizontal);
                }

                // vertical lines
                auto codeVertical = style.lineStyle == BoxLineStyle::HEAVY ? (int) BoxHeavy::VERTICAL : (int) BoxLight::VERTICAL;
                for (int y = 0; y < box.height; y++)
                {
                    Terminal::Put(box.x, y + box.y, (int) codeVertical);
                    Terminal::Put(box.x + box.width, y + box.y, (int) codeVertical);
                }

                // Choose the correct corner characters for the current style.
                int topLeft = style.lineStyle == BoxLineStyle::HEAVY ? (int) BoxHeavy::TOP_LEFT : (int) BoxLight::TOP_LEFT;
                int topRight = style.lineStyle == BoxLineStyle::HEAVY ? (int) BoxHeavy::TOP_RIGHT : (int) BoxLight::TOP_RIGHT;
                int bottomLeft = style.lineStyle == BoxLineStyle::HEAVY ? (int) BoxHeavy::BOTTOM_LEFT : (int) BoxLight::BOTTOM_LEFT;
                int bottomRight = style.lineStyle == BoxLineStyle::HEAVY ? (int) BoxHeavy::BOTTOM_RIGHT : (int) BoxLight::BOTTOM_RIGHT;

                // Draw corners using Terminal::Put.
                Terminal::Put(box.x, box.y, topLeft);
                Terminal::Put(box.x + box.width, box.y, topRight);
                Terminal::Put(box.x, box.y + box.height, bottomLeft);
                Terminal::Put(box.x + box.width, box.y + box.height, bottomRight);
            }
        }
    }

    // TEXT OPERATIONS -----------------------------------------------------------------------
    namespace Text
    {
        struct WrappedText
        {
            std::vector<std::string> lines;
            uint32_t amount;
        };

        inline WrappedText WrapText(const std::string& s, int wrapSize)
        {
            std::istringstream iss(s);
            std::string word, line;
            WrappedText wrap;

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
            wrap.amount = wrap.lines.size();

            return wrap;
        }
    }
}
