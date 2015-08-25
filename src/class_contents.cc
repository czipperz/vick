#include "class_contents.hh"

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
contents::~contents() {
    if(this->cont) delete this->cont;
}


contents::contents(const contents& other)
    : cont(other.cont),
      y(other.y),
      x(other.x),
      desired_x(other.desired_x),
      waiting_for_desired(other.waiting_for_desired) { }
contents& contents::operator=(const contents& other) {
    if(this != &other) {
        delete this->cont;
        *this->cont               = *other.cont;
        this->y                   = other.y;
        this->x                   = other.x;
        this->desired_x           = other.desired_x;
        this->y_offset            = other.y_offset;
        this->waiting_for_desired =
            other.waiting_for_desired;
    }
    return *this;
}


#if __cplusplus >= 201103L
contents::contents(contents&& other)
    : cont(other.cont),
      y(other.y),
      x(other.x),
      desired_x(other.desired_x),
      waiting_for_desired(other.waiting_for_desired) {
    other.cont = nullptr;
}
contents& contents::operator=(contents&& other) {
    if(this != &other) {
        delete this->cont;
        this->cont                = other.cont;
        other.cont                = NULL;
        this->y                   = other.y;
        this->x                   = other.x;
        this->desired_x           = other.desired_x;
        this->y_offset            = other.y_offset;
        this->waiting_for_desired = other.waiting_for_desired;
    }
    return *this;
}
#endif


void contents::push_back(const std::string& str) {
    this->cont->push_back(str);
}
