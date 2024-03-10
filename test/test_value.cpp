/*
 * Value object tests
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include "Value.hpp"



TEST_CASE("test_create_symbol_value", "value")
{
}


TEST_CASE("test_create_number_value", "value")
{
	NumberValue n1(1.0);

	NumberValue n2("1.0");
}
