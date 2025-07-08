# define folder
set(LIB_INCLUDE "${PROJECT_HOME}/include/libcds")
set(UNITTEST_DIR ${CMAKE_CURRENT_LIST_DIR})
set(TEST_DIR "${PROJECT_HOME}/test")

# define common files
set(TEST_HEADERS
    "${UNITTEST_DIR}/Test.hpp"
    "${UNITTEST_DIR}/Test.tpp"
    "${PROJECT_HOME}/include/util.hpp"
)

# define common libcds files
set(LIBCDS_FILES
    "${LIB_INCLUDE}/DataStructure.hpp"
)

# add each of the CPPs separately as they each are meant to be a separate executable.

# ... Linked List
add_executable(LinkedListTester ${TEST_HEADERS} "${UNITTEST_DIR}/LinkedList.cpp" "${LIB_INCLUDE}/LinkedList.hpp" "${LIB_INCLUDE}/LinkedList.tpp" ${LIBCDS_FILES})
source_group("Source Files" FILES "${LIB_INCLUDE}/LinkedList.tpp" "${UNITTEST_DIR}/Test.tpp")
set_target_properties(LinkedListTester PROPERTIES LINKER_LANGUAGE CXX FOLDER "Test")
target_include_directories(LinkedListTester PUBLIC "${PROJECT_HOME}/include")
target_include_directories(LinkedListTester PUBLIC ${TEST_DIR})
install(TARGETS LinkedListTester)

# ... Doubly Linked List
add_executable(DoublyLinkedListTester ${TEST_HEADERS} "${UNITTEST_DIR}/DoublyLinkedList.cpp" "${LIB_INCLUDE}/DoublyLinkedList.hpp" "${LIB_INCLUDE}/DoublyLinkedList.tpp" ${LIBCDS_FILES})
set_target_properties(DoublyLinkedListTester PROPERTIES LINKER_LANGUAGE CXX FOLDER "Test")
source_group("Source Files" FILES "${LIB_INCLUDE}/DoublyLinkedList.tpp" "${UNITTEST_DIR}/Test.tpp")
target_include_directories(DoublyLinkedListTester PUBLIC "${PROJECT_HOME}/include")
target_include_directories(DoublyLinkedListTester PUBLIC ${TEST_DIR})
install(TARGETS DoublyLinkedListTester)

# print about targets.
cmake_print_properties(
    TARGETS LinkedListTester DoublyLinkedListTester
    PROPERTIES SOURCES INCLUDE_DIRECTORIES
)