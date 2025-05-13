#pragma once
#include <string>

namespace Aethereal
{
    class Terminal
    {
    public:
        static void Open();
        static void Close();

        static void Print(int x, int y, const std::string& str);
        static void Put(int x, int y, int code);

        static void Clear();
        static void Poll();
        static void Refresh();

    private:
        Terminal() = default;
    };
}
