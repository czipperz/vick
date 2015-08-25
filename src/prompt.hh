#ifndef HEADER_GUARD_PROMPT_H
#define HEADER_GUARD_PROMPT_H

#include <string>

// if aborted (escape) then will return ""
std::string prompt(const std::string& message, unsigned int y);
std::string prompt(const std::string& message);

#endif
