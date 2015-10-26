#include "change.hh"

change_t gen_change()
{
    static change_t n = 0;
    return n++;
}
