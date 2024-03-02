// Tokenizer Test

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"


#include <string>
#include <vector>

#include "Tokenizer.hpp"


TEST_CASE("test_init_tokenizer", "token")
{
	Tokenizer t("a b c");

	// cool story but whats the assert?
}


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
	std::string inp = "~@";
	Tokenizer t(inp);

	std::string out = t.next();

	REQUIRE(out == inp);
}

