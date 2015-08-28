#include "change.hh"

change::change(void (*handle)(std::vector<std::string>&))
    : handle(std::function
               <void(std::vector<std::string>&)>
                 (handle)) { }

change::change(std::function<void(std::vector<std::string>&)> handle)
    : handle(handle) { }

change change::operator>>(const change& other) const {
    std::function < void(std::vector <std::string>&) > func(
        [&,other,this] (std::vector<std::string>& contents)
        { other(contents);   (*this)(contents); });
    return change(func);
}

void change::operator()(std::vector<std::string>& contents) const {
    handle(contents);
}
