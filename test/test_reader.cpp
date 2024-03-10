// Reader Test

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"


#include <string>
#include <vector>


#include "Reader.hpp"


TEST_CASE("test_tokenize", "reader")
{
	std::string inp = "a b c d e nil true false";
	std::vector<std::string> exp_tokens = {
		"a", "b", "c", "d", "e", "nil", "true", "false"
	};

	std::vector<std::string> out_tokens = tokenize(inp);

	REQUIRE(out_tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < out_tokens.size(); ++t)
		REQUIRE(out_tokens[t] == exp_tokens[t]);
}


//TEST_CASE("test_init_reader", "reader")
//{
//	std::string source = "(+ a b);";
//	std::vector<std::string> exp_tokens = {
//	};
//}
//


TEST_CASE("test_read_list", "reader")
{
}
