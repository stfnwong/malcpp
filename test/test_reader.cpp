// Reader Test

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"


#include <iostream>
#include <string>
#include <vector>


#include "Reader.hpp"


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
		"(", "+", "a", "b", ")", "\0"
	};

	std::vector<std::string> tokens = tokenize(source);
	for(unsigned i = 0; i < tokens.size(); ++i)
		std::cout << "[token " << i << "]: " << tokens[i] << std::endl;

	Reader reader(tokens);

	REQUIRE(reader.get_pos() == 0);
	REQUIRE(reader.peek() == "(");   // we should be able to see the first token

	std::vector<std::string> out_tokens;

	while(!reader.at_end())
		out_tokens.push_back(reader.next());

	for(unsigned i = 0; i < out_tokens.size(); ++i)
		std::cout << "[" << i << "]: " << out_tokens[i] << std::endl;

	//for(unsigned i = 0; i < exp_tokens.size(); ++i)
	//	REQUIRE(reader.next() == exp_tokens[i]);
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
	REQUIRE(reader.peek() == "(");

	Value out_val = read_list(reader);
	std::cout << out_val.to_string() << std::endl;
}
