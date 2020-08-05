#include "sfpch.hpp"
#include "Log.hpp"

#include <filesystem>
#include <fstream>
#include <ctime>
#include <string>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Silfur
{
    Ref<spdlog::logger> Log::s_logger;

    void Log::Init()
    {
        std::string l_patternLogs = "%^[%D-%T] [%L] %v%$";
        spdlog::level::level_enum l_levelLogs = spdlog::level::trace;
        std::string l_dirnameLogs = "logs";
        std::string l_filename = "app-logs";
        std::string l_extFile = ".txt";

        try
        {
            // Delete old directory if its exist and create a new one for log file
            try
            {
                if (std::filesystem::exists(l_dirnameLogs))
                {
                    std::filesystem::remove_all(l_dirnameLogs);
                }

                std::filesystem::create_directory(l_dirnameLogs);
            }
            //catch (const boost::filesystem::filesystem_error& p_ex)
            catch (const std::filesystem::filesystem_error& p_ex)
            {
                std::cout << "Create directory failed" << p_ex.what() << std::endl;
            }

            // Get date and time on system ; cut it
            time_t rawtime;
            struct tm* timeinfo;
            char buffer[80];
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            strftime(buffer, 80, "%F_%H-%M-%S", timeinfo);

            // Create a string for the filename
            std::stringstream l_ss;
#ifdef _WIN32
            l_ss << l_dirnameLogs << '\\' << l_filename << "_" << buffer << l_extFile;
#else
            l_ss << l_dirnameLogs << '/' << l_filename << "_" << buffer << l_extFile;
#endif
            std::string l_logFileFullPath(l_ss.str());

            // Create file log
            std::ofstream l_logFile(l_logFileFullPath);
            l_logFile.close();

            // Create sinks
#ifdef SF_CONFIG_DEBUG
            auto l_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
#endif
            auto l_fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(l_logFileFullPath);

            // Create and configure the logger
#ifndef SF_CONFIG_DEBUG
            s_logger = std::make_shared<spdlog::logger>("SF_LOGGER", l_fileSink);
#else
            s_logger = std::make_shared<spdlog::logger>("SF_LOGGER",
                    spdlog::sinks_init_list({ l_fileSink, l_console_sink }));
#endif
            s_logger->set_pattern(l_patternLogs);
            s_logger->set_level(l_levelLogs);
            s_logger->flush_on(spdlog::level::err);
        }
        catch (const spdlog::spdlog_ex& p_ex)
        {
            std::cout << "Log initialization failed" << p_ex.what() << std::endl;
        }
    }
}
