// src/sl/core/Log.cpp

#include <cstdint>
#include <format>
#include <iostream>

#include "sl/String.hpp"
#include "sl/Traits.hpp"

#include "sl/core/Log.hpp"

namespace sl::core
{
    static void WriteToDisk(const String&)
    {
        // TODO: Here
    }
}

// TODO: Figure out how to print in color (Will have to be platform specific)
namespace sl::core
{
    static void PrintDebug(const String& message)
    {
        // TODO: Add output option
        std::cout << "[DEBUG] " << message << '\n';
        // TODO: Write out to disk
        // WriteToDisk(...);
    }

    static void PrintSuccess(const String& message)
    {
        // TODO: Add output option
        std::cout << "[SUCCESS] " << message << '\n';
        // TODO: Write out to disk
        // WriteToDisk(...);
    }

    static void PrintWarning(const String& message)
    {
        // TODO: Add output option
        std::cout << "[WARNING] " << message << '\n';
        // TODO: Write out to disk
        // WriteToDisk(...);
    }

    static void PrintError(const String& message)
    {
        // TODO: Add output option
        std::cerr << "[ERROR] " << message << '\n';
        // TODO: Write out to disk
        // WriteToDisk(...);
    }

    static void PrintFatal(const String& message)
    {
        // TODO: Add output option
        std::cerr << "[FATAL] " << message << '\n';
        // TODO: Write out to disk
        // WriteToDisk(...);
    }

    static void PrintMessage(const String& message)
    {
        // TODO: Add output option
        std::cout << message << '\n';
        // TODO: Write out to disk
        // WriteToDisk(...);
    }
}

namespace sl::core
{
    void Log::Print(LogLevel level, const String& message)
    {
        switch (level) { using enum LogLevel;
            case eDebug:
#if defined(_DEBUG)
                PrintDebug(message);
#endif
                break;
            case eSuccess:
                PrintSuccess(message);
                break;
            case eWarning:
                PrintWarning(message);
                break;
            case eError:
                PrintError(message);
                break;
            case eFatal:
                PrintFatal(message);
                break;
            case eMessage:
                PrintMessage(message);
                break;
        };
    }
}
