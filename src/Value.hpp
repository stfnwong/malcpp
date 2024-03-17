/*
 * VALUE
 * Implements something like MalType as described in the guide
 */

#ifndef __MAL_VALUE_HPP
#define __MAL_VALUE_HPP

#include <string>
#include <vector>


enum class ValueType
{
	UNIT,
	ATOM,
	BOOL,
	INT,
	FLOAT,
	STRING,
	LIST
};


// TODO: Is this just for Substitution?
class Value
{
	union {
		int i;
		double f;
		bool b;
		// TODO: function pointer...
	} value_data;

	ValueType          type;
	std::string        str;
	std::vector<Value> list;

	Value cast_to_int(void) const;
	Value cast_to_float(void) const;

	public:
		Value();
		Value(int i);
		Value(double f);
		//Value(bool b);
		Value(const std::string& s);
		Value(const std::vector<Value>& l);

		// TODO: bool is_number()?

		int         as_int(void) const;
		bool        as_bool(void) const;
		double      as_float(void) const;
		std::string as_str(void) const;
		// as_list()?

		// Interface for list types
		void  push(Value v);
		Value pop(void);

		// Operators 
		bool operator==(const Value& other) const;
		bool operator!=(const Value& other) const;

		ValueType   get_type(void) const;
		unsigned    len(void) const;

		std::string type_to_str(void) const;
		std::string to_string(void) const;
};




#endif /*__MAL_VALUE_HPP*/
