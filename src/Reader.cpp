/*
 * READER
 */


#include "Reader.hpp"
#include "Tokenizer.hpp"


Reader::Reader(const std::vector<std::string>& t) : pos(0), tokens(t) {}


bool Reader::at_end(void) const
{
	return (this->pos == this->tokens.size()) ? true : false;
}

std::string Reader::next(void)
{
	if(!this->at_end())
		this->pos++;

	return this->tokens[this->pos-1];
}

std::string Reader::peek(void) const
{
	return this->tokens[this->pos];
}




// TODO: how does this fit with the other functions
std::vector<std::string> tokenize(const std::string& source)
{
	std::vector<std::string> tokens;

	Tokenizer t(source);

	while(!t.at_end())
		tokens.push_back(t.next());

	return tokens;
}
