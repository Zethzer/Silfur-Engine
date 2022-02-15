#pragma once

#include "defines.hpp"
#ifdef SF_CORE
    #include "LogCoreMacros.hpp"
#else
    #include "LogMacros.hpp"
#endif
#include "LogChannelsMacros.hpp"

#include <spdlog/logger.h>

namespace Silfur
{
    class Log
    {
    public:
        Log() = delete;

        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_logger; }

    private:
        static std::shared_ptr<spdlog::logger> s_logger;
    };
}
