#ifndef HEADER_GUARD_FILE_CONTENTS_H
#define HEADER_GUARD_FILE_CONTENTS_H

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
    contents(const contents&);
    ~contents();

    void push_back(const std::string& str);
    contents& operator=(const contents&);
};

void init(std::vector<std::string>*);
contents& get_contents();
void print_contents(const contents*);

#endif
