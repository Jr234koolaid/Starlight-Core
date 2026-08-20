// src/sl/Log.cpp

#include <cstdint>
#include <format>
#include <iostream>

#include "sl\Type.hpp"
#include "sl\Log.hpp"

namespace sl
{
    void Log(LogLevel _level, const String& _fmessage)
    {
        // TODO: Write out to disk
        if (!_fmessage.empty())
        {
            using enum LogLevel;
            switch (_level)
            {
#if defined(_DEBUG)
            case MESSAGE:
                std::cout << _fmessage << '\n';
                break;
            case DEBUG:
                std::cout << "[DEBUG]: " << _fmessage << '\n';
                break;
            case SUCCESS:
                std::cout << "[SUCCESS]: " << _fmessage << '\n';
                break;
            case WARNING:
                std::cout << "[WARNING]: " << _fmessage << '\n';
                break;
#endif
            case ERROR:
                std::cerr << "[ERROR]: " << _fmessage << '\n';
                break;
            case FATAL:
                std::cerr << "[FATAL]: " << _fmessage << '\n';
                break;
            default:
                break;
            }
        }
    }
}
