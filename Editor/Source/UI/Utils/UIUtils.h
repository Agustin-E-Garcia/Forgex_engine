#pragma once
#include <cstddef>
#include <cstdio>
#include <string>

namespace Forgex::Editor::UI::Utils
{
    inline std::string FormatBytes(size_t bytes)
    {
        constexpr double KB = 1024.0;
        constexpr double MB = 1024.0 * KB;
        constexpr double GB = 1024.0 * MB;
        char buf[32];
        if      (bytes >= static_cast<size_t>(GB)) snprintf(buf, sizeof(buf), "%.2f GB", bytes / GB);
        else if (bytes >= static_cast<size_t>(MB)) snprintf(buf, sizeof(buf), "%.2f MB", bytes / MB);
        else if (bytes >= static_cast<size_t>(KB)) snprintf(buf, sizeof(buf), "%.2f KB", bytes / KB);
        else                                       snprintf(buf, sizeof(buf), "%zu B",   bytes);
        return buf;
    }
}
