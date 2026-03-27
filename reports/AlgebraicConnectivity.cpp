//
// Created by rostam on 27.03.26.
//

#include "AlgebraicConnectivity.h"
#include "EigenRelatedFunctions.h"
#include <algorithm>

string AlgebraicConnectivity::report(const Graph& g) {
    int n = boost::num_vertices(g);
    if (n <= 1) return "0.000000";

    // Build Laplacian: L = D - A
    std::vector<double> deg_list;
    deg_list.reserve(n);
    for_each_v_const(g, [&](Ver v) {
        deg_list.emplace_back((double)boost::out_degree(v, g));
    });

    Eigen::MatrixXd m = Eigen::MatrixXd::Zero(n, n);
    for_each_e_const(g, [&](Edge e) {
        m(boost::source(e, g), boost::target(e, g)) = 1;
        m(boost::target(e, g), boost::source(e, g)) = 1;
    });

    Eigen::Map<Eigen::VectorXd> deg_vec(deg_list.data(), n);
    Eigen::MatrixXd L = Eigen::MatrixXd(deg_vec.asDiagonal()) - m;

    Eigen::EigenSolver<Eigen::MatrixXd> eigensolver;
    eigensolver.compute(L);
    if (eigensolver.info() != Eigen::Success) return "0.000000";

    Eigen::VectorXd ev = eigensolver.eigenvalues().real();
    std::sort(ev.data(), ev.data() + ev.size());

    return std::to_string(ev(1));
}
