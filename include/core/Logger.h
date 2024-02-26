#pragma once
#include <memory>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <string>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

namespace Mountain
{
	class Logger
	{
	public:
		template <typename... Args>
		static void Info(const std::string& msg, Args&&... args)
		{
			logger->info(msg, args...);
		}

		template <typename... Args>
		static void Warn(const std::string& msg, Args&&... args)
		{
			logger->warn(msg, args...);
		}

		template <typename... Args>
		static void Error(const std::string& msg, Args&&... args)
		{
			logger->error(msg, args...);
		}

		template <typename... Args>
		static void Fatal(const std::string& msg, Args&&... args)
		{
			logger->critical(msg, args...);
		}

#ifdef DEBUG
		template <typename... Args>
		static void Debug(const std::string& msg, Args&&... args)
		{
			logger->debug(msg, args...);
		}
#endif

		template <typename... Args>
		static void Trace(const std::string& msg, Args&&... args)
		{
			logger->trace(msg, args...);
		}

#ifdef DEBUG
		static void Assert(bool condition, const std::string& conditionStr,
						   const std::string& file, const std::string& msg, int line)
		{

			if (!condition)
			{
				logger->info("Assertion \"{}\" failed ({}:{}): {}", conditionStr, file,
							 line, msg);
			}
		}
#endif

		static void Init()
		{
			logger = spdlog::stdout_color_mt("Mountain");
			logger->set_pattern("[%^%n%$][%T][%l] %v");
			logger->set_level(spdlog::level::trace);

			std::shared_ptr<spdlog::logger> def = spdlog::stdout_color_mt("App");
			def->set_pattern("[%^%n%$][%T][%l][%s:%# %!()] %v");
			def->set_level(spdlog::level::trace);

			spdlog::set_default_logger(def);
		}

	private:
		inline static std::shared_ptr<spdlog::logger> logger;
	};
}

#define mn_info(msg, ...) SPDLOG_INFO(msg, ##__VA_ARGS__)
#define mn_warn(msg, ...) SPDLOG_WARN(msg, ##__VA_ARGS__)
#define mn_error(msg, ...) SPDLOG_ERROR(msg, ##__VA_ARGS__)
#define mn_fatal(msg, ...) SPDLOG_CRITICAL(msg, ##__VA_ARGS__)
#define mn_trace(msg, ...) SPDLOG_TRACE(msg, ##__VA_ARGS__)

#ifdef DEBUG
#	define mn_debug(msg, ...) SPDLOG_DEBUG(msg, ##__VA_ARGS__)
#	define mn_assert(condition, msg)                                                    \
		{                                                                                \
			if (!static_cast<bool>(condition))                                           \
				SPDLOG_INFO("Assertion \"{}\" failed: {}", #condition, msg);             \
		}
#else
#	define mn_debug(msg, ...)
#	define mn_assert(condition, msg)
#endif

#define mn_coreInfo(msg, ...) Mountain::Logger::Info(msg, ##__VA_ARGS__)
#define mn_coreWarn(msg, ...) Mountain::Logger::Warn(msg, ##__VA_ARGS__)
#define mn_coreError(msg, ...) Mountain::Logger::Error(msg, ##__VA_ARGS__)
#define mn_coreFatal(msg, ...) Mountain::Logger::Fatal(msg, ##__VA_ARGS__)
#define mn_coreTrace(msg, ...) Mountain::Logger::Trace(msg, ##__VA_ARGS__)

#ifdef DEBUG
#	define mn_coreDebug(msg, ...) Mountain::Logger::Debug(msg, ##__VA_ARGS__)
#	define mn_coreAssert(condition, msg)                                                \
		Mountain::Logger::Assert(static_cast<bool>(condition), #condition, __FILENAME__, \
								 msg, __LINE__)
#else
#	define mn_coreDebug(msg, ...)
#	define mn_coreAssert(condition, msg)
#endif
