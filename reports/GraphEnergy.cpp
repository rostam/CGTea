//
// Created by rostam on 27.03.26.
//

#include "GraphEnergy.h"
#include "EigenRelatedFunctions.h"

string GraphEnergy::report(const Graph& g) {
    int n = boost::num_vertices(g);
    if (n == 0) return "0.000000";
    Eigen::MatrixXd m = Eigen::MatrixXd::Zero(n, n);
    for_each_e_const(g, [&](Edge e) {
        m(boost::source(e, g), boost::target(e, g)) = 1;
        m(boost::target(e, g), boost::source(e, g)) = 1;
    });
    Eigen::EigenSolver<Eigen::MatrixXd> eigensolver;
    eigensolver.compute(m);
    if (eigensolver.info() != Eigen::Success) return "0.000000";
    double energy = eigensolver.eigenvalues().real().cwiseAbs().sum();
    return std::to_string(energy);
}
