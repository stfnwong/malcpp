/*
 * READER
 */


#include <iostream>		// TODO: debug only

#include "Reader.hpp"
#include "Tokenizer.hpp"


Reader::Reader(const std::vector<std::string>& t) : pos(0), tokens(t) {}


bool Reader::at_end(void) const
{
	return (this->pos == this->tokens.size()-1) ? true : false;
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

unsigned Reader::get_pos(void) const
{
	return this->pos;
}



/*
 * ==== Create value types ==== 
 */
Value read_list(Reader& reader)
{
	Value token;
	std::vector<Value> lvec;
	Value list(lvec);

	do
	{
		token = read_form(reader);
		if(token.as_str() == ")")
			return list;

		if(reader.at_end())
			std::cerr << "This is an error that I am not handling" << std::endl;
		list.push(Value(token));
	} while(!reader.at_end());

	return list;
}


Value read_atom(Reader& reader)
{
	if(std::isalpha(reader.peek()[0]))
		return Value(reader.peek());
}


Value read_form(Reader& reader)
{
	char c = reader.peek()[0];

	if(c == '(')
		return read_list(reader);
	else
		return read_atom(reader);
}


// TODO: how does this fit with the other functions
std::vector<std::string> tokenize(const std::string& source)
{
	std::vector<std::string> tokens;

	Tokenizer t(source);

	while(!t.at_end())
		tokens.push_back(t.next());
	tokens.push_back("\0");

	return tokens;
}


void read_str(const std::string& source)
{
	Tokenizer t(source);

	std::vector<std::string> tokens;

	while(!t.at_end())
		tokens.push_back(t.next());

	Reader r(tokens);

	read_form(r);
}
