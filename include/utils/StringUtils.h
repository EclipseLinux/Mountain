#pragma once
#include <string>
#include <vector>

void stringReplace(std::string& str, const std::string& src, const std::string& dest);

auto stringToUpper(std::string& str) -> std::string;

auto stringToLower(std::string& str) -> std::string;

auto stringSplit(const std::string& str, const std::string& delimiter)
	-> std::vector<std::string>;