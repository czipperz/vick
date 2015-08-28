#ifndef HEADER_GUARD_CHANGE_H
#define HEADER_GUARD_CHANGE_H

#include <string>
#include <vector>

class change {
    private:
    void (*const handle)(std::vector<std::string>&);
    public:
    change(void (*)(std::vector<std::string>&));
    change operator>>(change&); //then
    void operator()(std::vector<std::string>& contents);
};

#endif
