#ifndef HEADER_GUARD_CLASS_CONTENTS_H
#define HEADER_GUARD_CLASS_CONTENTS_H

#include <vector>
#include <string>

class contents {
    public:
    std::vector<std::string>* cont;
    unsigned long
        y,x,desired_x,
        y_offset;
    bool waiting_for_desired;

    contents(std::vector<std::string>* cont
             = new std::vector<std::string>());
    contents(long y, long x);
    ~contents();

    contents(const contents&);
    contents& operator=(const contents&);

#if __cplusplus >= 201103L
    contents(contents&&);
    contents& operator=(contents&&);
#endif

    void push_back(const std::string& str);
};

#endif
