#include <ncurses.h>

#include "show_message.hh"
#include "prefix_key.hh"

char prefix_key_times_ten = '0';

static void handle(contents& contents, boost::optional<int> op, int n) {
    int orig = op ? op.get() : 0;
    char c = getch();
    if(c == prefix_key_times_ten && orig != 0) {
        c = getch();
        while(c == prefix_key_times_ten) {
            orig *= 10;
            c = getch();
        }
    }
    orig *= 10;
    const auto& x = global_normal_map.find(c);
    if(x == global_normal_map.end()) {
        show_message(std::string("Unbound key: ") + std::to_string(c));
        return;
    }
    x->second(contents, orig + n);
}

void prefix_key_1(contents& contents, boost::optional<int> op) {
    handle(contents,op,1);
}
void prefix_key_2(contents& contents, boost::optional<int> op) {
    handle(contents,op,2);
}
void prefix_key_3(contents& contents, boost::optional<int> op) {
    handle(contents,op,3);
}
void prefix_key_4(contents& contents, boost::optional<int> op) {
    handle(contents,op,4);
}
void prefix_key_5(contents& contents, boost::optional<int> op) {
    handle(contents,op,5);
}
void prefix_key_6(contents& contents, boost::optional<int> op) {
    handle(contents,op,6);
}
void prefix_key_7(contents& contents, boost::optional<int> op) {
    handle(contents,op,7);
}
void prefix_key_8(contents& contents, boost::optional<int> op) {
    handle(contents,op,8);
}
void prefix_key_9(contents& contents, boost::optional<int> op) {
    handle(contents,op,9);
}
