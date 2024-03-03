/*
 * READER
 */

#ifndef __MAL_READER_HPP
#define __MAL_READER_HPP


#include <string>
#include <vector>


class Reader
{
	unsigned pos;
	std::vector<std::string> tokens;

	public:
		Reader(const std::vector<std::string>& t);

		bool at_end(void) const;
		std::string next(void);
		std::string peek(void) const;
};


std::vector<std::string> tokenize(const std::string& source);


#endif /*__MAL_READER_HPP*/
