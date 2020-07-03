//
// Created by rostam on 03.07.20.
//


#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN - dont need to repeat this define in more than one cpp file
#include <boost/test/unit_test.hpp>
#include "../G6Format/G6Format.h"
#include "../generators/Cycle.h"
#include "../ConjectureCheck/ConjectureCheck.h"


BOOST_AUTO_TEST_SUITE(IOTest)
    BOOST_AUTO_TEST_CASE(G6FormatTest) {
        Cycle c;
        Graph g = c.generate(3, 1);
        G6Format g6format;
        std::string out = g6format.graphToG6(g);
        BOOST_CHECK_EQUAL(out.c_str(),"Bw");
    }
    BOOST_AUTO_TEST_CASE(TableTest) {
        std::map<std::string, tuple<string,int,double>> result;
        result["test1"] = {"str1",1,0.4};
        result["test2"] = {"str2",3,0.5};
        BOOST_CHECK_EQUAL(result.size(),2);
    }
BOOST_AUTO_TEST_SUITE_END()