// Tokenizer Test

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"


#include <iostream>
#include <string>
#include <vector>

#include "Tokenizer.hpp"



TEST_CASE("test_tokenize_single_chars", "token")
{
	std::string inp = "[],(),{}";
	std::vector<std::string> exp_tokens = {
		"[", "]", "(", ")", "{", "}"
	};
	std::vector<std::string> out_tokens;
	std::string out;

	Tokenizer t(inp);

	while(!t.at_end())
	{
		out = t.next();
		out_tokens.push_back(out);
	}

	REQUIRE(out_tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < out_tokens.size(); ++t)
		REQUIRE(out_tokens[t] == exp_tokens[t]);
}


TEST_CASE("test_tokenize_special_character", "token")
{
	std::string out;
	std::string inp = "~@ ~@       ~@";		// Can we get ~@ from a string?

	Tokenizer t(inp);

	// Note empty token at the end, this is a consequence of the do-while loop
	std::vector<std::string> exp_tokens = {"~@", "~@", "~@"};
	std::vector<std::string> out_tokens;

	while(!t.at_end())
	{
		out = t.next();
		out_tokens.push_back(out);
	}

	REQUIRE(out_tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < out_tokens.size(); ++t)
		REQUIRE(out_tokens[t] == exp_tokens[t]);
}


TEST_CASE("test_tokenize_alphanum", "token")
{
	std::string inp = "a b c,     true false nil";

	Tokenizer t(inp);

	std::vector<std::string> exp_tokens = {
		"a", "b", "c", "true", "false", "nil"
	};
	std::vector<std::string> out_tokens;
	std::string out;

	while(!t.at_end())
	{
		out = t.next();
		out_tokens.push_back(out);
	}

	REQUIRE(out_tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < out_tokens.size(); ++t)
		REQUIRE(out_tokens[t] == exp_tokens[t]);
}


TEST_CASE("test_tokenize_comment", "token")
{
	std::string inp = "a ; none of this should appear in output";

	Tokenizer t(inp);

	// Comment just eats till the end of the input and then fails over
	// to returning a null string.
	std::vector<std::string> exp_tokens = {"a", ""};
	std::vector<std::string> out_tokens;
	std::string out;

	while(!t.at_end())
	{
		out = t.next();
		out_tokens.push_back(out);
	}

	REQUIRE(out_tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < out_tokens.size(); ++t)
		REQUIRE(out_tokens[t] == exp_tokens[t]);
}



TEST_CASE("test_tokenize_string", "token")
{
	std::string inp = "a string \"of text\"";
	Tokenizer t(inp);

	std::vector<std::string> exp_tokens = {
		"a", "string", "\"of text\""
	};
	std::vector<std::string> out_tokens;
	std::string out;

	while(!t.at_end())
	{
		out = t.next();
		out_tokens.push_back(out);
	} 

	REQUIRE(out_tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < out_tokens.size(); ++t)
		REQUIRE(out_tokens[t] == exp_tokens[t]);
}


TEST_CASE("test_tokenize_escaped_string", "token")
{
	std::string inp = "a \"string\" with \"another \\\"string\\\" inside\"";

	Tokenizer t(inp);

	std::vector<std::string> exp_tokens = {
		"a", "\"string\"", "with", "\"another \\\"string\\\" inside\""
	};
	std::vector<std::string> out_tokens;
	std::string out;

	while(!t.at_end())
	{
		out = t.next();
		out_tokens.push_back(out);
	}

	REQUIRE(out_tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < out_tokens.size(); ++t)
		REQUIRE(out_tokens[t] == exp_tokens[t]);
}
