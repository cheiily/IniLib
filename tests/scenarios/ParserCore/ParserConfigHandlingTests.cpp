#include <boost/test/unit_test.hpp>
#include "../../../code/include/IniParser.hpp"

BOOST_AUTO_TEST_SUITE(ParserConfigHandlingTests)

    BOOST_AUTO_TEST_CASE(CtorAndGetterTests) {
        IniParser parser;
        auto * config = parser.getConfig();
        BOOST_TEST(config->mergeDuplicateSections == true);
    }

    BOOST_AUTO_TEST_CASE(SetterTests) {
        IniParser parser;
        parser.loadConfig({false});
        BOOST_TEST(parser.getConfig()->mergeDuplicateSections == false);
        ParserConfig newConf = {true};
        parser.loadConfig(newConf);
        BOOST_TEST(parser.getConfig()->mergeDuplicateSections == true);
    }

BOOST_AUTO_TEST_SUITE_END()