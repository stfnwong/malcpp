/*
 * Value object tests
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <memory>
#include "Value.hpp"




TEST_CASE("test_create_number_value", "value")
{
	std::vector<Value> values = {
		Value(1.0f), Value(1), Value(22222.2)
	};
	std::vector<ValueType> exp_types = {
		ValueType::FLOAT, ValueType::INT, ValueType::FLOAT
	};

	std::vector<int> exp_values_as_int = {
		1, 1, 22222
	};

	std::vector<double> exp_values_as_float = {
		1.0, 1.0, 22222.2
	};

	// Ensure I wrote the test properly
	REQUIRE(values.size() == exp_types.size());

	for(unsigned i = 0; i < values.size(); ++i)
	{
		REQUIRE(values[i].get_type() == exp_types[i]);
		REQUIRE(values[i].as_int() == exp_values_as_int[i]);
		REQUIRE(values[i].as_float() == exp_values_as_float[i]);
	}
}


TEST_CASE("test_create_atom_value", "value")
{
	std::vector<Value> values = {
		Value("some string"), Value("another string")
	};
	std::vector<ValueType> exp_types = {
		ValueType::ATOM, ValueType::ATOM
	};
	std::vector<std::string> exp_values_as_string = {
		"some string", "another string"
	};

	REQUIRE(values.size() == exp_types.size());
	for(unsigned i = 0; i < exp_types.size(); ++i)
	{
		REQUIRE(values[i].get_type() == exp_types[i]);
	}
}


TEST_CASE("test_create_list_value", "value")
{
	//std::vector<Value> list_elements = {
	//	Value("string element"), Value(1.0), Value(20)
	//};

	std::vector<RcPtr<Value>> value_ptrs = {
		new Value("string element"), new Value(1.0), new Value(20)
	};

	ValueVec* ll;
	for(auto& p : value_ptrs)
		ll->push_back(p);

	ValuePtr list_value = make_list(ll);

	REQUIRE(list_value->get_type() == ValueType::LIST);
	REQUIRE(list_value->len() == value_ptrs.size());

	// Reverse order since I pop
	std::vector<ValueType> exp_value_types = {
		ValueType::INT,
		ValueType::FLOAT, 
		ValueType::ATOM, 
	};

	// Check I didn't mistype anything
	REQUIRE(exp_value_types.size() == value_ptrs.size());
	for(unsigned i = 0; i < exp_value_types.size(); ++i)
		REQUIRE(exp_value_types[i] == list_value->pop()->get_type());
}
