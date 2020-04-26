#pragma once

#ifndef __SILFUR_UTILITY_LOG_LOG_CORE_MACROS_HPP__
#define __SILFUR_UTILITY_LOG_LOG_CORE_MACROS_HPP__

#include <string>

#define SF_CORE_LOG_LEVEL_TRACE 6
#define SF_CORE_LOG_LEVEL_DEBUG 5
#define SF_CORE_LOG_LEVEL_INFO 4
#define SF_CORE_LOG_LEVEL_WARNING 3
#define SF_CORE_LOG_LEVEL_ERROR 2
#define SF_CORE_LOG_LEVEL_FATAL 1
#define SF_CORE_LOG_LEVEL_OFF 0

#ifndef SF_CORE_LOG_LEVEL
    #define SF_CORE_LOG_LEVEL SF_CORE_LOG_LEVEL_TRACE
#else
    #if SF_CORE_LOG_LEVEL <= -1
        #define SF_CORE_LOG_LEVEL SF_CORE_LOG_LEVEL_OFF
    #endif

    #if SF_CORE_LOG_LEVEL >= 7
        #define SF_CORE_LOG_LEVEL SF_CORE_LOG_LEVEL_TRACE
    #endif
#endif // SF_CORE_LOG_LEVEL

#define __PATTERN_LOG__ std::string("[") + ::Silfur::Log::GetLogger()->name() + "] [" + (strrchr("\\" __FILE__, '\\') + 1) + "::" + std::to_string(__LINE__) + "::" + __func__ + "] "

#if SF_CORE_LOG_LEVEL >= SF_CORE_LOG_LEVEL_TRACE
    #define SF_CORE_TRACE(p_channelName, ...)   ::Silfur::Log::GetLogger()->trace(__PATTERN_LOG__ + "[" + p_channelName.getChannelName() + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_CORE_TRACE(p_channelName, ...)
#endif

#if SF_CORE_LOG_LEVEL >= SF_CORE_LOG_LEVEL_DEBUG
    #define SF_CORE_DEBUG(p_channelName, ...)   ::Silfur::Log::GetLogger()->debug(__PATTERN_LOG__ + "[" + p_channelName.getChannelName() + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_CORE_DEBUG(p_channelName, ...)
#endif

#if SF_CORE_LOG_LEVEL >= SF_CORE_LOG_LEVEL_INFO
    #define SF_CORE_INFO(p_channelName, ...)    ::Silfur::Log::GetLogger()->info(__PATTERN_LOG__ + "[" + p_channelName.getChannelName() + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_CORE_INFO(p_channelName, ...)
#endif

#if SF_CORE_LOG_LEVEL >= SF_CORE_LOG_LEVEL_WARNING
    #define SF_CORE_WARNING(p_channelName, ...)  ::Silfur::Log::GetLogger()->warn(__PATTERN_LOG__ + "[" + p_channelName.getChannelName() + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_CORE_WARNING(p_channelName, ...)
#endif

#if SF_CORE_LOG_LEVEL >= SF_CORE_LOG_LEVEL_ERROR
    #define SF_CORE_ERROR(p_channelName, ...)    ::Silfur::Log::GetLogger()->error(__PATTERN_LOG__ + "[" + p_channelName.getChannelName() + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_CORE_ERROR(p_channelName, ...)
#endif

#if SF_CORE_LOG_LEVEL >= SF_CORE_LOG_LEVEL_FATAL
    #define SF_CORE_FATAL(p_channelName, p_FatalCode,...)   ::Silfur::Log::GetLogger()->critical(__PATTERN_LOG__ + "[" + p_channelName.getChannelName() + "] " + "[" + #p_FatalCode + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_CORE_FATAL(p_channelName, p_FatalCode,...)
#endif

#endif // __SILFUR_UTILITY_LOG_LOG_CORE_MACROS_HPP__
