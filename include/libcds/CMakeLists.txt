# collect headers
set(HEADER_FILES
    "${PROJECT_HOME}/include/libcds/DataStructure.hpp"
    "${PROJECT_HOME}/include/libcds/LinkedList.hpp"
    "${PROJECT_HOME}/include/libcds/DoublyLinkedList.hpp"
)

# collect source (TPPs)
set(SOURCE_FILES
    "${PROJECT_HOME}/include/libcds/LinkedList.tpp"
    "${PROJECT_HOME}/include/libcds/DoublyLinkedList.tpp"
)

source_group("Source Files" FILES ${SOURCE_FILES})

# add the library
add_library(libcds
    SHARED ${SOURCE_FILES} ${HEADER_FILES}
)
set_target_properties(libcds PROPERTIES LINKER_LANGUAGE CXX FOLDER "Library")

# add sources to target
target_sources(libcds PRIVATE ${SOURCE_FILES} PUBLIC ${HEADER_FILES})

# add include
target_include_directories(libcds PUBLIC "${PROJECT_HOME}/include")

# add to install
install(TARGETS libcds)

# print details
cmake_print_properties(
    TARGETS libcds
    PROPERTIES SOURCES LIBRARY_OUTPUT_DIRECTORY
)
