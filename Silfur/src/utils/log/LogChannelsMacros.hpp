#pragma once

#include "LogChannel.hpp"

#define DECLARE_LOG_CHANNEL_EXTERN(channelName) \
    extern struct LogChannel##channelName : public LogChannel \
    { \
        LogChannel##channelName() : LogChannel(#channelName) {} \
    } channelName;

#define DEFINE_LOG_CHANNEL(channelName) LogChannel##channelName channelName;

DECLARE_LOG_CHANNEL_EXTERN(Temp)

DECLARE_LOG_CHANNEL_EXTERN(Win32)

DECLARE_LOG_CHANNEL_EXTERN(Vulkan)

DECLARE_LOG_CHANNEL_EXTERN(Core)
DECLARE_LOG_CHANNEL_EXTERN(Assert)
DECLARE_LOG_CHANNEL_EXTERN(Window_l)
DECLARE_LOG_CHANNEL_EXTERN(Input)
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
