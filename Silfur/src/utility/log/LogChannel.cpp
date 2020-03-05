#include "sfpch.h"
#include "LogChannel.h"

LogChannelBase::LogChannelBase(const std::string& p_channelName) :
    m_channelName(p_channelName)
{
}

LogChannelBase::~LogChannelBase() = default;