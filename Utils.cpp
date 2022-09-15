#pragma once
#include <iostream>
#include <sstream>
#include <sys/uio.h>
#include <math.h>

namespace utils
{
    template <typename T>
    std::string convertNumberToString(const T a_value)
    {
        std::ostringstream out;
        out.precision(6);
        out << std::fixed << a_value;
        return out.str();
    }
}
