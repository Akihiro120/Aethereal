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
        Utility::Logging::LOG("Aethereal Terminal Began Instance");
    }

    void Terminal::Close()
    {
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
