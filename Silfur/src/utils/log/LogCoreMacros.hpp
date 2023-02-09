#pragma once

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

#define _LOGGER_NAME__ std::string("[") + ::Silfur::Log::GetLogger()->name() + "] "
#define _FILE_FUNC__ std::string("[") + (strrchr("\\" __FILE__, '\\') + 1) + "::" + std::to_string(__LINE__) + "::" + __func__ + "] "

#if SF_CORE_LOG_LEVEL >= SF_CORE_LOG_LEVEL_TRACE
    #define SF_CORE_TRACE(channelName, ...)   ::Silfur::Log::GetLogger()->trace(_LOGGER_NAME__ + _FILE_FUNC__ + "[" + channelName.getChannelName() + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_CORE_TRACE(channelName, ...)
#endif

#if SF_CORE_LOG_LEVEL >= SF_CORE_LOG_LEVEL_DEBUG
    #define SF_CORE_DEBUG(channelName, ...)   ::Silfur::Log::GetLogger()->debug(_LOGGER_NAME__ + _FILE_FUNC__ + "[" + channelName.getChannelName() + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_CORE_DEBUG(channelName, ...)
#endif

#if SF_CORE_LOG_LEVEL >= SF_CORE_LOG_LEVEL_INFO
    #define SF_CORE_INFO(channelName, ...)    ::Silfur::Log::GetLogger()->info(_LOGGER_NAME__ + "[" + channelName.getChannelName() + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_CORE_INFO(channelName, ...)
#endif

#if SF_CORE_LOG_LEVEL >= SF_CORE_LOG_LEVEL_WARNING
    #define SF_CORE_WARNING(channelName, ...)  ::Silfur::Log::GetLogger()->warn(_LOGGER_NAME__ + "[" + channelName.getChannelName() + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_CORE_WARNING(channelName, ...)
#endif

#if SF_CORE_LOG_LEVEL >= SF_CORE_LOG_LEVEL_ERROR
    #define SF_CORE_ERROR(channelName, errorCode, ...)    ::Silfur::Log::GetLogger()->error(_LOGGER_NAME__ + "[" + channelName.getChannelName() + "] " + "[" + #errorCode + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_CORE_ERROR(channelName, errorCode, ...)
#endif

#if SF_CORE_LOG_LEVEL >= SF_CORE_LOG_LEVEL_FATAL
    #define SF_CORE_FATAL(channelName, fatalCode, ...)   ::Silfur::Log::GetLogger()->critical(_LOGGER_NAME__ + _FILE_FUNC__ + "[" + channelName.getChannelName() + "] " + "[" + #fatalCode + "] " + fmt::format(__VA_ARGS__))
#else
    #define SF_CORE_FATAL(channelName, fatalCode, ...)
#endif
