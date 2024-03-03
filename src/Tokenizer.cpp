/*
 * TOKENIZE
 */


#include "Tokenizer.hpp"

Tokenizer::Tokenizer(const std::string& s) : source(s), pos(0) 
{
	this->source.push_back('\0');
}

bool Tokenizer::is_alphanum(char c) const
{
	// TODO: I think '-' is a legit character for an identifier
    return (std::isalnum(c) || c == '_' || c == '-') ? true : false;
}

bool Tokenizer::at_end(void) const
{
	return (this->pos == this->source.length()-1) ? true : false;
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

		if(c == '\\' && this->peek_char() == '"')	// if its an escape char
		{
			c = this->advance();
			continue;
		}
		if(c == '"')
			break;
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
	return std::string(1, this->advance());
}

std::string Tokenizer::peek(void)

{
	// Get the current token but don't advance
	// Basically advance() but we don't consume
	return "";		// Shut linter up for now
}


/*
  * ```[\[\]{}()'`~^@]```: Captures any special single character, one of
    ```[]{}()'`~^@``` (tokenized).
*/

std::string Tokenizer::next(void)
{
	if(this->at_end())
		return "\0";  // make the end a null char

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
			case '[':
			case ']':
			case '{':
			case '}':
			case '(':
			case ')':
			case '\'':
			case '`':
			case '^':
				return this->source.substr(this->pos-1, 2);

			// Capture ranges of double quotes
			case '"':
				// Now return the string that captures the start and end quotes;
				return this->capture_string_literal();
			case ';': 	//comment token
				while(!this->at_end() && c != '\n')
					c = this->advance();
				continue;

			default:		// capture that single character?
				return this->capture_one_char();
		}
	}

	return "";			// unreachable
}
