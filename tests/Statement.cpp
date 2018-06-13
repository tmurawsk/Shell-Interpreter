#define BOOST_TEST_MODULE Tests

#include "../src/Statements/Statement.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(All_statement_tests)

    BOOST_AUTO_TEST_CASE(string_match_pattern_case1) {
        // given
        std::string str = "abc.txt";
        std::string pattern = "*.txt";

        // when
        bool result = Statement::isStringMatchPatern(str, pattern);

        // then
        BOOST_CHECK(result);

    }
    BOOST_AUTO_TEST_CASE(string_match_pattern_case2) {
        // given
        std::string str = "xxaasc.txt";
        std::string pattern = "x*.txt";

        // when
        bool result = Statement::isStringMatchPatern(str, pattern);

        // then
        BOOST_CHECK(result);

    }
    BOOST_AUTO_TEST_CASE(string_match_pattern_case3) {
        // given
        std::string str = "babc.txt";
        std::string pattern = "a*.txt";

        // when
        bool result = Statement::isStringMatchPatern(str, pattern);

        // then
        BOOST_CHECK(!result);
    }

    BOOST_AUTO_TEST_CASE(string_match_pattern_case4) {
        // given
        std::string str = "abc.txt";
        std::string pattern = "abc.txt";

        // when
        bool result = Statement::isStringMatchPatern(str, pattern);

        // then
        BOOST_CHECK(result);

    }

    BOOST_AUTO_TEST_CASE(string_match_pattern_case5) {
        // given
        std::string str = "abbc.txt";
        std::string pattern = "a?c.txt";

        // when
        bool result = Statement::isStringMatchPatern(str, pattern);

        // then
        BOOST_CHECK(!result);
    }


    BOOST_AUTO_TEST_CASE(string_match_pattern_case6) {
        // given
        std::string str = "abc.txt";
        std::string pattern = "*";

        // when
        bool result = Statement::isStringMatchPatern(str, pattern);

        // then
        BOOST_CHECK(result);

    }

    //empty case
    BOOST_AUTO_TEST_CASE(string_match_pattern_case7) {
        // given
        std::string str = "abc.txt";
        std::string pattern = "abc*.txt";

        // when
        bool result = Statement::isStringMatchPatern(str, pattern);

        // then
        BOOST_CHECK(result);

    }

    // ? match to not null
    BOOST_AUTO_TEST_CASE(string_match_pattern_case8) {
        // given
        std::string str = "abc.txt";
        std::string pattern = "a?bc.txt";

        // when
        bool result = Statement::isStringMatchPatern(str, pattern);

        // then
        BOOST_CHECK(!result);

    }

BOOST_AUTO_TEST_SUITE_END()