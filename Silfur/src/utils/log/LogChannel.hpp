#pragma once

#include "defines.hpp"

#include <string>

struct LogChannel
{
    LogChannel(const std::string& name);
    ~LogChannel();

    std::string getChannelName() const { return m_channelName; }

protected:
    std::string m_channelName;
};
