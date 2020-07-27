#pragma once

#ifndef __SILFUR_UTILITY_LOG_LOG_CHANNEL_HPP__
#define __SILFUR_UTILITY_LOG_LOG_CHANNEL_HPP__

#include "core/Base.hpp"

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

#endif // __SILFUR_UTILITY_LOG_LOG_CHANNEL_HPP__
