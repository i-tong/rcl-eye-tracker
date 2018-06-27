#include "UtilString.h"


bool checkEndWith(const char* inputStr, const char* endStr) {
    const char * pch;
    pch = std::strstr(inputStr,endStr);
    if (pch != NULL) {
        return true;
    }
    return false;
}

