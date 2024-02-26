#include "utils/Demangler.h"

#ifdef __GNUG__
#	include <cstdlib>
#	include <cxxabi.h>
#	include <memory>

auto demangle(const char* name) -> std::string
{
	int status = -4; // some arbitrary value to eliminate the compiler warning

	std::unique_ptr<char, void (*)(void*)> res{
		abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};

	return (status == 0) ? res.get() : name;
}

#else

auto demangle(const char* name) -> std::string
{
	return name;
}

#endif