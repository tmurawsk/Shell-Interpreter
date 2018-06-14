//
// Created by dram on 14.06.18.
//

#include "../src/CommandHistory.h"
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE(All_CommandHistory_Test)

    BOOST_AUTO_TEST_CASE(addCommand_case1) {
        //given
        CommandHistory commandHistory("te.txt");
        std::string command = "cd";
        //when
        commandHistory.addCommand(command);
        // then
        std::string result = commandHistory.getLastComand();

        BOOST_CHECK(result == command);
    }

    BOOST_AUTO_TEST_CASE(addCommand_case2) {
        //given
        CommandHistory commandHistory("te.txt");
        std::string command = "cd";
        //when
        commandHistory.addCommand(command);
        commandHistory.addCommand(command);
        // then
        commandHistory.getLastComand();

        BOOST_CHECK(commandHistory.getLastComand() == command);
    }

BOOST_AUTO_TEST_SUITE_END()