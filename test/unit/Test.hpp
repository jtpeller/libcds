// =================================================================
// Test.hpp
//  Description     Unit Tester class
//  Date            2025.06.30
//  Author          jtpeller
// =================================================================

#ifndef CDSTEST_TEST_HPP
#define CDSTEST_TEST_HPP

#include <iostream>
#include <libcds/DataStructure.hpp>
#include <string>
#include <thread>
#include <vector>

namespace CdsTest
{
    template <typename T, typename K>
    class ITestDS
    {
    public:
        virtual K Generate() = 0;

        virtual void ExecuteOneUnit() = 0;
        virtual void ExecuteManyUnits() = 0;
    };

    template <typename T, typename K>
    class TestList : ITestDS<T, K>
    {
    private:
        size_t testListSize = 10;

    public:
        TestList();

        ~TestList() {}

        K Generate() override;

        // essential test drivers
        void ExecuteOneUnit();
        void ExecuteManyUnits();

        // test methods of IList

        // ... test IDataStructure members
        void TestSearch();
        void TestRemove();
        void TestSize();

        // .. test IList members
        void TestIndexOf();
        void TestInsert();

        // ... test thread-safety
        void TestThreadSafe();
    };
} // namespace CdsTest

#include <unit/Test.tpp>

#endif // CDSTEST_TEST_HPP
