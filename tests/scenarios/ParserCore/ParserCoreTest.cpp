#include <boost/test/unit_test.hpp>
#include "../../../code/include/IniParser.hpp"

BOOST_AUTO_TEST_SUITE(ParserCoreTests)

    BOOST_AUTO_TEST_CASE(GlobalEntriesParsingTests) {
        IniParser parser;
        auto result = parser.parse(R"(..\tests\ini\in\test1_core\globalEntries.ini)");
        BOOST_TEST(result->size() == 7);
        BOOST_TEST(result->get("entry2") == "value2");
        BOOST_TEST(result->get("entry3") == "value3");
        BOOST_TEST(result->get("entry4") == "value4");
        BOOST_TEST(result->get("entry1") == "value3");
        BOOST_TEST(result->get("empty1") == "");
        BOOST_TEST(result->get("empty2") == "");
        BOOST_TEST(result->get("empty 3") == "");
    }

    BOOST_AUTO_TEST_CASE(SectionsParsingTests) {
        IniParser parser;
        auto result = parser.parse(R"(..\tests\ini\in\test1_core\sections.ini)");
        BOOST_TEST(result->size() == 6);

        BOOST_TEST_REQUIRE(result->getSection("section1") != nullptr);
        BOOST_TEST_REQUIRE(result->getSection("section2") != nullptr);
        BOOST_TEST_REQUIRE(result->getSection("emptysection1") != nullptr);
        BOOST_TEST_REQUIRE(result->getSection("emptysection2") != nullptr);
        BOOST_TEST_REQUIRE(result->getSection("override") != nullptr);

        BOOST_TEST(result->getSection("section1")->size() == 2);
        BOOST_TEST(result->getSection("section2")->size() == 3);
        BOOST_TEST(result->getSection("emptysection1")->size() == 0);
        BOOST_TEST(result->getSection("emptysection2")->size() == 0);
        BOOST_TEST(result->getSection("override")->size() == 1);

        BOOST_TEST(result->get("global1") == "globalv1");

        BOOST_TEST(result->getSection("section1")->get("sectionkey1") == "sectionval1");
        BOOST_TEST(result->getSection("section1")->get("global1") == "globalv1");

        BOOST_TEST(result->getSection("section2")->get("sectionkey2") == "sectionval2");
        BOOST_TEST(result->getSection("section2")->get("sectionkey3") == "sectionval3");
        BOOST_TEST(result->getSection("section2")->get("sectionkey4") == "sectionval1");

        BOOST_TEST(result->getSection("emptysection1")->get("whatever") == "");
        BOOST_TEST(result->getSection("emptysection2")->get("whatever") == "");

        BOOST_TEST(result->getSection("override")->get("overridekey3") == "overrideval3");

    }

    BOOST_AUTO_TEST_CASE(CommentsParsingTests) {
        IniParser parser;
        auto result = parser.parse(R"(..\tests\ini\in\test1_core\comments.ini)");

        BOOST_TEST(result->size() == 2);
        BOOST_TEST(result->get("glob") == "");
        BOOST_TEST_REQUIRE(result->getSection("section") != nullptr);
        BOOST_TEST(result->getSection("section")->size() == 1);
        BOOST_TEST(result->getSection("section")->get("key") == "value");

        BOOST_TEST(result->get("keyInComment") == "");
        BOOST_TEST(result->get("keyInComment2") == "");

    }

    BOOST_AUTO_TEST_CASE(ParserSampleRun1) {
        IniParser parser;
        auto result = parser.parse(R"(..\tests\ini\in\test1_core\sample1.ini)");

        BOOST_TEST(result->size() == 5);
        BOOST_TEST(result->get("globalkey1") == "globalvalue1");
        BOOST_TEST(result->get("globalkey2") == "globalvalue2");
        BOOST_TEST(result->get("globalkey3") == "");

        BOOST_TEST_REQUIRE(result->getSection("section1") != nullptr);
        BOOST_TEST(result->getSection("section1")->size() == 1);
        BOOST_TEST(result->getSection("section1")->get("sectionkey1") == "sectionvalue3");

        BOOST_TEST_REQUIRE(result->getSection("section2") != nullptr);
        BOOST_TEST(result->getSection("section2")->size() == 2);
        BOOST_TEST(result->getSection("section2")->get("sectionkey3") == "sectionvalue1");
        BOOST_TEST(result->getSection("section2")->get("sectionkey4") == "sectionvalue1");

    }


BOOST_AUTO_TEST_SUITE_END() // ParserCoreTests
