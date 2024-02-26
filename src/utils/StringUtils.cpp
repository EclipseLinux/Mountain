#include "utils/StringUtils.h"
#include <algorithm>

void stringReplace(std::string& str, const std::string& src, const std::string& dest)
{
	if (src.empty())
	{
		return;
	}
	size_t start_pos = 0;
	while ((start_pos = str.find(src, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, src.length(), dest);
		start_pos += dest.length();
	}
}

auto stringToUpper(std::string& str) -> std::string
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);

	return str;
}

auto stringToLower(std::string& str) -> std::string
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	return str;
}