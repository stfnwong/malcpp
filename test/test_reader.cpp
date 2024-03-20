// Reader Test

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"


#include <iostream>
#include <string>
#include <vector>


#include "Reader.hpp"
#include "Value.hpp"


TEST_CASE("test_tokenize_single_chars", "token")
{
	std::string inp = "[],(),{}";
	std::vector<std::string> exp_tokens = {
		"[", "]", "(", ")", "{", "}"
	};
	std::vector<std::string> out_tokens;
	std::string out;

	Reader t(inp);

	while(!t.at_end())
	{
		out = t.next();
		out_tokens.push_back(out);
	}

	REQUIRE(out_tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < out_tokens.size(); ++t)
		REQUIRE(out_tokens[t] == exp_tokens[t]);
}


TEST_CASE("test_tokenize_string_with_spaces", "token")
{
	std::string inp = "hello world abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789 (;:() []{}\"'* ;:() []{}\"'* ;:() []{}\"'*)";
	std::vector<std::string> exp_tokens = {
		"hello", "world", "abcdefghijklmnopqrstuvwxyz",
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ", "0123456789", 
		"(", "\0" //NOTE: the ';' makes the rest of the string a comment
		//"(;:() []{}\"'*", ";:() []{}\"'*", ";:()",
		//"[]{}\"'*)"
	};

	std::vector<std::string> out_tokens;
	std::string out;

	Reader t(inp);

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

	Reader t(inp);

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

	Reader t(inp);

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


	// Comment just eats till the end of the input and then fails over
	// to returning a null string.
	std::vector<std::string> exp_tokens = {"a", ""};
	std::vector<std::string> out_tokens;
	std::string out;

	Reader t(inp);

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
	Reader t(inp);

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


	std::vector<std::string> exp_tokens = {
		"a", "\"string\"", "with", "\"another \\\"string\\\" inside\""
	};
	std::vector<std::string> out_tokens;
	std::string out;

	Reader t(inp);

	while(!t.at_end())
	{
		out = t.next();
		out_tokens.push_back(out);
	}

	REQUIRE(out_tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < out_tokens.size(); ++t)
		REQUIRE(out_tokens[t] == exp_tokens[t]);
}


TEST_CASE("test_tokenize_list", "token")
{
	std::string inp = "(a b c)";
	std::vector<std::string> exp_tokens = {
		"(", "a", "b", "c", ")"
	};

	std::string out;
	std::vector<std::string> out_tokens;

	Reader t(inp);

	while(!t.at_end())
	{
		out = t.peek();
		out_tokens.push_back(out);
		//t.next();	// TODO: should this return void?
	}

	for(unsigned t = 0; t < out_tokens.size(); ++t)
		std::cout << "[" << t << "] : " << out_tokens[t] << std::endl;

	REQUIRE(out_tokens.size() == exp_tokens.size());
	for(unsigned t = 0; t < out_tokens.size(); ++t)
		REQUIRE(out_tokens[t] == exp_tokens[t]);
}


// Error handling test 
TEST_CASE("test_unmatched_paren_error", "token")
{
    // Redirect cout
    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

	std::string input =  "(a b (c d)";
	std::vector<std::string> out_tokens;
	std::string out;

	Reader t(input);

	while(out != "\0")
	{
		out = t.next();
		out_tokens.push_back(out);
	}

	std::string output = oss.str();
	//std::cout << oss.str() << std::endl;

	// Reset cout
    std::cout.rdbuf(p_cout_streambuf);

	std::cout << output << std::endl;
}

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


//TEST_CASE("test_init_reader", "reader")
//{
//	std::string source = "(+ a b)";
//	std::vector<std::string> exp_tokens = {
//		"(", "+", "a", "b", ")"
//	};
//	std::vector<std::string> tokens = tokenize(source);
//
//	Reader reader(tokens);
//
//	REQUIRE(reader.get_pos() == 0);
//	REQUIRE(reader.peek() == "(");   // we should be able to see the first token
//
//	std::vector<std::string> out_tokens;
//
//	while(!reader.at_end())
//		out_tokens.push_back(reader.next());
//
//	for(unsigned i = 0; i < exp_tokens.size(); ++i)
//		REQUIRE(out_tokens[i] == exp_tokens[i]);
//}


//TEST_CASE("test_read_list", "reader")
//{
//	std::string source = "(a b c)";
//	std::vector<std::string> exp_tokens = {
//		"(", "a", "b", "c", ")", "\0"
//	};
//	std::vector<std::string> tokens = tokenize(source);
//
//	REQUIRE(tokens.size() == exp_tokens.size());
//	for(unsigned t = 0; t < tokens.size(); ++t)
//		REQUIRE(tokens[t] == exp_tokens[t]);
//
//	Reader reader(tokens);
//	REQUIRE(reader.get_pos() == 0);
//	
//
//	Value out_val = read_form(reader);
//	REQUIRE(out_val.get_type() == ValueType::LIST);
//
//	REQUIRE(out_val.len() == 3);
//}


//TEST_CASE("test_read_nested_list", "reader")
//{
//	std::string source = "(a, (b, c), (d, e, f))";
//	std::vector<std::string> exp_tokens = {
//		"(", "a", "(", "b", "c", ")", "(", "d", "e", "f", ")", ")", "\0"
//	};
//
//	std::vector<std::string> tokens = tokenize(source);
//
//	REQUIRE(tokens.size() == exp_tokens.size());
//	for(unsigned t = 0; t < tokens.size(); ++t)
//		REQUIRE(tokens[t] == exp_tokens[t]);
//
//	Reader reader(tokens);
//	REQUIRE(reader.get_pos() == 0);
//	REQUIRE(reader.peek() == "(");
//
//	Value out_val = read_form(reader);
//
//	REQUIRE(out_val.get_type() == ValueType::LIST);
//	REQUIRE(out_val.len() == 3);
//
//	// We pop from the back, so check in reverse order
//	std::vector<ValueType> exp_value_types = {
//		ValueType::LIST,
//		ValueType::LIST,
//		ValueType::ATOM,
//	};
//
//	unsigned ii = 0;
//	while(out_val.len() > 0)
//	{
//		REQUIRE(out_val.pop().get_type() == exp_value_types[ii]);
//		ii++;
//	}
//
//	// Am testing we get the same output from read_str() here
//	Value out_val_read_str = read_str(source);
//	REQUIRE(out_val_read_str.get_type() == ValueType::LIST);
//	REQUIRE(out_val_read_str.len() == 3);
//}
