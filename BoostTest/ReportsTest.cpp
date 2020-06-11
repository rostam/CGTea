//
// Created by rostam on 11.06.20.
//

#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN - don't need to repeat this define in more than one cpp file
#include <boost/test/unit_test.hpp>

#include "../reports/Diameter.h"
#include "../generators/Cycle.h"
#include "../generators/GeneralizedPeterson.h"
#include "../generators/Complete.h"

BOOST_AUTO_TEST_SUITE(ReportsTestSuite)
    BOOST_AUTO_TEST_CASE(DiameterTest) {
        Graph cycle10 = Cycle().generate(10,1);
        Graph peterson = GeneralizedPeterson().generate(5,2);
        Graph complete5 = Complete().generate(5,1);
        GraphDiameter gd;
        auto res = Utils::return_value(gd.report(cycle10), gd.type());
        BOOST_CHECK_EQUAL(std::get<int>(res), 5);
        res = Utils::return_value(gd.report(peterson), gd.type());
        BOOST_CHECK_EQUAL(std::get<int>(res), 2);
        res = Utils::return_value(gd.report(complete5), gd.type());
        BOOST_CHECK_EQUAL(std::get<int>(res), 1);
    }
BOOST_AUTO_TEST_SUITE_END()