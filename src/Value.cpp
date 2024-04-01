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

Value::Value(const std::string& s) : type(ValueType::ATOM), str(s) {}

// By default we assume all strings are atoms, but some of them are strings.
// Pass a type here (ie: pass ValueType::STRING) to construct as a string instead.
Value::Value(const std::string& s, ValueType t) : type(t), str(s) {}

Value::Value(ValueVec* ll) : type(ValueType::LIST), items(ll) {} 


Value::~Value()
{
	switch(this->type)
	{
		case(ValueType::LIST):
			delete this->items;
		default:
			break;
	}
}

//Value::Value(const std::vector<Value>& l) : type(ValueType::LIST), list(l)
//{
//}
//
// TODO: replace all the std::logic_error throws with something better or more specific
//Value Value::cast_to_int(void) const
//{
//	switch(this->type)
//	{
//		case ValueType::INT:
//			return *this;		// TODO: return copy ctor
//		case ValueType::FLOAT:
//			return Value(int(this->value_data.f));
//		default:
//			throw std::logic_error("Cant cast this type to INT");
//	}
//}
//
//// No copy ctor means we return a ref-counted pointer
//Value Value::cast_to_float(void) const
//{
//	switch(this->type)
//	{
//		case ValueType::INT:
//			return Value(double(this->value_data.i));
//		case ValueType::FLOAT:
//			return *this;
//		default:
//			throw std::logic_error("Cant cast this type to FLOAT");
//	}
//}
//

// Get values from this item
//int Value::as_int(void) const
//{
//	return this->cast_to_int().value_data.i;
//}
//
//double Value::as_float(void) const
//{
//	return this->cast_to_float().value_data.f;
//}
//
//std::string Value::as_str(void) const
//{
//	switch(this->type)
//	{
//		case ValueType::ATOM:
//		case ValueType::STRING:
//			return this->str;
//		default:
//			throw std::logic_error("Not a string type");
//	}
//}


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
			return this->list == other.list;		// TODO: what does this check?
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


// TODO: Do I want a version that returns a const ref?
// TODO: Can we modify in place?
Value Value::at(unsigned idx) const
{
	if(this->type == ValueType::LIST)
	{
		if(idx >= this->list.size())
			throw std::logic_error("Index is out of bounds");
		return this->list[idx];
	}
	else
		return Value();   // we have nothing to actually return
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




ValuePtr make_list(ValueVec* ll)
{
	return RcPtr<Value>(new Value(ll));
}

ValuePtr make_atom(const std::string& s)
{
	return RcPtr<Value>(new Value(s));
}

ValuePtr make_digit(double d)
{
	return RcPtr<Value>(new Value(d));
}


/*
 * Sequence container
 */
MalSequence::MalSequence(std::vector<RcPtr<Value>>* itm) : items(itm) {}

MalSequence::MalSequence(const MalSequence& that) : items(new MalSequence(*that.itm)) {}

MalSequence::~MalSequence()
{
	delete this->items;
}

//RcPtr<Value> MalSequence::first(void) const
//{
//	return this->size() == 0 ? RcPtr<Value>("nil") : *this->items[0];
//}

unsigned MalSequence::size(void) const
{
	return this->items->size();
}
