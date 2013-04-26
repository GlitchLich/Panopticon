#ifndef PARSINGUTILITIES_H
#define PARSINGUTILITIES_H

#include <iostream>
#include <sstream>
#include <algorithm>

bool is_number(const std::string& s)
{
    bool isNumber = false;
    std::string::const_iterator it = s.begin();
    if(std::count(s.begin(), s.end(), '.')<2)
    {
        while (
               it != s.end() && (
                   std::isdigit(*it) ||
                   ((*it)=='.')
                    )
               ) ++it;
        isNumber = !s.empty() && it == s.end();
    }
    return isNumber;
}

double string_to_double( const std::string& s )
{
    std::istringstream i(s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}
#endif // PARSINGUTILITIES_H
