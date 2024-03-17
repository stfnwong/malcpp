/*
 * READER
 */

#ifndef __MAL_READER_HPP
#define __MAL_READER_HPP


#include <stack>
#include <string>
#include <vector>

#include "Error.hpp"
#include "Value.hpp"

/*
 * Where a parenthesis is (for matching)
 */
struct Paren
{
	char glyph;
	int  line;
	int  col;
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
		bool        at_end(void) const;
};


// Wraps a list of tokens
// TODO: this gives me nothing - this and the tokenzier should be folded together.
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
