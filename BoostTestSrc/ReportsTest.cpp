//
// Created by rostam on 11.06.20.
//

#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN - don't need to repeat this define in more than one cpp file
#include <boost/test/unit_test.hpp>

#include "../reports/Diameter.h"
#include "../reports/GirthSize.h"
#include "../reports/NumOfVertices.h"
#include "../reports/NumOfEdges.h"
#include "../reports/MaxDegree.h"
#include "../reports/MinDegree.h"
#include "../reports/NumOfTriangles.h"
#include "../generators/Cycle.h"
#include "../generators/GeneralizedPeterson.h"
#include "../generators/Complete.h"
#include "../generators/Path.h"
#include "../generators/Star.h"
#include "../generators/Wheel.h"

BOOST_AUTO_TEST_SUITE(ReportsTestSuite)
    BOOST_AUTO_TEST_CASE(DiameterTest) {
        Graph cycle10 = Cycle().generate(10,1);
        Graph peterson = GeneralizedPeterson().generate(5,2);
        Graph complete5 = Complete().generate(5,1);
        GraphDiameter gd;
        auto res = Utils::return_value(gd.report(cycle10), gd.type());
        BOOST_CHECK_EQUAL(std::get<int>(res), 5);
        res = Utils::return_value(gd.report(peterson), gd.type());
        BOOST_CHECK_EQUAL(std::get<int>(res), 2);
        res = Utils::return_value(gd.report(complete5), gd.type());
        BOOST_CHECK_EQUAL(std::get<int>(res), 1);
    }

    BOOST_AUTO_TEST_CASE(GirthTest) {

        Graph peterson = GeneralizedPeterson().generate(5, 2);
        auto res2 = Utils::return_value(GraphGirthSize().report(peterson), "int");
        BOOST_CHECK_EQUAL(std::get<int>(res2), 5);

        Graph cycle10 = Cycle().generate(10, 1);
        auto res = Utils::return_value(GraphGirthSize().report(cycle10), "int");
        BOOST_CHECK_EQUAL(std::get<int>(res), 10);

        Graph complete5 = Complete().generate(5, 1);
        auto res3 = Utils::return_value(GraphGirthSize().report(complete5), "int");
        BOOST_CHECK_EQUAL(std::get<int>(res3), 3);

        // Trees and acyclic graphs have girth 0
        BOOST_CHECK_EQUAL(std::stoi(GraphGirthSize().report(Path().generate(5, 1))), 0);
        BOOST_CHECK_EQUAL(std::stoi(GraphGirthSize().report(Star().generate(5, 0))), 0);
    }

    BOOST_AUTO_TEST_CASE(BasicMetricsTest) {
        Graph k5 = Complete().generate(5, 1);
        BOOST_CHECK_EQUAL(std::stoi(NumOfVertices().report(k5)), 5);
        BOOST_CHECK_EQUAL(std::stoi(NumOfEdges().report(k5)), 10);
        BOOST_CHECK_EQUAL(std::stoi(MaxDegree().report(k5)), 4);
        BOOST_CHECK_EQUAL(std::stoi(MinDegree().report(k5)), 4);

        Graph path5 = Path().generate(5, 1);
        BOOST_CHECK_EQUAL(std::stoi(NumOfVertices().report(path5)), 5);
        BOOST_CHECK_EQUAL(std::stoi(NumOfEdges().report(path5)), 4);
        BOOST_CHECK_EQUAL(std::stoi(MaxDegree().report(path5)), 2);
        BOOST_CHECK_EQUAL(std::stoi(MinDegree().report(path5)), 1);

        Graph star6 = Star().generate(6, 0);
        BOOST_CHECK_EQUAL(std::stoi(NumOfVertices().report(star6)), 6);
        BOOST_CHECK_EQUAL(std::stoi(NumOfEdges().report(star6)), 5);
        BOOST_CHECK_EQUAL(std::stoi(MaxDegree().report(star6)), 5);
        BOOST_CHECK_EQUAL(std::stoi(MinDegree().report(star6)), 1);
    }

    BOOST_AUTO_TEST_CASE(NumOfTrianglesTest) {
        // K_n has C(n,3) triangles
        BOOST_CHECK_EQUAL(std::stoi(NumberOfTriangles().report(Complete().generate(4, 1))), 4);
        BOOST_CHECK_EQUAL(std::stoi(NumberOfTriangles().report(Complete().generate(5, 1))), 10);

        // Cycle and path have no triangles
        BOOST_CHECK_EQUAL(std::stoi(NumberOfTriangles().report(Cycle().generate(6, 1))), 0);
        BOOST_CHECK_EQUAL(std::stoi(NumberOfTriangles().report(Path().generate(5, 1))), 0);

        // Star has no triangles (tree)
        BOOST_CHECK_EQUAL(std::stoi(NumberOfTriangles().report(Star().generate(5, 0))), 0);

        // Wheel(n): each spoke pair with rim edge forms a triangle → n-1 triangles
        BOOST_CHECK_EQUAL(std::stoi(NumberOfTriangles().report(Wheel().generate(6, 0))), 5);
    }

BOOST_AUTO_TEST_SUITE_END()