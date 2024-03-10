/*
 * Value object tests
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include "Value.hpp"




TEST_CASE("test_create_number_value", "value")
{
	Value v1(1.0f);

	// TODO: if ValueType becomes private then test against a string repr?
	REQUIRE(v1.get_type() == ValueType::FLOAT);

	Value v2(2);
	REQUIRE(v2.get_type() == ValueType::INT);
}
