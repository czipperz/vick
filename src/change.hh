#ifndef HEADER_GUARD_CHANGE_H
#define HEADER_GUARD_CHANGE_H

#include <functional>
#include <string>
#include <vector>

class change {
    private:
    const std::function<void(std::vector<std::string>&)> handle;

    public:
    change(void (*)(std::vector<std::string>&));
    change(std::function<void(std::vector<std::string>&)>);

    //combines two changes together
    //mvd >> mvsot >> mvf   would past the first character on the next line
    change operator>>(const change&) const;
    void operator()(std::vector<std::string>& contents) const;
};

#endif
