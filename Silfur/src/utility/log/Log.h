#pragma once

#ifndef LOG_H
#define LOG_H

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
    class Log
    {
    public:
        Log() = delete;

        static void Init();

        inline static Ref<spdlog::logger>& GetLogger() { return s_logger; }

    private:
        static Ref<spdlog::logger> s_logger;
    };
}

#endif // LOG_H
