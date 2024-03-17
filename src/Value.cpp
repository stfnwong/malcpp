/*
 * VALUE
 */

#include <iomanip>
#include <sstream>
#include <stdexcept>

#include "Value.hpp"

// TODO: an Error class?

Value::Value() : type(ValueType::UNIT) {}


Value::Value(int i) : type(ValueType::INT)
{
	this->value_data.i = i;
}

Value::Value(double f) : type(ValueType::FLOAT)
{
	this->value_data.f = f;
}

//Value::Value(bool b) : type(ValueType::BOOL)
//{
//	this->value_data.b = b;
//}

Value::Value(const std::string& s) : type(ValueType::ATOM)
{
	this->str = s;
}

Value::Value(const std::vector<Value>& l) : type(ValueType::LIST), list(l)
{
}

// TODO: replace all the std::logic_error throws with something better or more specific
Value Value::cast_to_int(void) const
{
	switch(this->type)
	{
		case ValueType::INT:
			return *this;		// TODO: return copy ctor
		case ValueType::FLOAT:
			return Value(int(this->value_data.f));
		default:
			throw std::logic_error("Cant cast this type to INT");
	}
}

Value Value::cast_to_float(void) const
{
	switch(this->type)
	{
		case ValueType::INT:
			return Value(double(this->value_data.i));
		case ValueType::FLOAT:
			return *this;
		default:
			throw std::logic_error("Cant cast this type to FLOAT");
	}
}

// Get values from this item
int Value::as_int(void) const
{
	return this->cast_to_int().value_data.i;
}

double Value::as_float(void) const
{
	return this->cast_to_float().value_data.f;
}

std::string Value::as_str(void) const
{
	switch(this->type)
	{
		case ValueType::ATOM:
		case ValueType::STRING:
			return this->str;
		default:
			throw std::logic_error("Not a string type");
	}
}


// TODO: pass by const ref?
void Value::push(Value v)
{
	if(this->type != ValueType::LIST)
		throw std::logic_error("This isn't a list");

	this->list.push_back(v);
}


Value Value::pop(void)
{
	if(this->type != ValueType::LIST)
		throw std::logic_error("This isn't a list");

	Value v = this->list.back();
	this->list.pop_back();

	return v;
}

// Operators 
bool Value::operator==(const Value& other) const
{
	if(this->type != other.type)
		return false;

	switch(this->type)
	{
		case ValueType::INT:
			return this->value_data.i == other.value_data.i;
		case ValueType::FLOAT:
			return this->value_data.f == other.value_data.f;
		case ValueType::BOOL:
			return this->value_data.b == other.value_data.b;
		case ValueType::LIST:
			return this->list == other.list;
		default:
			return false;
	}
}

bool Value::operator!=(const Value& other) const
{
	return !(*this == other);
}

ValueType Value::get_type(void) const
{
	return this->type;
}

unsigned Value::len(void) const
{
	switch(this->type)
	{
		case ValueType::LIST:
			return this->list.size();
		case ValueType::STRING:
			return this->str.size();
		default:
			return 1;
	}
}


std::string Value::type_to_str(void) const
{
	switch(this->type)
	{
		case ValueType::UNIT: return "UNIT";
		case ValueType::ATOM: return "ATOM";
		case ValueType::BOOL: return "BOOL";
		case ValueType::INT: return "INT";
		case ValueType::FLOAT: return "FLOAT";
		case ValueType::STRING: return "STRING";
		case ValueType::LIST: return "LIST";
		default: return "UNKNOWN";
	}
}

std::string Value::to_string(void) const
{
	std::ostringstream oss;

	if(this->type == ValueType::LIST)
	{
		oss << "(";
		for(unsigned i = 0; i < this->list.size(); ++i)
		{
			oss << this->list[i].to_string();
			if(i < this->list.size()-1)
				oss << ", ";
		}
		oss << ")";
	}
	else if(this->type == ValueType::STRING || 
			this->type == ValueType::ATOM)
		oss << this->str;
	// This is dumb - how is std::setprecision supposed to work?
	else if(this->type == ValueType::FLOAT)
		oss << std::dec << std::setw(3) << std::setprecision(4) << std::to_string(this->value_data.f);
	else if(this->type == ValueType::INT)
		oss << std::to_string(this->value_data.i);
	else if(this->type == ValueType::BOOL)
		oss << std::to_string(this->value_data.b);
	else
		oss << "Value";

	return oss.str();
}

