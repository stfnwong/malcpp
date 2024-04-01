/*
 * VALUE
 * Implements something like MalType as described in the guide
 */

#ifndef __MAL_VALUE_HPP
#define __MAL_VALUE_HPP

#include <string>
#include <vector>

#include "Pointer.hpp"



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


class Value;
using ValuePtr = RcPtr<Value>;
using ValueVec = std::vector<RcPtr<Value>>;


// TODO: Is this just for Substitution?
class Value : public RefCountable
{
	union {
		int i;
		double f;
		bool b;
		// TODO: function pointer...
	} value_data;

	ValueType          type;
	std::string        str;
	ValueVec*          items;

	Value cast_to_int(void) const;
	Value cast_to_float(void) const;

	public:
		Value();
		Value(int i);
		Value(double f);
		//Value(bool b);
		Value(const std::string& s);  // construct an ATOM
		Value(const std::string& s, ValueType t);
		Value(ValueVec* ll);
		~Value();

		// TODO: bool is_number()?

		int         as_int(void) const;
		bool        as_bool(void) const;
		double      as_float(void) const;
		std::string as_str(void) const;
		//// as_list()?

		// Interface for list types
		void     push(ValuePtr v);
		ValuePtr pop(void);
		// TODO: pop_front()?

		// Operators 
		bool operator==(const Value& other) const;
		bool operator!=(const Value& other) const;

		ValueType   get_type(void) const;
		unsigned    len(void) const;

		//ValuePtr    at(unsigned idx) const;

		std::string type_to_str(void) const;
		std::string to_string(void) const;
};


// Some temp wrapper functions
ValuePtr make_list(ValueVec* ll);
ValuePtr make_atom(const std::string& s);
ValuePtr make_digit(double d);



#endif /*__MAL_VALUE_HPP*/
