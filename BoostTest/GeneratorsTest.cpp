//
// Created by rostam on 11.06.20.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN - don't need to repeat this define in more than one cpp file
#include <boost/test/unit_test.hpp>

#include "../generators/Cycle.h"
#include "../generators/GeneralizedPeterson.h"
#include "../reports/MaxDegree.h"
#include "../reports/MinDegree.h"
#include "../reports/Diameter.h"


BOOST_AUTO_TEST_SUITE(GeneratorsTestSuite)
    BOOST_AUTO_TEST_CASE(CircleGeneratorTest) {
        Cycle c;
        Graph g = c.generate(10,1);
        BOOST_CHECK_EQUAL(boost::num_vertices(g),10);
    }
    BOOST_AUTO_TEST_CASE(PetersonGeneratorTest) {
        GeneralizedPeterson gp;
        Graph g = gp.generate(5,2);
        BOOST_CHECK_EQUAL(boost::num_vertices(g),10);
        BOOST_CHECK_EQUAL(boost::num_edges(g),15);
        BOOST_CHECK_EQUAL(std::stoi(MaxDegree().report(g)), 3);
        BOOST_CHECK_EQUAL(std::stoi(MinDegree().report(g)), 3);
        BOOST_CHECK_EQUAL(std::stoi(GraphDiameter().report(g)), 2);
    }
BOOST_AUTO_TEST_SUITE_END()