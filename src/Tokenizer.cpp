/*
 * TOKENIZE
 */


#include "Tokenizer.hpp"



bool Tokenizer::at_end(void)
{
	return (this->pos == this->source.length()-1) ? true : false;
}

char Tokenizer::peek_char(void)
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

std::string Tokenizer::peek(void)
{
	// Get the current token but don't advance
	// Basically advance() but we don't consume
}


/*
  * ```[\[\]{}()'`~^@]```: Captures any special single character, one of
    ```[]{}()'`~^@``` (tokenized).
*/

std::string Tokenizer::next(void)
{
	if(this->at_end())
		return "";

	char c;

	while(1)
	{
		c = this->advance();
		if(c == '\0')
			break;

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
					return this->source.substr(this->pos-1, 2); //~@
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
				while(!this->at_end() || c != '"')
					c = this->advance();
				continue;
			case ';': 	//comment token
				while(!this->at_end() || c != '\n')
					c = this->advance();
				continue;
		}
	}

	return "";			// unreachable
}
