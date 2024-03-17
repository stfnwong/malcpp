/*
 * ERROR
 */

#include <iostream>
#include <iomanip>

#include "Error.hpp"



void Error(const std::string& msg, int line, int col)
{
	std::cerr << "[ERR] (line " << std::dec << line << ":" << col << ")" 
		<< " - " << msg << std::endl;
}
