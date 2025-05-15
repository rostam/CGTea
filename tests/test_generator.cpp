#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../generators/CocktailParty.h"

BOOST_AUTO_TEST_SUITE(CocktailPartyTests)

BOOST_AUTO_TEST_CASE(test_cocktail_party_basic_properties)
{
    CocktailParty generator;
    // Test with 2 pairs (4 vertices)
    Graph g = generator.generate_with_positions(2, 0, 100, 100);
    
    // Check number of vertices
    BOOST_CHECK_EQUAL(boost::num_vertices(g), 4);
    
    // Check number of edges
    // In a cocktail party graph with n pairs:
    // Each vertex connects to everyone except its pair
    // So each vertex has 2n-2 edges
    // Total edges = n * (2n-2) / 2 = n(n-1)
    BOOST_CHECK_EQUAL(boost::num_edges(g), 4);
    
    // Check that pairs are not connected
    BOOST_CHECK(!boost::edge(0, 2, g).second);
    BOOST_CHECK(!boost::edge(1, 3, g).second);
}

BOOST_AUTO_TEST_CASE(test_cocktail_party_connectivity)
{
    CocktailParty generator;
    Graph g = generator.generate_with_positions(3, 0, 100, 100);
    
    // For 3 pairs (6 vertices), each vertex should have 4 connections
    // (connects to all except its pair)
    for(unsigned int i = 0; i < 3; ++i) {
        int degree_i = boost::out_degree(i, g);
        BOOST_CHECK_EQUAL(degree_i, 4);
        
        int degree_i_pair = boost::out_degree(i + 3, g);
        BOOST_CHECK_EQUAL(degree_i_pair, 4);
    }
}

BOOST_AUTO_TEST_SUITE_END()