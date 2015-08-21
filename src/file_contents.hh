#ifndef HEADER_GUARD_FILE_CONTENTS_H
#define HEADER_GUARD_FILE_CONTENTS_H

#include <vector>
#include <string>

class contents {
    private:
    std::vector<std::string>* cont;
    long y,x,desired_x;
    bool waiting_for_desired;

    public:
    contents(std::vector<std::string>* cont
             = new std::vector<std::string>());
    contents(long y, long x);
    ~contents();

    void push_back(const std::string& str);
    long get_y() const;
    long get_x() const;
    long get_desired_x() const;
    bool get_waiting_for_desired() const;

    friend void redrawyx(contents&);

    friend void mvline (contents&, unsigned long);
    friend void mv     (contents&, unsigned long, unsigned long);

    friend void mvrel  (contents&, long,          long);

    friend void mvcol  (contents&, unsigned long);

    friend void mvsot  (contents&);

    friend void mveol  (contents&);
    friend void mvsol  (contents&);

    friend void mvsop  (contents&);
    friend void mveop  (contents&);

    friend void mvd    (contents&, long);
    friend void mvu    (contents&, long);

    friend void mvfw   (contents&, unsigned long);
    friend void mvbw   (contents&, unsigned long);

    friend void mvf    (contents&, unsigned long);
    friend void mvb    (contents&, unsigned long);
};

void init(std::vector<std::string>*);
contents& get_contents();

#endif
