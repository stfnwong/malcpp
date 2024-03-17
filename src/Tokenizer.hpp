/*
 * TOKENIZE
 */

#ifndef __MAL_TOKENIZE_HPP
#define __MAL_TOKENIZE_HPP


#include <stack>
#include <string>



struct Paren
{
	char glyph;
	int line;
	int col;
};



class Tokenizer
{
	std::string source;
	unsigned    pos;
	int         line;
	int 		col;
	std::stack<Paren> paren_check;

	bool is_alphanum(char c) const;
	char peek_char(void) const;
	char advance(void);

	std::string capture_string_literal(void);
	std::string capture_alphanum(void);
	std::string capture_one_char(void);

	public:
		Tokenizer(const std::string& s);
		std::string next(void);
		bool at_end(void) const;
};


#endif /*__MAL_TOKENIZE_HPP*/
