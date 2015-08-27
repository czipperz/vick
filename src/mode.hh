#ifndef HEADER_GUARD_MODE_H
#define HEADER_GUARD_MODE_H

#include <map>
#include <string>

extern std::map<char,void (*)()> global_normal_map;
extern std::map<char,void (*)()> global_insert_map;

struct mode {
    public:
    mode(const std::string&, bool (*const handle)(char));

    bool operator()(char);

    mode(const mode&);
    mode& operator=(const mode&);

    std::string get_name();

    static mode fundamental;
    static mode text;        // extends fundamental
    static mode programming; // extends programming

    struct listeners {
        static std::map<char,void (*)()> fundamental;
    };


    private:
    std::string name;
    // true = has binding
    bool (*handle)(char);
};
#endif
