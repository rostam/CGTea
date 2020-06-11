//
// Created by rostam on 11.06.20.
//

#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN - don't need to repeat this define in more than one cpp file
#include <boost/test/unit_test.hpp>

#include "../reports/Diameter.h"
#include "../generators/Cycle.h"

BOOST_AUTO_TEST_SUITE(ReportsTestSuite)
    BOOST_AUTO_TEST_CASE(DiameterTest) {
        Graph cycle10 = Cycle().generate(10,1);
        GraphDiameter gd;
        auto res = Utils::return_value(gd.report(cycle10), gd.type());
        BOOST_CHECK_EQUAL(std::get<int>(res), 5);
//        BOOST_CHECK_EQUAL(GraphDiameter().report(cycle10),boost::num_vertices(cycle10)/2);
//        Assertions.assertEquals(varDiameter.calculate(peterson),2);
//        Assertions.assertEquals(varDiameter.calculate(circle4),2);
//        Assertions.assertEquals(varDiameter.calculate(circle5),2);
//        Assertions.assertEquals(varDiameter.calculate(complete4), 1);
//        Assertions.assertEquals(varDiameter.calculate(complete5), 1);
    }
BOOST_AUTO_TEST_SUITE_END()