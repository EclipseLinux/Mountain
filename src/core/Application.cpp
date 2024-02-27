#include "core/Application.h"
#include "core/Logger.h"
#include "utils/StringUtils.h"
#include <regex>
#include <spdlog/spdlog.h>

namespace Mountain
{
	Application::Application(const std::string& appId)
	{
		Mountain::Logger::Init();

#ifdef DEBUG
		if (!std::regex_match(appId, std::regex(AppIdRegex)))
		{
			mn_coreFatal("App ID is invalid. It must contain 1 to 3 segments, delimited "
						 "by dots (.). Regex: \"{}\"",
						 AppIdRegex);

			exit(6);
		}
#endif

		_appId = appId.c_str();

		auto segments = stringSplit(appId, ".");

		// we're going to assume it matches the regex, but still make some checks
		mn_coreAssert(!segments.empty(), "Expected at least one segment");
		mn_coreAssert(segments.size() <= 3, "Expected at most three segments");

		if (segments.size() == 3)
		{
			// best case
			_appDomain = segments[0].c_str();
			_appOrg = segments[1].c_str();
			_appName = segments[2].c_str();
		}
		else
		{
			_appOrg = segments[0].c_str();
			_appName = segments[1].c_str();
		}

		spdlog::set_default_logger(spdlog::default_logger()->clone(_appName));

		mn_coreTrace("Initializing \"{}\", by \"{}\"", _appName, _appOrg);
	}
}