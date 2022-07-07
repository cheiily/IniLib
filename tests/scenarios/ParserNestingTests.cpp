#include <boost/test/unit_test.hpp>
#include "../../code/include/IniParser.hpp"

BOOST_AUTO_TEST_SUITE(RelativeNestingParsingTests)

    BOOST_AUTO_TEST_CASE(RelativeNestingWithoutChildAccessor) {
        IniParser parser;
        auto result = parser.parse(R"(..\tests\ini\in\test2_nesting\relativeSectionNesting1.ini)");
        BOOST_TEST_REQUIRE(result.get()->size() == 3);

        auto * main = result->getSection("main");
        auto * branch = result->getSection("branch");
        auto * leaf = result->getSection("leaf");
        
        BOOST_TEST_REQUIRE(main != nullptr);
        BOOST_TEST_REQUIRE(branch != nullptr);
        BOOST_TEST_REQUIRE(leaf != nullptr);

        BOOST_TEST(main->size() == 4);
        BOOST_TEST(branch->size() == 2);
        BOOST_TEST(leaf->size() == 1);
        BOOST_TEST(main->get("key1") == "value1");
        BOOST_TEST(branch->get("key8") == "value8");
        BOOST_TEST(leaf->get("key10") == "value10");
        
        auto * sub1 = main->getSection("sub1");
        auto * sub2 = main->getSection("sub2");
        auto * sub3 = main->getSection("sub3");
        auto * branchsub = branch->getSection("branchsub");

        BOOST_TEST_REQUIRE(sub1 != nullptr);
        BOOST_TEST_REQUIRE(sub2 != nullptr);
        BOOST_TEST_REQUIRE(sub3 != nullptr);
        BOOST_TEST_REQUIRE(branchsub != nullptr);

        BOOST_TEST(sub1->size() == 1);
        BOOST_TEST(sub2->size() == 3);
        BOOST_TEST(sub3->size() == 2);
        BOOST_TEST(branchsub->size() == 1);
        BOOST_TEST(sub1->get("key2") == "value2");
        BOOST_TEST(sub2->get("key3") == "value3");
        BOOST_TEST(sub3->get("key6") == "value6");
        BOOST_TEST(branch->get("key8") == "value8");
        BOOST_TEST(sub1->getParent() == main);
        BOOST_TEST(sub2->getParent() == main);
        BOOST_TEST(sub3->getParent() == main);
        BOOST_TEST(branchsub->getParent() == branch);
        
        auto * ssub1 = sub2->getSection("ssub1");
        auto * ssub2 = sub2->getSection("ssub2");
        auto * ssub3 = sub3->getSection("ssub3");

        BOOST_TEST_REQUIRE(ssub1 != nullptr);
        BOOST_TEST_REQUIRE(ssub2 != nullptr);
        BOOST_TEST_REQUIRE(ssub3 != nullptr);

        BOOST_TEST(ssub1->size() == 1);
        BOOST_TEST(ssub2->size() == 1);
        BOOST_TEST(ssub3->size() == 1);
        BOOST_TEST(ssub1->get("key4") == "value4");
        BOOST_TEST(ssub2->get("key5") == "value5");
        BOOST_TEST(ssub3->get("key7") == "value7");
        BOOST_TEST(ssub1->getParent() == sub2);
        BOOST_TEST(ssub2->getParent() == sub2);
        BOOST_TEST(ssub3->getParent() == sub3);

    }

    BOOST_AUTO_TEST_CASE(RelativeNestingWithChildAccessor) {
        auto result = IniParser().parse(R"(..\tests\ini\in\test2_nesting\relativeSectionNesting2.ini)");
        BOOST_TEST_REQUIRE(result->size() == 3);

        auto * main = result->getSection("main");
        auto * branch = result->getSection("branch");
        auto * leaf = result->getSection("leaf");

        BOOST_TEST_REQUIRE(main != nullptr);
        BOOST_TEST_REQUIRE(branch != nullptr);
        BOOST_TEST_REQUIRE(leaf != nullptr);

        BOOST_TEST(main->size() == 4);
        BOOST_TEST(branch->size() == 2);
        BOOST_TEST(leaf->size() == 1);
        BOOST_TEST(main->get("key1") == "value1");
        BOOST_TEST(branch->get("key8") == "value8");
        BOOST_TEST(leaf->get("key10") == "value10");

        auto * sub1 = main->getSection("sub1");
        auto * sub2 = main->getSection("sub2");
        auto * sub3 = main->getSection("sub3");
        auto * branchsub = branch->getSection("branchsub");

        BOOST_TEST_REQUIRE(sub1 != nullptr);
        BOOST_TEST_REQUIRE(sub2 != nullptr);
        BOOST_TEST_REQUIRE(sub3 != nullptr);
        BOOST_TEST_REQUIRE(branchsub != nullptr);

        BOOST_TEST(sub1->size() == 1);
        BOOST_TEST(sub2->size() == 3);
        BOOST_TEST(sub3->size() == 2);
        BOOST_TEST(branchsub->size() == 1);
        BOOST_TEST(sub1->get("key2") == "value2");
        BOOST_TEST(sub2->get("key3") == "value3");
        BOOST_TEST(sub3->get("key6") == "value6");
        BOOST_TEST(branch->get("key8") == "value8");
        BOOST_TEST(sub1->getParent() == main);
        BOOST_TEST(sub2->getParent() == main);
        BOOST_TEST(sub3->getParent() == main);
        BOOST_TEST(branchsub->getParent() == branch);

        auto * ssub1 = sub2->getSection("ssub1");
        auto * ssub2 = sub2->getSection("ssub2");
        auto * ssub3 = sub3->getSection("ssub3");

        BOOST_TEST_REQUIRE(ssub1 != nullptr);
        BOOST_TEST_REQUIRE(ssub2 != nullptr);
        BOOST_TEST_REQUIRE(ssub3 != nullptr);

        BOOST_TEST(ssub1->size() == 1);
        BOOST_TEST(ssub2->size() == 1);
        BOOST_TEST(ssub3->size() == 1);
        BOOST_TEST(ssub1->get("key4") == "value4");
        BOOST_TEST(ssub2->get("key5") == "value5");
        BOOST_TEST(ssub3->get("key7") == "value7");
        BOOST_TEST(ssub1->getParent() == sub2);
        BOOST_TEST(ssub2->getParent() == sub2);
        BOOST_TEST(ssub3->getParent() == sub3);
    }

