/*
 * MAL
 * Entrypoint for repl
 */


#include <iostream>
#include <string>


std::string READ(const std::string& input)
{
	return input;
}

std::string EVAL(const std::string& input)
{
	return input;
}

std::string PRINT(const std::string& input)
{
	return input;
}



int main(int argc, char *argv[])
{
	std::string input;

	while(1)
	{
		std::cout << "> ";
		if(std::getline(std::cin, input))
		{
			std::cout << input << std::endl;
		}
		else
		{
			std::cout << std::endl;
			break;
		}
	}

	return 0;
}
