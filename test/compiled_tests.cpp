//
// Created by aleksander on 25.07.22.
//

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wparentheses"
// This one is necessary for the const return non-reference test
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#endif

#define CATCH_CONFIG_MAIN
#include "../play/serializer/SerializableStringList.h"

#include "catch.hpp"


TEST_CASE("Two strings are equal")
{
    std::string s1("string");
    std::string s2("string");

    CHECK(s1 == s2);
}

TEST_CASE("String list is properly deserialized")
{
    Bassplay::Play::Serializer::SerializableStringList list;
    std::string s1("string1");
    std::string s2("string2");
    list.add(s1);
    list.add(s2);
    std::string serialized = list.serialize();
    CHECK(serialized == std::string("string1\nstring2"));
}