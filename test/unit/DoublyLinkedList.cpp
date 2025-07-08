// =================================================================
// DoublyLinkedList.cpp
//  Description     Unit tests for DoublyLinkedList
//  Date            2025.02.22
//  Author          jtpeller
// =================================================================

#include <unit/Test.hpp>
#include <cassert>
#include <iostream>
#include <libcds/DoublyLinkedList.hpp>
#include <thread>
#include <util.hpp>

std::string
CdsTest::TestList<CDS::DoublyLinkedList<std::string>, std::string>::Generate()
{
    return CdsUtil::string_generator();
}

uint32_t
CdsTest::TestList<CDS::DoublyLinkedList<uint32_t>, uint32_t>::Generate()
{
    return CdsUtil::rand_range(0, 250);
}

int
main()
{
    printf("Testing DoublyLinkedList with uint32_t...\n");
    CdsTest::TestList<CDS::DoublyLinkedList<uint32_t>, uint32_t> dll_uint32_tester;
    dll_uint32_tester.ExecuteManyUnits();
    printf("OK.\n");

    printf("Testing DoublyLinkedList with std::string...\n");
    CdsTest::TestList<CDS::DoublyLinkedList<std::string>, std::string> dll_str_tester;
    dll_str_tester.ExecuteManyUnits();
    printf("OK.\n");
    return 0;
}
