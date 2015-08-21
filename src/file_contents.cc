#include "file_contents.hh"
#include "newmove.hh"
#include "parse_init_contents.hh"

contents::contents(std::vector<std::string>* cont)
    : cont(cont),
      y(0),
      x(0),
      desired_x(0),
      waiting_for_desired(false) { }

contents::contents(long y, long x)
    : cont(new std::vector<std::string>()),
      y(y),
      x(x),
      desired_x(0),
      waiting_for_desired(false) { }

contents::~contents() { delete this->cont; }

void contents::push_back(const std::string& str) {
    this->cont->push_back(str);
}

long contents::get_y() const { return this->y; }
long contents::get_x() const { return this->x; }
long contents::get_desired_x() const { return this->desired_x; }
bool contents::get_waiting_for_desired() const { return this->waiting_for_desired; }

static contents* cont;

void init(std::vector<std::string>* vec) {
    cont = new contents(vec);
    print_init_contents(vec);
}

contents& get_contents() { return *cont; }
