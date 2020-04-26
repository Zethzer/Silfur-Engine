#pragma once

#ifndef __SILFUR_UTILITY_LOG_LOG_HPP__
#define __SILFUR_UTILITY_LOG_LOG_HPP__

#include "core/Core.hpp"
#ifdef SF_CORE
    #include "LogCoreMacros.hpp"
#else
    #include "LogMacros.hpp"
#endif
#include "LogChannelsMacros.hpp"

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

#endif // __SILFUR_UTILITY_LOG_LOG_HPP__
