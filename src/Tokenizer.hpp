/*
 * TOKENIZE
 */

#ifndef __MAL_TOKENIZE_HPP
#define __MAL_TOKENIZE_HPP


#include <string>

// TODO: Do I want typed tokens?

class Tokenizer
{
	std::string source;
	unsigned    pos;

	bool is_alphanum(char c) const;
	bool at_end(void) const;
	char peek_char(void) const;
	char advance(void);

	std::string capture_string_literal(void);
	std::string capture_alphanum(void);
	std::string capture_one_char(void);

	public:
		Tokenizer(const std::string& s);
		std::string next(void);
		std::string peek(void);

};



#endif /*__MAL_TOKENIZE_HPP*/
