#include "change.hh"

change::change(void (*handle)(std::vector<std::string>&))
    : handle(handle) { }
change change::operator>>(change& other) {
    return change([&,other,this] (std::vector<std::string>& contents)
                  {
                      other(contents);
                      this(contents);
                  });
}
