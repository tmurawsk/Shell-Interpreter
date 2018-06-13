//
// Created by dram on 13.06.18.
//

#include "../src/System.h"
#include "../src/Exceptions.h"
#include <boost/test/unit_test.hpp>
#include <unistd.h>

BOOST_AUTO_TEST_SUITE(All_system_tests)

    BOOST_AUTO_TEST_CASE(get_user_case1) {

        // then
        BOOST_CHECK_NO_THROW(System::getUser());

    }
    BOOST_AUTO_TEST_CASE(get_user_case2) {
        // given
        std::string userStr;

        struct passwd * user;
        user = getpwuid(getuid());

        if(user->pw_name != nullptr)
            userStr = std::string(user->pw_name);

        // when
        std::string result = System::getUser();

        // then
        BOOST_CHECK(userStr == result);

    }

    BOOST_AUTO_TEST_CASE(get_host_case1) {

        // then
        BOOST_CHECK_NO_THROW(System::getHost());

    }

    BOOST_AUTO_TEST_CASE(get_dir_case1) {

        // then
        BOOST_CHECK_NO_THROW(System::getDir());

    }

BOOST_AUTO_TEST_SUITE_END()