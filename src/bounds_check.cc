#include "bounds_check.hh"

namespace vick {

void bounds_check(contents& contents) {
    if(contents.cont.size() == 0) {
        contents.cont.push_back("");
        contents.y = 0;
        contents.x = 0;
        return;
    }
    // if (contents.y < 0) contents.y = 0;
    // else 
        if (contents.y >= contents.cont.size())
            contents.y = contents.cont.size() - 1;
    // if (contents.x < 0) contents.x = 0;
    // else 
        if (contents.x >= contents.cont[contents.y].length())
            contents.x = contents.cont[contents.y].length() - 1;
}

}
