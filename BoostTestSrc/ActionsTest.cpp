//
// Created by rostam on 05.07.20.
//

#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN - dont need to repeat this define in more than one cpp file
#include <boost/test/unit_test.hpp>
#include "../actions/LineGraph.h"
#include "../generators/GeneralizedPeterson.h"

BOOST_AUTO_TEST_SUITE(ConjectureCheckTest)
    BOOST_AUTO_TEST_CASE(LineGraphTest) {
        GeneralizedPeterson gp;
        Graph peterson = gp.generate(5,2);
        LineGraph llg;
        Graph L = llg.action(peterson);
        BOOST_CHECK_EQUAL(boost::num_vertices(L), boost::num_edges(peterson));
        BOOST_CHECK_EQUAL(boost::num_edges(peterson), 30);
        bool isCorrect = false;
        for_each_v(L, [&](Ver v){
            int d_e_L = boost::degree(v,L);
            Edge e = llg.VertexToEdgeMapper[v];
            int d_v_g = boost::degree(boost::source(e,peterson),peterson);
            int d_u_g = boost::degree(boost::target(e,peterson),peterson);
//            cerr << d_e_L << " " << d_v_g << " " << d_u_g << endl;
            isCorrect = (d_e_L == (d_v_g + d_u_g - 2));
            if(!isCorrect)
                return;
        });
        for_each_e(L, [&](Edge e){
           std::cerr << e << endl;
        });
        BOOST_CHECK_EQUAL(isCorrect, true);
    }
BOOST_AUTO_TEST_SUITE_END()