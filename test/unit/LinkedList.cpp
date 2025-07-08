// =================================================================
// LinkedList.cpp
//  Description     Unit tests for LinkedList
//  Date            2025.02.22
//  Author          jtpeller
// =================================================================

#include <unit/Test.hpp>
#include <cassert>
#include <iostream>
#include <libcds/LinkedList.hpp>
#include <thread>
#include <util.hpp>

std::string
CdsTest::TestList<CDS::LinkedList<std::string>, std::string>::Generate()
{
    return CdsUtil::string_generator();
}

uint32_t
CdsTest::TestList<CDS::LinkedList<uint32_t>, uint32_t>::Generate()
{
    return CdsUtil::rand_range(0, 250);
}

int
main()
{
    // with int
    printf("Testing LinkedList with uint32_t...");
    CdsTest::TestList<CDS::LinkedList<uint32_t>, uint32_t> ll_uint32_tester;
    ll_uint32_tester.ExecuteManyUnits();
    printf("OK.\n");

    printf("Testing LinkedList with std::string...");
    CdsTest::TestList<CDS::LinkedList<std::string>, std::string> ll_str_tester;
    ll_str_tester.ExecuteManyUnits();
    printf("OK.\n");
    return 0;
}
