#include <map>
#include <ncurses.h>
#include <string>

#include "file_contents.hh"
#include "mode.hh"
#include "show_message.hh"
#include "prefix.hh"

prefix::prefix(char ch)
    : prech(ch) { }

void prefix::push_back(char ch, std::function<void(contents&, boost::optional<int>)> fun) {
    this->map[ch] = fun;
}

void prefix::operator()(contents& cont, boost::optional<int> op) {
    show_message(message + "-");
    char ch = getch();
    auto it = map.find(ch);
    if(it == map.end()) {
        show_message(std::string("Didn't recognize key sequence: '")
                     + message + '-' + ch + '\'');
    } else {
        it->second(cont, op);
    }
}

prefix::operator std::function < void ( contents&,
                                        boost::optional<int> ) > () {
    return std::function < void ( contents&,
                                  boost::optional<int> ) >
        ([&,this] (contents& cont, boost::optional<int> op)
         {
             (*this)(cont,op);
         });
}
