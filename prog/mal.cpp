/*
 * MAL
 * Entrypoint for repl
 */


#include <iostream>
#include <string>

#include "Reader.hpp"
#include "Printer.hpp"


Value READ(const std::string& input)
{
	return read_str(input);
}

Value EVAL(const Value& input)
{
	return input;
}

std::string PRINT(Value& v)
{
	return pr_str(v);
}



int main(int argc, char *argv[])
{
	std::string input;

	while(1)
	{
		std::cout << "> ";
		if(std::getline(std::cin, input))
		{
			auto ast = READ(input);
			auto result = EVAL(ast);
			
			std::cout << PRINT(result) << std::endl;
		}
		else
		{
			std::cout << std::endl;
			break;
		}
	}

	return 0;
}
