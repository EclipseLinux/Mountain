#pragma once
#include <string>

namespace Mountain
{
	/**
	 * @brief Main starting point of every application built on top of Mountain
	 *
	 */
	class Application
	{
	public:
		/**
		 * @brief Unique instance of an Application
		 *
		 * There can only be one instance globally (singleton)
		 */
		inline static Application* main;
		/**
		 * @brief Simple RegEx describing Application Identifiers
		 *
		 * Used for internal purposes, but meh
		 */
		inline const static std::string AppIdRegex =
			"[a-zA-Z0-9_-]+\\.[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)?";

		/**
		 * @brief Construct a new Application
		 *
		 * @param appId Application Identifier, must match the @see AppIdRegex
		 */
		Application(const std::string& appId);

	private:
		const char* _appId;
		const char* _appName;
		const char* _appOrg;
		const char* _appDomain{""};
	};
}