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
	std::vector<std::string> exp_outputs = {
		"[", "]", "(", ")", "{", "}"
	};
	std::vector<std::string> tok_outputs;

	Tokenizer t(inp);

	while(1)
	{
		std::string out = t.next();
		if(out == "")
			break;
		tok_outputs.push_back(out);
	}

	REQUIRE(tok_outputs.size() == exp_outputs.size());
}

TEST_CASE("test_tokenize_special_character", "token")
{
	std::string out;
	std::string inp = "~@       ~@";		// Can we get ~@ from a string?

	Tokenizer t(inp);

	out = t.next();
	REQUIRE(out == "~@");

	out = t.next();
	REQUIRE(out == "~@");

	out = t.next();
	REQUIRE(out == "");
}

TEST_CASE("test_tokenize_alphanum", "token")
{
	std::string inp = "a b c";

	Tokenizer t(inp);

	std::vector<std::string> exp_tokens = {"a", "b", "c"};
	std::vector<std::string> out_tokens;
	std::string out;

	do
	{
		out = t.next();
		out_tokens.push_back(out);
	} while(out.length() > 0);

	REQUIRE(out_tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < out_tokens.size(); ++t)
		REQUIRE(out_tokens[t] == exp_tokens[t]);
	
}

TEST_CASE("test_tokenize_comment", "token")
{
	std::string inp = "a ; none of this should appear in output";

	Tokenizer t(inp);

	// Note that we return an empty token by default
	std::vector<std::string> exp_tokens = {"a", ""};	
	std::vector<std::string> out_tokens;
	std::string out;

	do
	{
		out = t.next();
		out_tokens.push_back(out);
	} while(out.length() > 0);

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
	std::string out = "<sentinel>";

	while(1)
	{
		std::string out = t.next();
		std::cout << "out: " << out << "(size: " << out.size() << ")" << std::endl;
		out_tokens.push_back(out);
		if(out.size() == 0)
			break;
	}

	REQUIRE(out_tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < out_tokens.size(); ++t)
		REQUIRE(out_tokens[t] == exp_tokens[t]);
}

//
//TEST_CASE("test_tokenize_escaped_string", "token")
//{
//}
