#pragma once
#include <memory>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <string>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

namespace Mountain
{
	/**
	 * @brief Simple class for logging with pretty colors, and fast
	 *
	 * Used only by Mountain, as it has the huge "Mountain" name on it.
	 * For normal logging, use the "mn_" related macros
	 */
	class Logger
	{
	public:
		/**
		 * @brief Logs with an "info" level, and green
		 *
		 * @tparam Args Any fmt formattable type
		 * @param msg Message to log
		 * @param args Arguments to format the message with
		 */
		template <typename... Args>
		static void Info(const std::string& msg, Args&&... args)
		{
			logger->info(fmt::runtime(msg), args...);
		}

		/**
		 * @brief Logs with a "warn" level, and yellow
		 *
		 * @tparam Args Any fmt formattable type
		 * @param msg Message to log
		 * @param args Arguments to format the message with
		 */
		template <typename... Args>
		static void Warn(const std::string& msg, Args&&... args)
		{
			logger->warn(fmt::runtime(msg), args...);
		}

		/**
		 * @brief Logs with an "error" level, and red
		 *
		 * @tparam Args Any fmt formattable type
		 * @param msg Message to log
		 * @param args Arguments to format the message with
		 */
		template <typename... Args>
		static void Error(const std::string& msg, Args&&... args)
		{
			logger->error(fmt::runtime(msg), args...);
		}

		/**
		 * @brief Logs with a "critical" level, and *bold* red
		 *
		 * @tparam Args Any fmt formattable type
		 * @param msg Message to log
		 * @param args Arguments to format the message with
		 */
		template <typename... Args>
		static void Fatal(const std::string& msg, Args&&... args)
		{
			logger->critical(fmt::runtime(msg), args...);
		}

#ifdef DEBUG
		/**
		 * @brief Logs with a "debug" level, and cyan
		 *
		 * @tparam Args Any fmt formattable type
		 * @param msg Message to log
		 * @param args Arguments to format the message with
		 */
		template <typename... Args>
		static void Debug(const std::string& msg, Args&&... args)
		{
			logger->debug(fmt::runtime(msg), args...);
		}
#endif

		/**
		 * @brief Logs with a "trace" level, and no color. crazy, right?
		 *
		 * @tparam Args Any fmt formattable type
		 * @param msg Message to log
		 * @param args Arguments to format the message with
		 */
		template <typename... Args>
		static void Trace(const std::string& msg, Args&&... args)
		{
			logger->trace(fmt::runtime(msg), args...);
		}

#ifdef DEBUG
		/**
		 * @brief Used only internally by Mountain, but still available
		 *
		 * @param condition Condition to check, the message will only print if this
		 * evaluates to @code {.cpp} false
		 * @endcode
		 *
		 * @param conditionStr Basically the condition, but in string format
		 * @param file Filename where the assert came from
		 * @param msg Message to print if it evaluates to false
		 * @param line Line number where the assert came from

		 * This is supposed to be used in macros, don't expect simplicity
		 */
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

		/**
		 * @brief Simply initialize the loggers, with their patterns, names, and stuff
		 *
		 * Done automatically by @see Application when initializing, don't worry
		 */
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
