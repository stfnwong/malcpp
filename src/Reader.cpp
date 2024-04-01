/*
 * READER
 */


#include <iostream>		// TODO: debug only
#include <memory>

#include "Error.hpp"
#include "Reader.hpp"



/*
 * READER
 */
Reader::Reader(const std::string& s) : 
	source(s), cur_token(""), pos(0), line(1), col(1)
{
	this->source.push_back('\0');
	this->next();
	// Can we consume the first token here?
}


bool Reader::is_alphanum(char c) const
{
	// TODO: I think '-' is a legit character for an identifier
    return (std::isalnum(c) || c == '_' || c == '-') ? true : false;
}

char Reader::peek_char(void) const
{
	return this->source[this->pos];
}

char Reader::advance(void)
{
	if(this->at_end())
		return '\0';

	this->pos++;
	if(this->source[pos-1] == '\n')
	{
		this->line++;
		this->col = 0;
	}
	this->col++;

	return this->source[pos-1];
}

std::string Reader::capture_string_literal(void)
{
	unsigned len = 0;
	char c; 

	while(!this->at_end())
	{
		c = this->advance();
		len++;

		if(c == '"')
			break;

		// Skip ahead another character if we see an escaped quote
		if(c == '\\' && this->peek_char() == '"') 
		{
			c = this->advance();
			len++;
		}
	}

	return this->source.substr(this->pos-len-1, len+1);

}

std::string Reader::capture_alphanum(void)
{
	unsigned len = 1;  // we already captured the first char

	while(!this->at_end())
	{
		if(!this->is_alphanum(this->peek_char()))
			break;
		this->advance();
		len++;
	}

	return this->source.substr(this->pos-len, len);
}

std::string Reader::capture_one_char(void)
{
	return std::string(1, this->source[this->pos-1]);
}

std::string Reader::peek(void) const
{
	return this->cur_token;
}


// TODO: have this set this->cur_token, new function signature is
// void Reader::next(void)
std::string Reader::consume(void)
{
	if(this->at_end())
	{
		if(!this->paren_stack.empty())
		{
			std::string err_msg = "Unmatched '" + std::string(this->paren_stack.top().glyph, 1) + "'"; 
			Error(err_msg, this->paren_stack.top().line, this->paren_stack.top().col);
		}
		return "\0";  // make the end a null char
	}

	char c;

	while(1)
	{
		c = this->advance();
		if(c == '\0')
			return "\0";

		if(this->is_alphanum(c))
			return this->capture_alphanum();

		switch(c)
		{
			// eat whitespace
			case ' ':
			case '\n':
			case '\t':
			case ',': 	// apparently we don't capture comma
				continue;

			case '~': {
				if(this->peek_char() == '@')
				{
					this->advance(); // move over that char
					return this->source.substr(this->pos-2, 2); //~@
				}
				return this->source.substr(this->pos-1, 1); // ~
			}
			// Opening single char
			case '[':
			case '{':
			case '(':
				this->paren_stack.push(Paren(c, this->line, this->col));
				return this->source.substr(this->pos-1, 1);

			// Closing single char
			case ']':
			case '}':
			case ')':
				this->paren_stack.pop();
				return this->source.substr(this->pos-1, 1);

			// Regular single char
			case '\'':
			case '`':
			case '^':
				return this->source.substr(this->pos-1, 1);

			case '"':   // capture string literal including quotes
				return this->capture_string_literal();
			case ';': 	//comment token
				while(!this->at_end() && c != '\n')
					c = this->advance();
				continue;

			default:		// capture that single character?
				return this->capture_one_char();
		}
	}

	return "\0";			
}


void Reader::next(void)
{
	this->cur_token = this->consume();
}

bool Reader::at_end(void) const
{
	return (this->pos == this->source.length()-1) ? true : false;
}

unsigned Reader::get_pos(void) const
{
	return this->pos;
}



/*
 * ==== Create value types ==== 
 */
void read_list(Reader& reader, ValueVec* items)
{
	do
	{
		std::string token = reader.peek();
		if(token == ")")
		{
			reader.next();
			return;
		}
		items->push_back(read_form(reader));
	} while(!reader.at_end());
}


ValuePtr read_atom(Reader& reader)
{
	std::string t = reader.peek();
	reader.next();
	
	if(std::isdigit(t[0]))
		return make_digit(std::stod(t));

	// Construct a Symbol token and return that
	return make_atom(t);
}



ValuePtr read_form(Reader& reader)
{
	std::string token = reader.peek();

	if(token[0] == '(')
	{
		reader.next(); 		// consume '('
		
		std::unique_ptr<ValueVec> items(new ValueVec);
		read_list(reader, items.get());
		return make_list(items.release());
	}
	else
		return read_atom(reader);
}


// TODO: how does this fit with the other functions
std::vector<std::string> tokenize(const std::string& source)
{
	std::vector<std::string> tokens;

	Reader t(source);

	do
	{
		tokens.push_back(t.peek());
		t.next();
	} while(t.peek() != "\0");

	return tokens;
}


ValuePtr read_str(const std::string& input)
{
	Reader r(input);

	return read_form(r);
}
