//
// Created by rostam on 15.05.25.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../G6Format.h"

BOOST_AUTO_TEST_SUITE(G6FormatTests)

BOOST_AUTO_TEST_CASE(test_graph_size_detection)
{
    G6Format g6;
    // Test small graph (n ≤ 62)
    BOOST_CHECK_EQUAL(g6.graphsize("A_"), 1);
    BOOST_CHECK_EQUAL(g6.graphsize("B?"), 2);

    // Test larger graph
    BOOST_CHECK_EQUAL(g6.graphsize(":?@"), 63);
}

BOOST_AUTO_TEST_CASE(test_empty_graph_conversion)
{
    G6Format g6;
    Graph g;
    boost::add_vertex(g);
    boost::add_vertex(g);

    std::string g6str = g6.graphToG6(g);
    Graph decoded = g6.stringToGraph(g6str);

    BOOST_CHECK_EQUAL(boost::num_vertices(decoded), 2);
    BOOST_CHECK_EQUAL(boost::num_edges(decoded), 0);
}

BOOST_AUTO_TEST_CASE(test_simple_graph_conversion)
{
    G6Format g6;
    Graph g;
    boost::add_vertex(g);
    boost::add_vertex(g);
    boost::add_vertex(g);
    boost::add_edge(0, 1, g);
    boost::add_edge(1, 2, g);

    std::string g6str = g6.graphToG6(g);
    Graph decoded = g6.stringToGraph(g6str);

    BOOST_CHECK_EQUAL(boost::num_vertices(decoded), 3);
    BOOST_CHECK_EQUAL(boost::num_edges(decoded), 2);

    // Check that specific edges exist
    BOOST_CHECK(boost::edge(0, 1, decoded).second);
    BOOST_CHECK(boost::edge(1, 2, decoded).second);
    BOOST_CHECK(!boost::edge(0, 2, decoded).second);
}

BOOST_AUTO_TEST_SUITE_END()