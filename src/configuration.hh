#ifndef HEADER_GUARD_Configuration_H
#define HEADER_GUARD_Configuration_H

#include <map>
#include <vector>
#include <string>
#include <functional>

#include "contents.hh"

extern const int TAB_SIZE;

void add_listeners();

void add_commands(std::map<std::string,
                           std::function<void(contents&,
                                              boost::optional<int>)> >&);

extern const std::string DELIMINATORS;

#endif
