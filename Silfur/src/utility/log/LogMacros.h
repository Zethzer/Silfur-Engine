#pragma once

#ifndef LOG_MACROS_H
#define LOG_MACROS_H

#include <string>

#define SF_LOG_LEVEL_TRACE 6
#define SF_LOG_LEVEL_DEBUG 5
#define SF_LOG_LEVEL_INFO 4
#define SF_LOG_LEVEL_WARNING 3
#define SF_LOG_LEVEL_ERROR 2
#define SF_LOG_LEVEL_FATAL 1
#define SF_LOG_LEVEL_OFF 0

#ifndef SF_LOG_LEVEL
    #define SF_LOG_LEVEL SF_LOG_LEVEL_TRACE
#else
    #if SF_LOG_LEVEL <= -1
        #define SF_LOG_LEVEL SF_LOG_LEVEL_OFF
    #endif

    #if SF_LOG_LEVEL >= 7
        #define SF_LOG_LEVEL SF_LOG_LEVEL_TRACE
    #endif
#endif

#define __PATTERN_LOG__ std::string("[") + (strrchr("\\" __FILE__, '\\') + 1) + "::" + std::to_string(__LINE__) + "::" + __func__ + "] "

#if SF_LOG_LEVEL >= SF_LOG_LEVEL_TRACE
    #define SF_TRACE(p_channelName, ...)    ::Silfur::Log::GetLogger()->trace(__PATTERN_LOG__ + "[" + p_channelName.getChannelName() + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_TRACE(p_channelName, ...)
#endif

#if SF_LOG_LEVEL >= SF_LOG_LEVEL_DEBUG
    #define SF_DEBUG(p_channelName, ...)    ::Silfur::Log::GetLogger()->debug(__PATTERN_LOG__ + "[" + p_channelName.getChannelName() + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_DEBUG(p_channelName, ...)
#endif

#if SF_LOG_LEVEL >= SF_LOG_LEVEL_INFO
    #define SF_INFO(p_channelName, ...) ::Silfur::Log::GetLogger()->info(__PATTERN_LOG__ + "[" + p_channelName.getChannelName() + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_INFO(p_channelName, ...)
#endif

#if SF_LOG_LEVEL >= SF_LOG_LEVEL_WARNING
    #define SF_WARNING(p_channelName, ...)  ::Silfur::Log::GetLogger()->warn(__PATTERN_LOG__ + "[" + p_channelName.getChannelName() + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_WARNING(p_channelName, ...)
#endif

#if SF_LOG_LEVEL >= SF_LOG_LEVEL_ERROR
    #define SF_ERROR(p_channelName, p_ErrorCode,...)    ::Silfur::Log::GetLogger()->error(__PATTERN_LOG__ + "[" + p_channelName.getChannelName() + "] " + "[" + #p_ErrorCode + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_ERROR(p_channelName, p_ErrorCode,...)
#endif

#if SF_LOG_LEVEL >= SF_LOG_LEVEL_FATAL
    #define SF_FATAL(p_channelName, p_FatalCode,...)    ::Silfur::Log::GetLogger()->critical(__PATTERN_LOG__ + "[" + p_channelName.getChannelName() + "] " + "[" + #p_FatalCode + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_FATAL(p_channelName, p_FatalCode,...)
#endif

#endif // LOG_MACROS_H
