/*
 * PRINTER
 */

#include "Printer.hpp"


// NOTE: this is already covered in the class definition
std::string pr_str(Value& v)
{
	return v.to_string();

	//switch(v.get_type())
	//{
	//	case ValueType::STRING:
	//		return v.as_str();
	//	case ValueType::LIST:
	//		return v.to_string();
	//}
}

