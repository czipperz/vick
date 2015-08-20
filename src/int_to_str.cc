#include <string>
#include <vector>

static char int_to_char(int num) {
    if(num < 10 && num >= 0) return num + 48;
    return '*';
}

std::string int_to_str(int num) {
    if(num == 0) return "0";
    if(num < 0) return std::string("-") + int_to_str(-num);
    int digits = 0, process = num, single;
    std::string numString;
    //count number of digits
    while(process != 0) {
        single = process % 10;
        process = (process - single)/10;
        digits++;
    }
    process = num;
    numString.reserve(digits);
    for(int i = 0; i < digits; i++)
        numString += '*';
    for(int i = digits - 1; i >= 0; i--) {
        single = process % 10;
        numString[i] = int_to_char(single);
        process = (process - single) / 10;
    }
    return numString;
}

std::string bool_to_str(bool b) {
    if(b) return "true";
    return "false";
}

std::string inter_space(const std::vector<std::string>* vec) {
    std::string result;
    for(int i = 0; i < vec->size() - 1; i++) {
        result += (*vec)[i];
        result += " ";
    }
    result += (*vec)[vec->size() - 1];
    return result;
}
