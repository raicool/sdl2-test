#pragma once

#include "spdlog/spdlog.h"

struct log
{
	inline static std::shared_ptr<spdlog::logger> debuglogger;

	static void init()
	{
		spdlog::sink_ptr consolesink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		spdlog::sink_ptr filesink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("dragonfruit.log");
		filesink->flush();

		consolesink->set_pattern("%^[%T] : %v%$");
		filesink->set_pattern("[%T] : %v");

		debuglogger = std::make_shared<spdlog::logger>("Dragon", spdlog::sinks_init_list{ consolesink, filesink });
		spdlog::register_logger(debuglogger);
		spdlog::set_level(spdlog::level::trace);
		spdlog::flush_on(spdlog::level::trace);
	}
}; 

#define LOG_TRACE(...) log::debuglogger->trace(__VA_ARGS__)
#define LOG_INFO(...)  log::debuglogger->info(__VA_ARGS__)
#define LOG_WARN(...)  log::debuglogger->warn(__VA_ARGS__)
#define LOG_ERROR(...) log::debuglogger->error(__VA_ARGS__)
#define LOG_FATAL(...) log::debuglogger->critical(__VA_ARGS__)