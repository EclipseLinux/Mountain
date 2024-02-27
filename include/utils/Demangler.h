#pragma once
#include <string>

/**
 * @brief Tries to demangle a name, used internally
 *
 * @param name Name to demangle, usually by typeid().name()
 * @return std::string Demangled name, if using GCC, otherwise the mangled one
 */
auto demangle(const char* name) -> std::string;