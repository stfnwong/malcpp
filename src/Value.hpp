/*
 * VALUE
 * Implements something like MalType as described in the guide
 */

#ifndef __MAL_VALUE_HPP
#define __MAL_VALUE_HPP

#include <string>
#include <vector>


// TODO: Is this just for Substitution?
class Value
{
	enum class ValueType
	{
		ATOM,
		FLOAT,
		STRING,
		LIST
	};

	union {
		int i;
		double f;
		// TODO: function pointer...
	} value_data;

	std::string str;
	std::vector<Value> list;
};


class ListValue : public Value
{
	std::vector<Value> list;

	public:
		ListValue() {}  // TODO: how do we construct this?
		void add(Value v);
};


class SymbolValue : public Value
{
	std::string symbol;

	public:
		SymbolValue(const std::string& s) : symbol(s) {} 
};


class NumberValue : public Value
{
	float value;

	public:
		NumberValue(float v) : value(v) {} 
		NumberValue(const std::string& s) : value(std::stof(s)) {} 
};



#endif /*__MAL_VALUE_HPP*/
