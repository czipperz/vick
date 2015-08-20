#ifndef HEADER_GUARD_Configuration_H
#define HEADER_GUARD_Configuration_H

#include <map>
#include <vector>
#include <string>
int TAB_SIZE();
void add_listeners(std::map<char,void (*)()>&);
void add_commands (std::map<std::string,
                            void (*)(const std::vector<std::string>&)>&);

const std::string& DELIMINATORS();

#endif
