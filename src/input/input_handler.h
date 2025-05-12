#pragma once
#include <raylib.h>
#include <string>

namespace Aethereal::Input
{
    inline void GetKeyboardInput(std::string* str)
    {
        if (IsKeyPressed(KEY_BACKSPACE) && !str->empty())
        {
            str->pop_back();
        }

        int code = GetCharPressed();
        while (code > 0)
        {
            if ((code >= '0' && code <= '9') ||
                (code >= 'A' && code <= 'Z') ||
                (code >= 'a' && code <= 'z') ||
                (code == ' '))
            {
                str->push_back(char(code));
            }
            code = GetCharPressed();
        }
    }
}
