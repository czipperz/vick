#ifndef HEADER_GUARD_COMMAND_LISTENERS_H
#define HEADER_GUARD_COMMAND_LISTENERS_H

#include <boost/optional.hpp>
#include "contents.hh"

void command_executor(contents& cont, boost::optional<int> times);

#endif
