/*
 * ENVIRONMENT
 * Its fine initally for this to be just an associative map, but I think it may need to
 * be reference counted in the future.
 */


#ifndef __MAL_ENVIRONMENT_HPP
#define __MAL_ENVIRONMENT_HPP


#include <string>
#include <unordered_map>

// This is the most basic environment we could have
using Environment = std::unordered_map<std::string, std::string>;


#endif /*__MAL_ENVIRONMENT_HPP*/
