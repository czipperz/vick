#include <fstream>
#include <ncurses.h>

#include "hooks.hh"
#include "open_file.hh"
#include "prompt.hh"

namespace vick {

struct full_diff : public change {
    contents o, n;
    full_diff(contents o, contents n)
        : o(o)
        , n(n) {}
    virtual bool is_overriding() override { return true; }
    virtual void undo(contents& cont) override { cont = o; }
    virtual void redo(contents& cont) override { cont = n; }
    virtual std::shared_ptr<change>
    regenerate(const contents& cont) const override {
        return std::make_shared<full_diff>(cont, n);
    }
};

boost::optional<std::shared_ptr<change> >
open_file_i(contents& cont, boost::optional<int>) {
    attron(COLOR_PAIR(1));
    auto opt = prompt("File to open: ");
    attroff(COLOR_PAIR(1));
    if (not opt)
        return boost::none;
    return open_file(cont, *opt);
}

contents open_file(std::string file) {
    contents cont;
    bool& windows = cont.windows_file_endings;
    bool asked = false;

    std::string line;
    std::ifstream myfile(file);

    if (std::getline(myfile, line)) {
        if (not line.empty() and line.back() == '\r') {
            line.pop_back();
            windows = true;
        }
        cont.cont.push_back(line);
        while (std::getline(myfile, line)) {
            if (not line.empty() and line.back() == '\r') {
                if (not windows and not asked) {
                    asked = true;
                    windows =
                        repeat_remove_optional(prompt_yes_no,
                                               "Windows file endings "
                                               "detected, "
                                               "use them when "
                                               "saving? ");
                }
                line.pop_back();
            }
            cont.cont.push_back(line);
        }
    } else {
        cont.cont.push_back("");
    }

    hook::proc(hook::open_file, cont);

    return cont;
}

boost::optional<std::shared_ptr<change> >
open_file(contents& cont, std::string file) {
    contents before = cont;
    cont.y = 0;
    cont.x = 0;
    cont.cont.clear();
    bool& windows = cont.windows_file_endings;
    bool asked = false;
    std::string line;
    std::ifstream myfile(file);

    if (std::getline(myfile, line)) {
        if (not line.empty() and line.back() == '\r') {
            line.pop_back();
            windows = true;
        }
        cont.cont.push_back(line);
        while (std::getline(myfile, line)) {
            if (not line.empty() and line.back() == '\r') {
                if (not windows and not asked) {
                    asked = true;
                    windows =
                        repeat_remove_optional(prompt_yes_no,
                                               "Windows file endings "
                                               "detected, "
                                               "use them when "
                                               "saving? ");
                }
                line.pop_back();
            }
            cont.cont.push_back(line);
        }
    } else
        cont.cont.push_back("");

    hook::proc(hook::open_file, cont);

    if (before.cont == cont.cont)
        return boost::none;
    return boost::optional<std::shared_ptr<change> >(
        std::make_shared<full_diff>(std::move(before), cont));
}
}
