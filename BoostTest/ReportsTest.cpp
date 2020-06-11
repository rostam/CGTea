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
        GraphDiameter gd;
        Cycle c;
        Graph g = c.generate(10,1);
        gd.report(g);
        BOOST_CHECK_EQUAL(boost::num_vertices(g),10);
    }
BOOST_AUTO_TEST_SUITE_END()