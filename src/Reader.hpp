/*
 * READER
 */

#ifndef __MAL_READER_HPP
#define __MAL_READER_HPP


#include <string>
#include <vector>

#include "Value.hpp"


// Wraps a list of tokens
class Reader
{
	unsigned pos;
	std::vector<std::string> tokens;

	public:
		Reader(const std::vector<std::string>& t);

		bool        at_end(void) const;
		std::string next(void);
		std::string peek(void) const;
		unsigned    get_pos(void) const;
};


Value read_list(Reader& reader);
Value read_atom(Reader& reader);
Value read_form(Reader& reader);


std::vector<std::string> tokenize(const std::string& source);


Value read_str(const std::string& input);


#endif /*__MAL_READER_HPP*/
