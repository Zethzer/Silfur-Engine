#pragma once

#include "core/Core.h"
#include "LogChannel.h"

#define DECLARE_LOG_CHANNEL_EXTERN(p_channelName) \
    extern struct LogChannel##p_channelName : public LogChannel \
    { \
        LogChannel##p_channelName() : LogChannel(#p_channelName) {} \
    } p_channelName;

#define DEFINE_LOG_CHANNEL(p_channelName) LogChannel##p_channelName p_channelName;

#define DEFINE_LOG_CHANNEL_STATIC(p_channelName) \
    static struct LogChannel##p_channelName : public LogChannel \
    { \
        LogChannel##p_channelName() : LogChannel(#p_channelName) {} \
    } p_channelName;

DECLARE_LOG_CHANNEL_EXTERN(Win32)

DECLARE_LOG_CHANNEL_EXTERN(Temp)

DECLARE_LOG_CHANNEL_EXTERN(Core)
DECLARE_LOG_CHANNEL_EXTERN(Assert)
DECLARE_LOG_CHANNEL_EXTERN(Window_l)
DECLARE_LOG_CHANNEL_EXTERN(Serialization)
DECLARE_LOG_CHANNEL_EXTERN(Math)
DECLARE_LOG_CHANNEL_EXTERN(Memory)
DECLARE_LOG_CHANNEL_EXTERN(ProfilingDebugging)
DECLARE_LOG_CHANNEL_EXTERN(OutputDevice)

DECLARE_LOG_CHANNEL_EXTERN(Init)
DECLARE_LOG_CHANNEL_EXTERN(Exit)
DECLARE_LOG_CHANNEL_EXTERN(Exec)
DECLARE_LOG_CHANNEL_EXTERN(Load)

DECLARE_LOG_CHANNEL_EXTERN(Animation)
DECLARE_LOG_CHANNEL_EXTERN(Model)
DECLARE_LOG_CHANNEL_EXTERN(Texture)
DECLARE_LOG_CHANNEL_EXTERN(Material)
DECLARE_LOG_CHANNEL_EXTERN(Font)
DECLARE_LOG_CHANNEL_EXTERN(Image)
