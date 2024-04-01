// Pointer Test

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"


#include <iostream>
#include <string>
#include <vector>


#include "Pointer.hpp"


struct CountMe : public RefCountable
{
	int a;
	int b;
};


TEST_CASE("test_ref_countable", "pointer")
{
	CountMe c;
}

TEST_CASE("test_init_ref_counted_pointer", "pointer")
{
}

