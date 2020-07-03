//
// Created by rostam on 03.07.20.
//


#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN - dont need to repeat this define in more than one cpp file
#include <boost/test/unit_test.hpp>
#include "../G6Format/G6Format.h"
#include "../generators/Cycle.h"
#include "../ConjectureCheck/ConjectureCheck.h"
#include "../ConjectureCheck/ConjectureCheck.h"
#include "../reports/Diameter.h"


BOOST_AUTO_TEST_SUITE(ConjectureCheckTest)
    BOOST_AUTO_TEST_CASE(AllConjectureTest) {
        ConjectureCheck cc;
        cc.CheckSaveToFile(All, std::make_unique<GraphDiameter>(),
                "/home/rostam/all6.g6", "/home/rostam/all6_diameter.csv");
    }
BOOST_AUTO_TEST_SUITE_END()