#pragma once
#include <string>

namespace Mountain
{
	class Application
	{
	public:
		const static std::string AppIdRegex;

		Application(const std::string& appId);

	private:
		const char* _appId;
		const char* _appName;
		const char* _appOrg;
		const char* _appDomain{""};
	};
}