BOOST_AUTO_TEST_SUITE_END() // RelativeNesting



BOOST_AUTO_TEST_SUITE(AbsoluteNestingParsingTests)

    BOOST_AUTO_TEST_CASE(AbsoluteNestingWithoutGlobalAccessor) {
        auto result = IniParser().parse(R"(..\tests\ini\in\test2_nesting\absoluteSectionNesting1.ini)");
        BOOST_TEST_REQUIRE(result->size() == 3);

        auto * main = result->getSection("main");
        auto * branch = result->getSection("branch");
        auto * leaf = result->getSection("leaf");

        BOOST_TEST_REQUIRE(main != nullptr);
        BOOST_TEST_REQUIRE(branch != nullptr);
        BOOST_TEST_REQUIRE(leaf != nullptr);

        BOOST_TEST(main->size() == 4);
        BOOST_TEST(branch->size() == 2);
        BOOST_TEST(leaf->size() == 1);
        BOOST_TEST(main->get("key1") == "value1");
        BOOST_TEST(branch->get("key8") == "value8");
        BOOST_TEST(leaf->get("key10") == "value10");

        auto * sub1 = main->getSection("sub1");
        auto * sub2 = main->getSection("sub2");
        auto * sub3 = main->getSection("sub3");
        auto * branchsub = branch->getSection("branchsub");

        BOOST_TEST_REQUIRE(sub1 != nullptr);
        BOOST_TEST_REQUIRE(sub2 != nullptr);
        BOOST_TEST_REQUIRE(sub3 != nullptr);
        BOOST_TEST_REQUIRE(branchsub != nullptr);

        BOOST_TEST(sub1->size() == 1);
        BOOST_TEST(sub2->size() == 3);
        BOOST_TEST(sub3->size() == 2);
        BOOST_TEST(branchsub->size() == 1);
        BOOST_TEST(sub1->get("key2") == "value2");
        BOOST_TEST(sub2->get("key3") == "value3");
        BOOST_TEST(sub3->get("key6") == "value6");
        BOOST_TEST(branch->get("key8") == "value8");
        BOOST_TEST(sub1->getParent() == main);
        BOOST_TEST(sub2->getParent() == main);
        BOOST_TEST(sub3->getParent() == main);
        BOOST_TEST(branchsub->getParent() == branch);

        auto * ssub1 = sub2->getSection("ssub1");
        auto * ssub2 = sub2->getSection("ssub2");
        auto * ssub3 = sub3->getSection("ssub3");

        BOOST_TEST_REQUIRE(ssub1 != nullptr);
        BOOST_TEST_REQUIRE(ssub2 != nullptr);
        BOOST_TEST_REQUIRE(ssub3 != nullptr);

        BOOST_TEST(ssub1->size() == 1);
        BOOST_TEST(ssub2->size() == 1);
        BOOST_TEST(ssub3->size() == 1);
        BOOST_TEST(ssub1->get("key4") == "value4");
        BOOST_TEST(ssub2->get("key5") == "value5");
        BOOST_TEST(ssub3->get("key7") == "value7");
        BOOST_TEST(ssub1->getParent() == sub2);
        BOOST_TEST(ssub2->getParent() == sub2);
        BOOST_TEST(ssub3->getParent() == sub3);

    }

    BOOST_AUTO_TEST_CASE(AbsoluteNestingWithGlobalAccessor) {
        std::unique_ptr<IniSection> result;
        BOOST_CHECK_THROW(result = IniParser().parse(R"(..\tests\ini\in\test2_nesting\absoluteSectionNesting2.ini)"), FeatureIncompleteException);
        BOOST_TEST_MESSAGE("To run this test case, uncomment a matching line (currently 107) in IniParser.cpp");
//        BOOST_TEST_REQUIRE(result->size() == 3);
//
//        auto * main = result->getSection("main");
//        auto * branch = result->getSection("branch");
//        auto * leaf = result->getSection("leaf");
//
//        BOOST_TEST_REQUIRE(main != nullptr);
//        BOOST_TEST_REQUIRE(branch != nullptr);
//        BOOST_TEST_REQUIRE(leaf != nullptr);
//
//        BOOST_TEST(main->size() == 4);
//        BOOST_TEST(branch->size() == 2);
//        BOOST_TEST(leaf->size() == 1);
//        BOOST_TEST(main->get("key1") == "value1");
//        BOOST_TEST(branch->get("key8") == "value8");
//        BOOST_TEST(leaf->get("key10") == "value10");
//
//        auto * sub1 = main->getSection("sub1");
//        auto * sub2 = main->getSection("sub2");
//        auto * sub3 = main->getSection("sub3");
//        auto * branchsub = branch->getSection("branchsub");
//
//        BOOST_TEST_REQUIRE(sub1 != nullptr);
//        BOOST_TEST_REQUIRE(sub2 != nullptr);
//        BOOST_TEST_REQUIRE(sub3 != nullptr);
//        BOOST_TEST_REQUIRE(branchsub != nullptr);
//
//        BOOST_TEST(sub1->size() == 1);
//        BOOST_TEST(sub2->size() == 3);
//        BOOST_TEST(sub3->size() == 2);
//        BOOST_TEST(branchsub->size() == 1);
//        BOOST_TEST(sub1->get("key2") == "value2");
//        BOOST_TEST(sub2->get("key3") == "value3");
//        BOOST_TEST(sub3->get("key6") == "value6");
//        BOOST_TEST(branch->get("key8") == "value8");
//        BOOST_TEST(sub1->getParent() == main);
//        BOOST_TEST(sub2->getParent() == main);
//        BOOST_TEST(sub3->getParent() == main);
//        BOOST_TEST(branchsub->getParent() == branch);
//
//        auto * ssub1 = sub2->getSection("ssub1");
//        auto * ssub2 = sub2->getSection("ssub2");
//        auto * ssub3 = sub3->getSection("ssub3");
//
//        BOOST_TEST_REQUIRE(ssub1 != nullptr);
//        BOOST_TEST_REQUIRE(ssub2 != nullptr);
//        BOOST_TEST_REQUIRE(ssub3 != nullptr);
//
//        BOOST_TEST(ssub1->size() == 1);
//        BOOST_TEST(ssub2->size() == 1);
//        BOOST_TEST(ssub3->size() == 1);
//        BOOST_TEST(ssub1->get("key4") == "value4");
//        BOOST_TEST(ssub2->get("key5") == "value5");
//        BOOST_TEST(ssub3->get("key7") == "value7");
//        BOOST_TEST(ssub1->getParent() == sub2);
//        BOOST_TEST(ssub2->getParent() == sub2);
//        BOOST_TEST(ssub3->getParent() == sub3);

    }

BOOST_AUTO_TEST_SUITE_END() // AbsoluteNesting