//
// Created by rostam on 15.05.25.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../reports/AdditiveHarary.h"
#include <boost/graph/adjacency_list.hpp>

BOOST_AUTO_TEST_SUITE(AdditiveHararyTests)

BOOST_AUTO_TEST_CASE(test_empty_graph)
{
    Graph g;
    AdditiveHararyIndex harary;
    BOOST_CHECK_EQUAL(harary.report(g), "0");
}

BOOST_AUTO_TEST_CASE(test_single_edge)
{
    Graph g;
    boost::add_vertex(g);
    boost::add_vertex(g);
    boost::add_edge(0, 1, g);

    AdditiveHararyIndex harary;
    BOOST_CHECK_EQUAL(harary.report(g), "1");
}

BOOST_AUTO_TEST_CASE(test_triangle)
{
    Graph g;
    boost::add_vertex(g);
    boost::add_vertex(g);
    boost::add_vertex(g);
    boost::add_edge(0, 1, g);
    boost::add_edge(1, 2, g);
    boost::add_edge(2, 0, g);

    AdditiveHararyIndex harary;
    BOOST_CHECK_EQUAL(harary.report(g), "3");
}

BOOST_AUTO_TEST_SUITE_END()