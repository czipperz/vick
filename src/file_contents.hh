#ifndef HEADER_GUARD_FILE_CONTENTS_H
#define HEADER_GUARD_FILE_CONTENTS_H

#include <vector>
#include <string>
#include "contents.hh"

void      init(std::vector<std::string>);
contents& get_contents();
void      print_contents(contents&);

#endif
