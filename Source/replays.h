#ifndef REPLAYS
#define REPLAYS
#include <string>
#include <iostream>
#include <map>
#include <stdlib.h>
#include "x_values.h"

/// Copyright Gabriel Synnaeve 2011
/// This code is under 3-clauses (new) BSD License

std::string pruneOpeningVal(std::string& input)
{
    // get
    std::string::size_type loc = input.find("Protoss_Opening");
    if (loc == std::string::npos)
        loc = input.find("Zerg_Opening");
    if (loc == std::string::npos)
        loc = input.find("Terran_Opening");
    if (loc == std::string::npos)
    {
        std::cout << "ERROR: no Opening label" << std::endl;
        return "";
    }
    std::string::size_type begin = input.find_first_of(' ', loc);
    std::string::size_type end = input.find_first_of(';', begin);
    if (begin == std::string::npos || end == std::string::npos)
    {
        std::cout << "ERROR: bad Opening label formatting" << std::endl;
        return "";
    }
    std::string r = input.substr(begin+1, end-begin-1);
    // remove
    input.erase(loc, end-loc+1);
    return r;
}

void getBuildings(std::string str, 
        std::multimap<int, Building>& b,
        unsigned int cutoffseconds = 0)
{
    while (str.length() > 2)
    {
        ///std::cout << "STR: " << str << std::endl;
        std::string::size_type loc = str.find_first_not_of(' ');
        std::string::size_type begin = str.find_first_of(' ', loc);
        std::string::size_type end = str.find_first_of(';', begin);
        ///std::cout << str.substr(begin+1, end-begin-1) << " ::: "
        ///    << "|" << str.substr(loc, begin-loc) << "|"
        ///    << " [Begin: " << begin << "]"
        ///    << " [End: " << end << "]"
        ///    << std::endl;
        Building tmpBuilding(str.substr(loc, begin-loc).c_str());
        if (cutoffseconds == 0 ||
                atoi(str.substr(begin+1, end-begin-1).c_str()) < cutoffseconds)
            b.insert(std::make_pair<int, Building>(
                        atoi(str.substr(begin+1, end-begin-1).c_str()), 
                        tmpBuilding));
        if (str.length() <= end+1)
            str.erase();
        else 
            str.erase(0, end+1);
    }
}

#endif
