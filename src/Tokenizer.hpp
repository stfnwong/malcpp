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
	bool at_end(void);
	char peek_char(void);
	char advance(void);

	std::string capture_string_literal(void);
	std::string capture_alphanum(void);
	std::string capture_one_char(void);

	public:
		Tokenizer(const std::string& s) : source(s), pos(0) {}
		std::string next(void);
		std::string peek(void);

};



#endif /*__MAL_TOKENIZE_HPP*/
