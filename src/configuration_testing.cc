#include "configuration.hh"

namespace vick {

char QUIT_KEY = 0;
int TAB_SIZE = 1;
void (*PUSH_BACK_CHANGE)(contents&,
                         std::shared_ptr<change>) = nullptr;
std::string DELIMINATORS = "!@#$%^&*()-=+[]{}\\|;:'\",.<>/?`~";
std::string MATCHES = "()[]{}";

bool use_colors() { return true; }
void init_conf() {}
void add_listeners() {}
void add_commands(
    std::map<std::string,
             std::function<boost::optional<std::shared_ptr<change> >(
                 contents&, boost::optional<int>)> >&) {}
}
