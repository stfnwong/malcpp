/*
 * READER
 */

#ifndef __MAL_READER_HPP
#define __MAL_READER_HPP


#include <stack>
#include <string>
#include <vector>

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



// Wraps a list of tokens
// TODO: this gives me nothing - this and the tokenzier should be folded together.
class Reader
{
	// Where are we in the source?
	std::string source;
	std::string cur_token;
	unsigned    pos;
	int         line;
	int         col;
	std::stack<Paren> paren_stack;

	// Internal string functions

	bool is_alphanum(char c) const;
	char peek_char(void) const;
	char advance(void);

	std::string capture_string_literal(void);
	std::string capture_alphanum(void);
	std::string capture_one_char(void);
	std::string consume(void);	

	public:
		Reader(const std::string& source);

		bool        at_end(void) const;
		void        next(void);
		std::string peek(void) const;  // TODO: hide this?
		unsigned    get_pos(void) const;
};


Value read_list(Reader& reader);
Value read_atom(Reader& reader);
Value read_form(Reader& reader);


std::vector<std::string> tokenize(const std::string& source);


Value read_str(const std::string& input);


#endif /*__MAL_READER_HPP*/
