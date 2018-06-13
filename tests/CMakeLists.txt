find_package(Boost 1.56.0 REQUIRED COMPONENTS system unit_test_framework)

set(CMAKE_CXX_STANDARD 17)

include_directories(${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(Tests Statement.cpp System.cpp)

target_link_libraries(Tests ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
