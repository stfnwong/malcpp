/*
 * MAL
 * Entrypoint for repl
 */


#include <iostream>
#include <string>

#include "Reader.hpp"
#include "Printer.hpp"


ValuePtr READ(const std::string& input)
{
	return read_str(input);
}

ValuePtr EVAL(ValuePtr input)
{
	return input;
}

std::string PRINT(ValuePtr v)
{
	return pr_str(v);
}

//static std::string rep(const std::string& inp)
//{
//	return PRINT(EVAL(READ(inp)));
//}
//


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
