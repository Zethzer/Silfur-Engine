#pragma once

#include <memory>
#include <string>

#include "core/Core.h"
#ifdef SF_CORE
    #include "LogCoreMacros.h"
#else
    #include "LogMacros.h"
#endif
#include "LogChannelsMacros.h"

#include "spdlog/spdlog.h"

namespace Silfur
{
    /// <summary>Log static class</summary>
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
