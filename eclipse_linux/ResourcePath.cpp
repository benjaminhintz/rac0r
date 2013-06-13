/*
 * ResourcePath.cpp
 *
 *  Created on: 13.06.2013
 *      Author: david
 */


#include "ResourcePath.hpp"

std::string Global::__path;

// "magic" stuff is going on here
std::string resourcePath(void)
{

    std::string rpath = Global::__path + "/../assets/";
    return rpath;
}


