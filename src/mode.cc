#include <functional>
#include <boost/optional.hpp>

#include "configuration.hh"
#include "key_aliases.hh"
#include "file_contents.hh"
#include "mode.hh"
#include "show_message.hh"

namespace vick {

std::map<char, std::function<boost::optional<std::shared_ptr<
                   change> >(contents &, boost::optional<int>)> >
    global_normal_map, global_insert_map;

mode::mode(const std::string& name)
    : name(name)
    , normal_map(
          std::make_shared<std::map<
              char,
              std::function<boost::optional<std::shared_ptr<
                  change> >(contents&, boost::optional<int>)> > >())
    , insert_map(
          std::make_shared<std::map<
              char,
              std::function<boost::optional<std::shared_ptr<
                  change> >(contents&, boost::optional<int>)> > >()) {
    static int uid = 0;
    unique_id = uid++;
}

bool mode::operator()(contents& cont, char ch) const {
    if (ch == RESIZE)
        return true;

    // *b*uffer iterator
    auto bit = cont.normal_map.find(ch);
    if (bit == cont.normal_map.end()) {
        // *m*ode iterator
        auto mit = normal_map->find(ch);
        if (mit == normal_map->end()) {
            // *g*lobal iterator
            auto git = global_normal_map.find(ch);
            if (git == global_normal_map.end()) {
                return false;

#define mac(i)                                                       \
    clear_message();                                                 \
    if (auto optional = i->second(cont, boost::none)) {              \
        PUSH_BACK_CHANGE(cont, *optional);                           \
    }

            } else {
                mac(git);
            }
        } else {
            mac(mit);
        }
    } else {
        mac(bit);
    }
#undef mac

    return true;
}

const std::string& mode::get_name() const { return name; }

bool mode::operator==(const mode& other) const {
    return unique_id == other.unique_id;
}

bool mode::operator!=(const mode& other) const {
    return unique_id != other.unique_id;
}

void mode::add_to_mode_normal_map(
    char ch, std::function<boost::optional<std::shared_ptr<change> >(
                 contents&, boost::optional<int>)> fun) {
    (*normal_map)[ch] = fun;
}

void mode::add_to_mode_insert_map(
    char ch, std::function<boost::optional<std::shared_ptr<change> >(
                 contents&, boost::optional<int>)> fun) {
    (*insert_map)[ch] = fun;
}

mode fundamental_mode("Fundamental");
}
