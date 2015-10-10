#ifndef HEADER_GUARD_PREFIX_H
#define HEADER_GUARD_PREFIX_H

#include <map>
#include <functional>
#include <boost/optional.hpp>


class contents;

class prefix {
    private:
    // use this for documentation
    std::string message;
    std::map < char, std::function < void ( contents&, boost::optional<int> ) > > map;

    public:
    prefix(std::string message);

    void push_back(char, std::function < void
                                  ( contents&, boost::optional<int> ) > );
    void operator ()              ( contents&, boost::optional<int> );
    operator std::function < void ( contents&, boost::optional<int> ) > ();
};

#endif
