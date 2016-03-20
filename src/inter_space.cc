#include <string>
#include <vector>

namespace vick {

std::string inter_space(const std::vector<std::string>& vec) {
    if (vec.empty())
        return "";
    std::string result;
    for (std::vector<std::string>::size_type i = 0;
         i < vec.size() - 1; i++) {
        result += vec[i];
        result += " ";
    }
    result += vec[vec.size() - 1];
    return result;
}
}
