#include "sfpch.hpp"
#include "LogChannel.hpp"

LogChannelBase::LogChannelBase(const std::string& p_channelName) :
    m_channelName(p_channelName)
{
}

LogChannelBase::~LogChannelBase() = default;