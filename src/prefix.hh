#ifndef HEADER_GUARD_PREFIX_H
#define HEADER_GUARD_PREFIX_H

#include <map>
#include <functional>

#include "contents.hh"

class prefix {
    private:
    // use this for documentation
    char prech;

    std::map < char, std::function < void ( contents&,
                                            boost::optional<int> ) > > map;

    public:
    prefix(char);
    void push_back(char, std::function < void ( contents&,
                                                boost::optional<int> ) > );
    void operator() ( contents& cont, boost::optional<int> );
    operator std::function < void ( contents&,
                                    boost::optional<int> ) > ();
};

#endif
