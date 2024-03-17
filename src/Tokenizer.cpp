/*
 * TOKENIZE
 */


#include "Error.hpp"
#include "Tokenizer.hpp"


Tokenizer::Tokenizer(const std::string& s) : source(s), pos(0), line(1), col(1)
{
	this->source.push_back('\0');		// add null termination to input
}

bool Tokenizer::is_alphanum(char c) const
{
	// TODO: I think '-' is a legit character for an identifier
    return (std::isalnum(c) || c == '_' || c == '-') ? true : false;
}

char Tokenizer::peek_char(void) const
{
	return this->source[this->pos];
}

char Tokenizer::advance(void)
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

std::string Tokenizer::capture_string_literal(void)
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

std::string Tokenizer::capture_alphanum(void)
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

std::string Tokenizer::capture_one_char(void)
{
	return std::string(1, this->source[this->pos-1]);
}


/*
 * Entry point for obtaining next token.
 */
std::string Tokenizer::next(void)
{
	if(this->at_end())
	{
		if(!this->paren_check.empty())
		{
			std::string err_msg = "Unmatched '" + std::string(this->paren_check.top().glyph, 1) + "'"; 
			Error(err_msg, this->paren_check.top().line, this->paren_check.top().col);
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
				this->paren_check.push(Paren(c, this->line, this->col));
				return this->source.substr(this->pos-1, 1);

			// Closing single char
			case ']':
			case '}':
			case ')':
				this->paren_check.pop();
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

bool Tokenizer::at_end(void) const
{
	return (this->pos == this->source.length()-1) ? true : false;
}
