#include "../../code/include/IniSection.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(General)

    BOOST_AUTO_TEST_SUITE(Ctors)

        BOOST_AUTO_TEST_SUITE(ObjectCreation)

            BOOST_AUTO_TEST_CASE(ExplicitCtor) {
                auto * s = new IniSection(nullptr);
                BOOST_TEST_REQUIRE(s != nullptr);
                delete s;
            }

            BOOST_AUTO_TEST_CASE(CopyCtorNegative) {
                BOOST_TEST_REQUIRE(!std::is_copy_constructible<IniSection>());
            }

            BOOST_AUTO_TEST_CASE(MoveCtor) {
                IniSection arg(nullptr);
                auto * s = new IniSection(std::move(arg));
                BOOST_TEST_REQUIRE(s != nullptr);
                delete s;
            }

        BOOST_AUTO_TEST_SUITE_END() // ObjectCreation


        BOOST_AUTO_TEST_SUITE(ParameterAssignment)

            BOOST_AUTO_TEST_CASE(ExplicitCtor) {
                auto * s = new IniSection(nullptr);
                auto * s1 = new IniSection(s);
                BOOST_TEST_REQUIRE(s->getParent() == nullptr);
                BOOST_TEST_REQUIRE(s1->getParent() == s);
                delete s1;
                delete s;
            }

            BOOST_AUTO_TEST_CASE(MoveCtor) {
                IniSection arg(nullptr);
                auto * s = new IniSection(&arg);
                auto * s1 = new IniSection(std::move(*s));
                BOOST_TEST_REQUIRE(s1->getParent() == &arg);
                delete s1;
                delete s;
            }

        BOOST_AUTO_TEST_SUITE_END() // ParameterAssignment

    BOOST_AUTO_TEST_SUITE_END() // Ctors


    BOOST_AUTO_TEST_SUITE(SubsectionCreation)

        BOOST_AUTO_TEST_CASE(MakeSection) {
            IniSection super(nullptr);
            IniSection * sub = super.makeSection("Subsection", &super).get();
            BOOST_TEST(super.getSection("Subsection") == sub);
            BOOST_TEST(sub->getParent() == &super);
            BOOST_TEST(sub->isLeaf());
            BOOST_TEST(super.isRoot());
        }

        BOOST_AUTO_TEST_CASE(PutSection) {
            IniSection super(nullptr);
            IniSection sub(&super);
            sub.makeSection("Dummy", &sub);
            IniSection * putSub = super.putSection("Subsection", sub).get();
            BOOST_TEST(sub.isLeaf());
            BOOST_TEST(super.isRoot());
            BOOST_TEST(!putSub->isLeaf());
            BOOST_TEST_REQUIRE(putSub->getSection("Dummy") != nullptr);
            BOOST_TEST(putSub->getSection("Dummy")->isLeaf());
            BOOST_TEST(putSub->getParent() == &super);
            BOOST_TEST(super.getSection("Subsection") == putSub);
        }

    BOOST_AUTO_TEST_SUITE_END() // SubsectionCreation

BOOST_AUTO_TEST_SUITE_END() // General



BOOST_AUTO_TEST_SUITE(StringEntrySection)

    BOOST_AUTO_TEST_SUITE(Getter)

        BOOST_AUTO_TEST_CASE(Get) {
            IniSection super(nullptr);
            super.put("Key", "Value");
            BOOST_TEST(super.get("Key") == "Value");
        }

        BOOST_AUTO_TEST_CASE(GetNotPresent) {
            IniSection super(nullptr);
            BOOST_TEST(super.get("Key") == "");
        }

    BOOST_AUTO_TEST_SUITE_END() // Getter

    BOOST_AUTO_TEST_SUITE(Put)

        BOOST_AUTO_TEST_CASE(Put) {
            IniSection super(nullptr);
            super.put("Key", "Value");
            BOOST_TEST(super.get("Key") == "Value");
        }

        BOOST_AUTO_TEST_CASE(PutOverwrite) {
            IniSection super(nullptr);
            super.put("Key", "Value");
            super.put("Key", "Value2");
            BOOST_TEST(super.get("Key") == "Value2");
        }

    BOOST_AUTO_TEST_SUITE_END() // Put

    BOOST_AUTO_TEST_SUITE(PutIfNotPresent)

        BOOST_AUTO_TEST_CASE(PutIfNotPresent) {
            IniSection super(nullptr);
            super.put("Key", "Value");
            super.putIfNotPresent("Key", "Value2");
            BOOST_TEST(super.get("Key") == "Value");
        }

    BOOST_AUTO_TEST_SUITE_END() // PutIfNotPresent


BOOST_AUTO_TEST_SUITE_END() // StringEntrySection