//
// Created by rostam on 05.07.20.
//

#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN - dont need to repeat this define in more than one cpp file
#include <boost/test/unit_test.hpp>
#include "../actions/LineGraph.h"
#include "../generators/GeneralizedPeterson.h"
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

    }
BOOST_AUTO_TEST_SUITE_END()