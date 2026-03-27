//
// Created by rostam on 05.07.20.
//

#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN - dont need to repeat this define in more than one cpp file
#include <boost/test/unit_test.hpp>
#include "../actions/LineGraph.h"
#include "../actions/Coloring.h"
#include "../generators/GeneralizedPeterson.h"
#include "../generators/Complete.h"
#include "../generators/Cycle.h"
#include "../generators/Path.h"
#include "../generators/Star.h"

BOOST_AUTO_TEST_SUITE(ActionsTest)
    BOOST_AUTO_TEST_CASE(LineGraphTest) {
        GeneralizedPeterson gp;
        Graph peterson = gp.generate(5,2);
        LineGraph llg;
        Graph L = llg.action(peterson);
        BOOST_CHECK_EQUAL(boost::num_vertices(L), boost::num_edges(peterson));
        bool isCorrect = false;
        for_each_v(L, [&](Ver v){
            int d_e_L = boost::degree(v,L);
            Edge e = llg.VertexToEdgeMapper[v];
            int d_v_g = boost::degree(boost::source(e,peterson),peterson);
            int d_u_g = boost::degree(boost::target(e,peterson),peterson);
            isCorrect = (d_e_L == (d_v_g + d_u_g - 2));
            if(!isCorrect)
                return;
        });
        BOOST_CHECK_EQUAL(isCorrect, true);

        Graph path = Path().generate(4,0);
        Graph Lpath = llg.action(path);
        BOOST_CHECK_EQUAL(boost::num_vertices(Lpath), boost::num_edges(path));
        BOOST_CHECK_EQUAL(boost::num_edges(Lpath), boost::num_edges(path) - 1);

        Graph star = Star().generate(4, 0);
        Graph Lstar = llg.action(star);
        BOOST_CHECK_EQUAL(boost::num_vertices(Lstar), 3);
        BOOST_CHECK_EQUAL(boost::num_edges(Lstar), 3);

        // L(K4) has 6 vertices (one per edge) and 12 edges
        Graph k4 = Complete().generate(4, 1);
        Graph Lk4 = llg.action(k4);
        BOOST_CHECK_EQUAL(boost::num_vertices(Lk4), boost::num_edges(k4));
        BOOST_CHECK_EQUAL(boost::num_edges(Lk4), 12);
    }

    BOOST_AUTO_TEST_CASE(ColoringProperTest) {
        // A proper coloring assigns different colors to every pair of adjacent vertices
        auto is_proper_coloring = [](const Graph& g) {
            bool proper = true;
            for_each_e_const(g, [&](Edge e) {
                Ver u = boost::source(e, g);
                Ver v = boost::target(e, g);
                if (boost::get(vertex_color, g, u) == boost::get(vertex_color, g, v))
                    proper = false;
            });
            return proper;
        };

        Coloring coloring;

        Graph peterson = GeneralizedPeterson().generate(5, 2);
        BOOST_CHECK(is_proper_coloring(coloring.action(peterson)));

        Graph cycle8 = Cycle().generate(8, 1);
        BOOST_CHECK(is_proper_coloring(coloring.action(cycle8)));

        Graph k5 = Complete().generate(5, 1);
        BOOST_CHECK(is_proper_coloring(coloring.action(k5)));
    }

    BOOST_AUTO_TEST_CASE(ColoringChromaticTest) {
        auto max_color_used = [](const Graph& g) {
            int max_color = 0;
            for_each_v_const(g, [&](Ver v) {
                max_color = std::max(max_color, (int)boost::get(vertex_color, g, v));
            });
            return max_color + 1;
        };

        Coloring coloring;

        // K_n requires exactly n colors
        BOOST_CHECK_EQUAL(max_color_used(coloring.action(Complete().generate(4, 1))), 4);

        // Even cycle is bipartite, needs exactly 2 colors
        BOOST_CHECK_EQUAL(max_color_used(coloring.action(Cycle().generate(6, 1))), 2);

        // Path is bipartite, needs exactly 2 colors (for n >= 2)
        BOOST_CHECK_EQUAL(max_color_used(coloring.action(Path().generate(5, 1))), 2);
    }

BOOST_AUTO_TEST_SUITE_END()