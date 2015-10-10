#ifndef HEADER_GUARD_BASIC_COMMANDS_H
#define HEADER_GUARD_BASIC_COMMANDS_H

#include "contents.hh"

void quit_command(contents&, boost::optional<int>);
void key_test_command(contents&, boost::optional<int>);
void replace_character(contents&, boost::optional<int>);

#endif
