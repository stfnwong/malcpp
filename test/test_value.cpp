/*
 * Value object tests
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

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
