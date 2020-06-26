//
// Created by rostam on 11.06.20.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN - dont need to repeat this define in more than one cpp file
#include <boost/test/unit_test.hpp>

#include "../generators/Cycle.h"
#include "../generators/Complete.h"
#include "../generators/GeneralizedPeterson.h"
#include "../generators/Prism.h"
#include "../generators/Antiprism.h"
#include "../generators/Cmn.h"
#include "../generators/Path.h"
#include "../generators/Flower.h"

#include "../reports/MaxDegree.h"
#include "../reports/MinDegree.h"
#include "../reports/Diameter.h"
#include "../reports/GirthSize.h"


BOOST_AUTO_TEST_SUITE(GeneratorsTestSuite)
    BOOST_AUTO_TEST_CASE(CircleGeneratorTest) {
        Cycle c;
        Graph g = c.generate(10,1);
        BOOST_CHECK_EQUAL(boost::num_vertices(g),10);
        BOOST_CHECK_EQUAL(boost::num_edges(g),10);
        BOOST_CHECK_EQUAL(std::stoi(MaxDegree().report(g)), 2);
        BOOST_CHECK_EQUAL(std::stoi(MinDegree().report(g)), 2);
        BOOST_CHECK_EQUAL(std::stoi(GraphDiameter().report(g)), 5);
        BOOST_CHECK_EQUAL(std::stoi(GraphGirthSize().report(g)), 10);
    }
    BOOST_AUTO_TEST_CASE(CompleteGraphGeneratorTest) {
        Complete c;
        Graph g = c.generate(10,1);
        BOOST_CHECK_EQUAL(boost::num_vertices(g),10);
        BOOST_CHECK_EQUAL(boost::num_edges(g),45);
        BOOST_CHECK_EQUAL(std::stoi(MaxDegree().report(g)), 9);
        BOOST_CHECK_EQUAL(std::stoi(MinDegree().report(g)), 9);
        BOOST_CHECK_EQUAL(std::stoi(GraphDiameter().report(g)), 1);
        BOOST_CHECK_EQUAL(std::stoi(GraphGirthSize().report(g)), 3);
    }
    BOOST_AUTO_TEST_CASE(PrismGraphTest) {
        Prism c;
        Graph g = c.generate(10,1);
        BOOST_CHECK_EQUAL(boost::num_vertices(g),20);
        BOOST_CHECK_EQUAL(boost::num_edges(g),30);
        BOOST_CHECK_EQUAL(std::stoi(MaxDegree().report(g)), 3);
        BOOST_CHECK_EQUAL(std::stoi(MinDegree().report(g)), 3);
        BOOST_CHECK_EQUAL(std::stoi(GraphDiameter().report(g)), 6);
        BOOST_CHECK_EQUAL(std::stoi(GraphGirthSize().report(g)), 4);
    }
    BOOST_AUTO_TEST_CASE(AntiPrismGraphTest) {
        Antiprism c;
        Graph g = c.generate(10,1);
        BOOST_CHECK_EQUAL(boost::num_vertices(g),20);
        BOOST_CHECK_EQUAL(boost::num_edges(g),40);
        BOOST_CHECK_EQUAL(std::stoi(MaxDegree().report(g)), 4);
        BOOST_CHECK_EQUAL(std::stoi(MinDegree().report(g)), 4);
        BOOST_CHECK_EQUAL(std::stoi(GraphDiameter().report(g)), 5);
        BOOST_CHECK_EQUAL(std::stoi(GraphGirthSize().report(g)), 3);
    }
    BOOST_AUTO_TEST_CASE(PetersonGeneratorTest) {
        GeneralizedPeterson gp;
        Graph g = gp.generate(5,2);
        BOOST_CHECK_EQUAL(boost::num_vertices(g),10);
        BOOST_CHECK_EQUAL(boost::num_edges(g),15);
        BOOST_CHECK_EQUAL(std::stoi(MaxDegree().report(g)), 3);
        BOOST_CHECK_EQUAL(std::stoi(MinDegree().report(g)), 3);
        BOOST_CHECK_EQUAL(std::stoi(GraphDiameter().report(g)), 2);
        BOOST_CHECK_EQUAL(std::stoi(GraphGirthSize().report(g)), 5);
    }
    BOOST_AUTO_TEST_CASE(CmnGeneratorTest) {
        Cmn cmn;
        Graph g = cmn.generate(5,4);
        BOOST_CHECK_EQUAL(boost::num_vertices(g),20);
        BOOST_CHECK_EQUAL(boost::num_edges(g),40);
        BOOST_CHECK_EQUAL(std::stoi(MaxDegree().report(g)), 4);
        BOOST_CHECK_EQUAL(std::stoi(MinDegree().report(g)), 4);
        BOOST_CHECK_EQUAL(std::stoi(GraphDiameter().report(g)), 4);
        BOOST_CHECK_EQUAL(std::stoi(GraphGirthSize().report(g)), 4);
    }
    BOOST_AUTO_TEST_CASE(PathGeneratorTest) {
        Path path;
        Graph g = path.generate(5,1);
        BOOST_CHECK_EQUAL(boost::num_vertices(g),5);
        BOOST_CHECK_EQUAL(boost::num_edges(g),4);
        BOOST_CHECK_EQUAL(std::stoi(MaxDegree().report(g)), 2);
        BOOST_CHECK_EQUAL(std::stoi(MinDegree().report(g)), 1);
        BOOST_CHECK_EQUAL(std::stoi(GraphDiameter().report(g)), 4);
        BOOST_CHECK_EQUAL(std::stoi(GraphGirthSize().report(g)), 4);
    }
    BOOST_AUTO_TEST_CASE(FlowerGeneratorTest) {
        int n = 3;
        Flower flower;
        Graph g = flower.generate(n,1);
        BOOST_CHECK_EQUAL(boost::num_vertices(g),2*n+1);
        BOOST_CHECK_EQUAL(boost::num_edges(g),4*n);
        BOOST_CHECK_EQUAL(std::stoi(MaxDegree().report(g)), 2*n);
        BOOST_CHECK_EQUAL(std::stoi(MinDegree().report(g)), 2);
        BOOST_CHECK_EQUAL(std::stoi(GraphDiameter().report(g)), 2);
        BOOST_CHECK_EQUAL(std::stoi(GraphGirthSize().report(g)), 3);
    }
BOOST_AUTO_TEST_SUITE_END()