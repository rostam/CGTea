//
// Created by rostam on 03.07.20.
//


#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN - dont need to repeat this define in more than one cpp file
#include <boost/test/unit_test.hpp>
#include "../G6Format/G6Format.h"
#include "../generators/Cycle.h"
#include "../generators/Complete.h"
#include "../generators/Path.h"


BOOST_AUTO_TEST_SUITE(IOTest)
    BOOST_AUTO_TEST_CASE(G6FormatEncodeTest) {
        G6Format g6format;
        // Cycle(3) is a triangle: 3 lower-triangle bits "111" -> padded to "111000" -> 'w'; n=3 -> 'B'
        BOOST_CHECK_EQUAL(g6format.graphToG6(Cycle().generate(3, 1)), "Bw");
        // Path(2) has 1 edge: 1 bit "1" -> padded to "100000" -> '_'; n=2 -> 'A'
        BOOST_CHECK_EQUAL(g6format.graphToG6(Path().generate(2, 1)), "A_");
    }

    BOOST_AUTO_TEST_CASE(G6GraphsizeTest) {
        G6Format g6format;
        // graphsize should recover n from an encoded graph
        for (int n = 3; n <= 10; n++) {
            std::string encoded = g6format.graphToG6(Cycle().generate(n, 1));
            BOOST_CHECK_EQUAL(g6format.graphsize(encoded), n);
        }
    }

    BOOST_AUTO_TEST_CASE(G6RoundTripTest) {
        G6Format g6format;
        // graph -> G6 string -> graph must preserve vertex and edge counts
        auto round_trip_ok = [&](const Graph& original) {
            std::string encoded = g6format.graphToG6(original);
            Graph decoded = g6format.stringToGraph(encoded);
            return boost::num_vertices(decoded) == boost::num_vertices(original)
                && boost::num_edges(decoded) == boost::num_edges(original);
        };

        BOOST_CHECK(round_trip_ok(Cycle().generate(5, 1)));
        BOOST_CHECK(round_trip_ok(Cycle().generate(10, 1)));
        BOOST_CHECK(round_trip_ok(Complete().generate(4, 1)));
        BOOST_CHECK(round_trip_ok(Complete().generate(6, 1)));
        BOOST_CHECK(round_trip_ok(Path().generate(7, 1)));
    }

BOOST_AUTO_TEST_SUITE_END()