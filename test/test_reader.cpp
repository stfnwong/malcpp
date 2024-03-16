// Reader Test

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"


#include <iostream>
#include <string>
#include <vector>


#include "Reader.hpp"
#include "Value.hpp"



TEST_CASE("test_tokenize", "reader")
{
	std::string inp = "a b c d e nil true false";
	std::vector<std::string> exp_tokens = {
		"a", "b", "c", "d", "e", "nil", "true", "false", "\0"
	};

	std::vector<std::string> out_tokens = tokenize(inp);

	REQUIRE(out_tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < out_tokens.size(); ++t)
		REQUIRE(out_tokens[t] == exp_tokens[t]);
}


TEST_CASE("test_init_reader", "reader")
{
	std::string source = "(+ a b)";
	std::vector<std::string> exp_tokens = {
		"(", "+", "a", "b", ")"
	};
	std::vector<std::string> tokens = tokenize(source);

	Reader reader(tokens);

	REQUIRE(reader.get_pos() == 0);
	REQUIRE(reader.peek() == "(");   // we should be able to see the first token

	std::vector<std::string> out_tokens;

	while(!reader.at_end())
		out_tokens.push_back(reader.next());

	for(unsigned i = 0; i < exp_tokens.size(); ++i)
		REQUIRE(out_tokens[i] == exp_tokens[i]);
}


TEST_CASE("test_read_list", "reader")
{
	std::string source = "(a b c)";
	std::vector<std::string> exp_tokens = {
		"(", "a", "b", "c", ")", "\0"
	};
	std::vector<std::string> tokens = tokenize(source);

	REQUIRE(tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < tokens.size(); ++t)
		REQUIRE(tokens[t] == exp_tokens[t]);

	Reader reader(tokens);
	REQUIRE(reader.get_pos() == 0);
	REQUIRE(reader.peek() == "(");

	Value out_val = read_form(reader);
	REQUIRE(out_val.get_type() == ValueType::LIST);

	REQUIRE(out_val.len() == 3);
}


TEST_CASE("test_read_nested_list", "reader")
{
	std::string source = "(a, (b, c), (d, e, f))";
	std::vector<std::string> exp_tokens = {
		"(", "a", "(", "b", "c", ")", "(", "d", "e", "f", ")", ")", "\0"
	};

	std::vector<std::string> tokens = tokenize(source);

	REQUIRE(tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < tokens.size(); ++t)
		REQUIRE(tokens[t] == exp_tokens[t]);

	Reader reader(tokens);
	REQUIRE(reader.get_pos() == 0);
	REQUIRE(reader.peek() == "(");

	Value out_val = read_form(reader);

	REQUIRE(out_val.get_type() == ValueType::LIST);
	REQUIRE(out_val.len() == 3);

	// We pop from the back, so check in reverse order
	std::vector<ValueType> exp_value_types = {
		ValueType::LIST,
		ValueType::LIST,
		ValueType::ATOM,
	};

	unsigned ii = 0;
	while(out_val.len() > 0)
	{
		REQUIRE(out_val.pop().get_type() == exp_value_types[ii]);
		ii++;
	}

	// Am testing we get the same output from read_str() here
	Value out_val_read_str = read_str(source);
	REQUIRE(out_val_read_str.get_type() == ValueType::LIST);
	REQUIRE(out_val_read_str.len() == 3);
}
