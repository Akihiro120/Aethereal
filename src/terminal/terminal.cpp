#include "terminal.h"
#include <clocale>
#include <vector>
#include <string>
#include <ncpp/NotCurses.hh>
#include "../utility/logging.h"

static ncpp::NotCurses s_Curses;
static ncpp::Plane* s_Plane;

// input
static std::vector<char> s_PolledInputs;

namespace Aethereal
{
    void Terminal::Open()
    {
        // std::setlocale(LC_ALL, "");
        Utility::Logging::LOG("Loaded NotCurses Version: " + std::string(s_Curses.version()));
        s_Curses.s_Plane = s_Curses.get_stdplane();
    }

    void Terminal::Close()
    {
        s_Curses.stop();
    }

    void Terminal::Print(int x, int y, const std::string& str)
    {
        s_Plane->putstr(x, y, str.c_str());
    }

    void Terminal::Put(int x, int y, int code)
    {
        s_Plane->putwch(x, y, (char) code);
    }

    void Terminal::Poll()
    {
        s_PolledInputs.clear();
    }

    void Terminal::Clear()
    {
        s_Plane->erase();
    }

    void Terminal::Refresh()
    {
        s_Curses.render();
    }
}
