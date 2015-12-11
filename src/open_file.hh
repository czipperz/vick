#ifndef HEADER_GUARD_OPEN_FILE_H
#define HEADER_GUARD_OPEN_FILE_H

#include "contents.hh"

namespace vick {

boost::optional<std::shared_ptr<change> >
open_file_i(contents& contents, boost::optional<int> = boost::none);

boost::optional<std::shared_ptr<change> >
open_file(contents& contents, std::string file);

}

#endif
