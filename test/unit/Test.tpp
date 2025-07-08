// =================================================================
// DataStructure.tpp
//  Description     Defines the necessary Test methods
//  Date            2025.07.05
//  Author          jtpeller
// =================================================================

#include <cassert>
#include <thread>
#include <type_traits>
#include <unit/Test.hpp>
#include <util.hpp>

template <typename T, typename K>
CdsTest::TestList<T, K>::TestList()
{
    // enforce T being a child of IList
    static_assert(std::is_base_of<CDS::IList<K>, T>::value, "Derived not derived from BaseClass");

    // enforce that K has equality operator to itself
    CdsUtil::assertf(__LINE__, CdsUtil::has_operator_equal<K>::value, "Secondary Type missing equal operator");
}

template <typename T, typename K>
K
CdsTest::TestList<T, K>::Generate()
{
    return (*generator)();
}

template <typename T, typename K>
void
CdsTest::TestList<T, K>::ExecuteOneUnit()
{
    // create threads
    std::thread t1(&CdsTest::TestList<T, K>::TestSearch, this);
    std::thread t2(&CdsTest::TestList<T, K>::TestIndexOf, this);
    std::thread t3(&CdsTest::TestList<T, K>::TestSize, this);
    std::thread t4(&CdsTest::TestList<T, K>::TestInsert, this);
    std::thread t5(&CdsTest::TestList<T, K>::TestRemove, this);
    std::thread t6(&CdsTest::TestList<T, K>::TestThreadSafe, this);

    // don't forget to join!
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
}

template <typename T, typename K>
void
CdsTest::TestList<T, K>::ExecuteManyUnits()
{
    printf("Beginning tests...\n");
    size_t testCount = 1000;
    size_t itrCount = testCount / 10;
    for (size_t i = 0; i < testCount; i++)
    {
        ExecuteOneUnit();
        if ((i + 1) % itrCount == 0)
            printf("Completed %d iterations...\n", i + 1);
    }
    printf("Tests Complete.\n");
}

//
// Test Functionality
//

// test the IList search functionality
template <typename T, typename K>
void
CdsTest::TestList<T, K>::TestSearch()
{
    T* list = new T();
    CdsUtil::assertf(__LINE__, !list->Search(Generate()), "List initialized incorrectly.");
    for (size_t i = 0; i < testListSize; ++i)
    {
        K gen = Generate();
        list->Insert(gen);
        CdsUtil::assertf(__LINE__, list->Search(gen), "List unable to find gen value: %d", gen);
    }

    // cleanup!
    delete list;
    list = nullptr;
}

// test the remove functionality
template <typename T, typename K>
void
CdsTest::TestList<T, K>::TestRemove()
{
    // initialize the list
    T* list = new T();
    for (size_t i = 1; i <= testListSize; ++i)
    {
        K gen = Generate();
        list->Insert(gen);
        CdsUtil::assertf(__LINE__, list->Search(gen), "List unable to find gen: %d", gen);
        CdsUtil::assertf(__LINE__, list->Size() == 1, "List size is not 1, got %d", list->Size());
        CdsUtil::assertf(__LINE__, list->Remove(gen), "Unable to remove gen");
        CdsUtil::assertf(__LINE__, !list->Search(gen), "Found gen when it shouldn't");
        CdsUtil::assertf(__LINE__, list->Size() == 0, "Expected size = 0, got size = %d", list->Size());
    }

    // cleanup!
    delete list;
    list = nullptr;
}

// test the IList IndexOf functionality
template <typename T, typename K>
void
CdsTest::TestList<T, K>::TestIndexOf()
{
    T* list = new T();
    for (size_t i = 1; i <= testListSize; ++i)
    {
        K gen = Generate();
        list->Insert(gen);
        CdsUtil::assertf(__LINE__, list->Search(gen), "Unable to find gen");
        CdsUtil::assertf(__LINE__, list->IndexOf(gen) == 0, "Expected index = %d, got index = %d", (i - 1), list->IndexOf(gen));
    }

    // cleanup!
    delete list;
    list = nullptr;
}

