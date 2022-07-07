#define BOOST_AUTO_TEST_MAIN //root of all tests
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

struct MyConfig {

    MyConfig() {
              tolerance(0.0001);
    }

    ~MyConfig() {

    }
};
//
BOOST_GLOBAL_FIXTURE(MyConfig);