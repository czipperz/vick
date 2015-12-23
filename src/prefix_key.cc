#include <ncurses.h>

#include "show_message.hh"
#include "prefix_key.hh"

namespace vick {

char prefix_key_times_ten;

static boost::optional< std::shared_ptr<change> > handle(contents& contents, boost::optional<int> op, int n) {
    int total = n + (op ? op.get() : 0) * 10;
    show_message(std::to_string(total) + "-");
    char c = getch();
    while (c == prefix_key_times_ten) {
        total *= 10;
        show_message(std::to_string(total) + "-");
        c = getch();
    }
    auto x = global_normal_map.find(c);
    if (x == global_normal_map.end()) {
        show_message(std::string("Unbound key: ") + std::to_string(c));
        return boost::none;
    }
    showing_message = false;
    return x->second(contents, total);
}

boost::optional< std::shared_ptr<change> > prefix_key_1(contents& contents, boost::optional<int> op) {
    return handle(contents,op,1);
}
boost::optional< std::shared_ptr<change> > prefix_key_2(contents& contents, boost::optional<int> op) {
    return handle(contents,op,2);
}
boost::optional< std::shared_ptr<change> > prefix_key_3(contents& contents, boost::optional<int> op) {
    return handle(contents,op,3);
}
boost::optional< std::shared_ptr<change> > prefix_key_4(contents& contents, boost::optional<int> op) {
    return handle(contents,op,4);
}
boost::optional< std::shared_ptr<change> > prefix_key_5(contents& contents, boost::optional<int> op) {
    return handle(contents,op,5);
}
boost::optional< std::shared_ptr<change> > prefix_key_6(contents& contents, boost::optional<int> op) {
    return handle(contents,op,6);
}
boost::optional< std::shared_ptr<change> > prefix_key_7(contents& contents, boost::optional<int> op) {
    return handle(contents,op,7);
}
boost::optional< std::shared_ptr<change> > prefix_key_8(contents& contents, boost::optional<int> op) {
    return handle(contents,op,8);
}
boost::optional< std::shared_ptr<change> > prefix_key_9(contents& contents, boost::optional<int> op) {
    return handle(contents,op,9);
}

}
