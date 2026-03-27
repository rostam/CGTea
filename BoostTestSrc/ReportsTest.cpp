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
#include "../reports/AverageDegree.h"
#include "../reports/Density.h"
#include "../reports/NumConnectedComponents.h"
#include "../reports/Radius.h"
#include "../reports/WienerIndex.h"
#include "../reports/GraphEnergy.h"
#include "../reports/AlgebraicConnectivity.h"
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

    BOOST_AUTO_TEST_CASE(AverageDegreeTest) {
        // K5: every vertex has degree 4 → average = 4.0
        BOOST_CHECK_CLOSE(std::stod(AverageDegree().report(Complete().generate(5, 1))), 4.0, 0.001);
        // Path(5): 2 endpoints (deg 1) + 3 middle (deg 2) → sum = 8, avg = 1.6
        BOOST_CHECK_CLOSE(std::stod(AverageDegree().report(Path().generate(5, 1))), 1.6, 0.001);
        // Cycle(10): every vertex has degree 2 → average = 2.0
        BOOST_CHECK_CLOSE(std::stod(AverageDegree().report(Cycle().generate(10, 1))), 2.0, 0.001);
    }

    BOOST_AUTO_TEST_CASE(DensityTest) {
        // K5: fully connected → density = 1.0
        BOOST_CHECK_CLOSE(std::stod(Density().report(Complete().generate(5, 1))), 1.0, 0.001);
        // Path(5): 4 edges, n=5 → 2*4/(5*4) = 0.4
        BOOST_CHECK_CLOSE(std::stod(Density().report(Path().generate(5, 1))), 0.4, 0.001);
        // Star(6): 5 edges, n=6 → 2*5/(6*5) = 1/3
        BOOST_CHECK_CLOSE(std::stod(Density().report(Star().generate(6, 0))), 1.0/3.0, 0.001);
    }

    BOOST_AUTO_TEST_CASE(ConnectedComponentsTest) {
        BOOST_CHECK_EQUAL(std::stoi(NumConnectedComponents().report(Complete().generate(5, 1))), 1);
        BOOST_CHECK_EQUAL(std::stoi(NumConnectedComponents().report(Path().generate(5, 1))), 1);
        BOOST_CHECK_EQUAL(std::stoi(NumConnectedComponents().report(Cycle().generate(10, 1))), 1);
        BOOST_CHECK_EQUAL(std::stoi(NumConnectedComponents().report(Star().generate(6, 0))), 1);
    }

    BOOST_AUTO_TEST_CASE(RadiusTest) {
        // K5: all eccentricities = 1
        BOOST_CHECK_EQUAL(std::stoi(GraphRadius().report(Complete().generate(5, 1))), 1);
        // Path(5): center vertex (index 2) has eccentricity 2
        BOOST_CHECK_EQUAL(std::stoi(GraphRadius().report(Path().generate(5, 1))), 2);
        // Cycle(10): radius = floor(10/2) = 5
        BOOST_CHECK_EQUAL(std::stoi(GraphRadius().report(Cycle().generate(10, 1))), 5);
        // Star(6): center has eccentricity 1 (adjacent to all leaves)
        BOOST_CHECK_EQUAL(std::stoi(GraphRadius().report(Star().generate(6, 0))), 1);
    }

    BOOST_AUTO_TEST_CASE(WienerIndexTest) {
        // K5: C(5,2)=10 pairs each at distance 1 → W = 10
        BOOST_CHECK_EQUAL(std::stoll(WienerIndex().report(Complete().generate(5, 1))), 10);
        // Path(5): sum of all pairwise distances = 20
        BOOST_CHECK_EQUAL(std::stoll(WienerIndex().report(Path().generate(5, 1))), 20);
        // Cycle(10): 10 pairs at d=1, 10 at d=2, 10 at d=3, 10 at d=4, 5 at d=5 → W = 125
        BOOST_CHECK_EQUAL(std::stoll(WienerIndex().report(Cycle().generate(10, 1))), 125);
        // Star(6): 5 centre-leaf pairs (d=1) + C(5,2)=10 leaf-leaf pairs (d=2) → W = 25
        BOOST_CHECK_EQUAL(std::stoll(WienerIndex().report(Star().generate(6, 0))), 25);
    }

    BOOST_AUTO_TEST_CASE(GraphEnergyTest) {
        // K4: eigenvalues 3 (×1) and -1 (×3) → energy = 3+3 = 6
        BOOST_CHECK_CLOSE(std::stod(GraphEnergy().report(Complete().generate(4, 1))), 6.0, 0.01);
        // K5: eigenvalues 4 (×1) and -1 (×4) → energy = 4+4 = 8
        BOOST_CHECK_CLOSE(std::stod(GraphEnergy().report(Complete().generate(5, 1))), 8.0, 0.01);
        // Empty graph (edgeless) → energy = 0
        BOOST_CHECK_CLOSE(std::stod(GraphEnergy().report(Path().generate(1, 1))), 0.0, 0.01);
    }

    BOOST_AUTO_TEST_CASE(AlgebraicConnectivityTest) {
        // K5: Laplacian eigenvalues are 0 and 5 (×4) → Fiedler = 5.0
        BOOST_CHECK_CLOSE(std::stod(AlgebraicConnectivity().report(Complete().generate(5, 1))), 5.0, 0.01);
        // Cycle(6): second smallest Laplacian eigenvalue = 2-2cos(2π/6) = 2-1 = 1.0
        BOOST_CHECK_CLOSE(std::stod(AlgebraicConnectivity().report(Cycle().generate(6, 1))), 1.0, 0.01);
        // Path is a tree; algebraic connectivity = 2-2cos(π/5) ≈ 0.382
        BOOST_CHECK_CLOSE(std::stod(AlgebraicConnectivity().report(Path().generate(5, 1))), 0.382, 0.5);
    }

BOOST_AUTO_TEST_SUITE_END()