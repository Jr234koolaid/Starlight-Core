// src/sl/Log.cpp

#include <cstdint>
#include <format>
#include <iostream>

#include "sl/Log.hpp"
#include "sl/Type.hpp"

namespace sl
{
    static void WriteToDisk(const String&)
    {
        // TODO: Here
    }
}

namespace sl
{
    static void WriteDebug(const String& message)
    {
        // TODO: Add output option
        std::cout << "DEBUG: " << message << '\n';
        // TODO: Write out to disk
        // WriteToDisk(...);
    }

    static void WriteSuccess(const String& message)
    {
        // TODO: Add output option
        std::cout << "SUCCESS: " << message << '\n';
        // TODO: Write out to disk
        // WriteToDisk(...);
    }

    static void WriteWarning(const String& message)
    {
        // TODO: Add output option
        std::cout << "WARNING: " << message << '\n';
        // TODO: Write out to disk
        // WriteToDisk(...);
    }

    static void WriteError(const String& message)
    {
        // TODO: Add output option
        std::cerr << "ERROR: " << message << '\n';
        // TODO: Write out to disk
        // WriteToDisk(...);
    }

    static void WriteFatal(const String& message)
    {
        // TODO: Add output option
        std::cerr << "FATAL: " << message << '\n';
        // TODO: Write out to disk
        // WriteToDisk(...);
    }

    static void WriteMessage(const String& message)
    {
        // TODO: Add output option
        std::cout << message << '\n';
        // TODO: Write out to disk
        // WriteToDisk(...);
    }
}

namespace sl
{
    void LogMessage(LogLevel level, const String& message)
    {
        switch (level) { using enum LogLevel;
        case LOG_DEBUG:
            WriteDebug(message);
            break;
        case LOG_SUCCESS:
            WriteSuccess(message);
            break;
        case LOG_WARNING:
            WriteWarning(message);
            break;
        case LOG_ERROR:
            WriteError(message);
            break;
        case LOG_FATAL:
            WriteFatal(message);
            break;
        case LOG_MESSAGE:
            WriteMessage(message);
            break;
        };
    }
}