// test the IList Size functionality
template <typename T, typename K>
void
CdsTest::TestList<T, K>::TestSize()
{
    T* list = new T();

    // verify with Insert
    for (size_t i = 1; i <= testListSize; ++i)
    {
        K gen = Generate();
        list->Insert(gen);
        CdsUtil::assertf(__LINE__, list->Size() == i, "Size was not equal to %d, got %d", i, list->Size());
    }

    // verify after InsertAt w/ remove
    for (size_t i = 1; i <= testListSize; ++i)
    {
        K gen = Generate();
        CdsUtil::assertf(__LINE__, list->Insert(gen, i - 1), "Expected insertion at %d to succeed", (i - 1));
        CdsUtil::assertf(__LINE__, list->Size() == testListSize + 1, "Expected size = %d, got %d", testListSize + 1, list->Size());
        list->Remove(gen);
        CdsUtil::assertf(__LINE__, list->Size() == testListSize, "Expected size = %d, got %d", testListSize, list->Size());
    }

    // verify after Clear
    list->Clear();
    CdsUtil::assertf(__LINE__, list->Size() == 0, "Expected size = 0, got %d", list->Size());

    // cleanup!
    delete list;
    list = nullptr;
}

// test the IList Insert functionality
template <typename T, typename K>
void
CdsTest::TestList<T, K>::TestInsert()
{
    // generate the values for insert at to use
    K k0 = Generate();
    K k1 = Generate();
    while (k1 == k0)
        k1 = Generate();
    K k2 = Generate();
    while (k2 == k1 || k2 == k0)
        k2 = Generate();
    K k3 = Generate();
    while (k3 == k2 || k3 == k1 || k3 == k0)
        k3 = Generate();

    // initialize a list
    T* list = new T();
    list->Insert(k0);
    list->Insert(k0);

    // insert at some other indexes
    CdsUtil::assertf(__LINE__, list->Insert(k1), "Failed to insert k1.");
    CdsUtil::assertf(__LINE__, list->Insert(k2, 2), "Failed to insert k2 at index 2");
    CdsUtil::assertf(__LINE__, !list->Insert(k3, 15), "Insersion succeeded at index that is out of bounds."); // expected to fail

    // ensure has returns properly
    CdsUtil::assertf(__LINE__, list->Search(k1), "Failed to find k1");
    CdsUtil::assertf(__LINE__, list->Search(k2), "Failed to find k2");
    CdsUtil::assertf(__LINE__, !list->Search(k3), "k3 found when it shouldn't have been");

    // ensure index of (on top of has, just for extra checks)
    CdsUtil::assertf(__LINE__, list->IndexOf(k1) == 0, "IndexOf failed to retrieve k1 at expected index 0.");
    CdsUtil::assertf(__LINE__, list->IndexOf(k2) == 2, "IndexOf failed to retrieve k2 at expected index 2.");
    CdsUtil::assertf(__LINE__, list->IndexOf(k3) == list->npos, "IndexOf managed to find k3, somehow.");

    // cleanup!
    delete list;
    list = nullptr;
}

// test thread safe
template <typename T, typename K>
void
CdsTest::TestList<T, K>::TestThreadSafe()
{
    // initialize list
    T* list = new T();
    K notSpecial = Generate();
    list->Insert(notSpecial);
    list->Insert(notSpecial);
    list->Insert(notSpecial);

    // create and enforce a unique special value
    K special = Generate();
    while (special == notSpecial)
        special = Generate();

    list->Insert(special);

    // create lambdas
    auto testInsert = [&](T* list) -> void
    {
        // create a relatively long and sporadic hold on the list
        size_t many_times = 20000;
        for (size_t i = 0; i <= many_times; ++i)
            list->Insert(notSpecial);
    };

    auto testRemove = [&](T* list) -> void
    {
        list->Remove(special);
    };

    // begin threads
    std::thread tts1(testInsert, list);
    std::thread tts2(testRemove, list);

    // join
    tts1.join();
    tts2.join();

    // ASSERT that removal doesn't exist
    CdsUtil::assertf(__LINE__, !list->Search(special), "Found special value, even though it shouldn't have.");

    // cleanup!
    delete list;
    list = nullptr;
}
