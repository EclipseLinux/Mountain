#pragma once
#include <string>

namespace Mountain
{
	class Application
	{
	public:
		const std::string AppIdRegex =
			"[a-zA-Z0-9_-]+\.[a-zA-Z0-9_-]+(\.[a-zA-Z0-9_-]+)?";

		Application(const std::string& appId);

	private:
		char* _appId;
		char* _appName;
		char* _appOrg;
		char* _appDomain;
	};
}