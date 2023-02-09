#include "sfpch.hpp"
#include "LogChannel.hpp"

LogChannel::LogChannel(const std::string& name)
    : m_channelName(name)
{
}

LogChannel::~LogChannel() = default;
