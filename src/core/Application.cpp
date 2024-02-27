#include "core/Application.h"
#include "core/Logger.h"
#include <regex>

namespace Mountain
{
	Application::Application(const std::string& appId)
	{
		Mountain::Logger::Init();

#ifdef DEBUG
		if (!std::regex_match(appId, std::regex(AppIdRegex)))
		{
			mn_coreFatal("App ID is invalid. It must contain 1 to 3 segments, delimited "
						 "by dots (.). Regex: {}",
						 AppIdRegex);

			exit(6);
		}
#endif
	}
}