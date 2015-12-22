#include <map>
#include <ncurses.h>
#include <string>

#include "file_contents.hh"
#include "mode.hh"
#include "show_message.hh"
#include "prefix.hh"

namespace vick {

prefix::prefix(std::string message)
    : map(std::make_shared<std::map<char, std::function<boost::optional<std::shared_ptr<change> >
                                                        (contents&, boost::optional<int>)> > >())
    , message(message) { }

void prefix::push_back(char ch, std::function < boost::optional< std::shared_ptr<change> >
                                                ( contents&, boost::optional<int> ) > fun)
{
    (*map)[ch] = fun;
}

boost::optional< std::shared_ptr<change> >
prefix::operator()(contents& cont, boost::optional<int> op) {
    show_message(message + "-");
    char ch = getch();
    auto it = map->find(ch);
    if (it == map->end()) {
        show_message(std::string("Didn't recognize key sequence: '")
                     + message + '-' + ch + '\'');
        return boost::none;
    } else {
        showing_message = false;
        return it->second(cont, op);
    }
}

prefix::operator std::function<boost::optional<std::shared_ptr<change> >
                               (contents&, boost::optional<int>)>()
{
    return std::function<boost::optional<std::shared_ptr<change> >
                         (contents&, boost::optional<int>)>
        ([this](contents& cont, boost::optional<int> op) {
            return (*this)(cont, op);
        });
}

}
