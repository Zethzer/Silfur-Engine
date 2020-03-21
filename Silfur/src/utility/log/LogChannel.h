#pragma once

#ifndef LOG_CHANNEL_H
#define LOG_CHANNEL_H

#include "core/Core.h"

#include <string>

struct LogChannelBase
{
    explicit LogChannelBase(const std::string& p_name);
    ~LogChannelBase();

    std::string getChannelName() const { return m_channelName; }

protected:
    std::string m_channelName;
};

struct LogChannel : public LogChannelBase
{
    explicit LogChannel(const std::string& p_name) : LogChannelBase(p_name) {}
};

#endif // LOG_CHANNEL_H
