//
// Created by rostam on 19.06.20.
//

#ifndef CGTEA_EIGENRELATEDFUNCTIONS_H
#define CGTEA_EIGENRELATEDFUNCTIONS_H
#include "../Eigen/Dense"
#include "../Eigen/Eigenvalues"

namespace EigenRelatedFunctions {

    static std::tuple<double, double, double> eigen_values(const Graph &g) {
        int n = boost::num_vertices(g);
        if (n <= 0) return std::make_tuple(0, 0, 0);

        Eigen::MatrixXd m = Eigen::MatrixXd::Zero(n, n);
        for_each_e_const(g, [&](Edge e) {
            m(boost::source(e, g), boost::target(e, g)) = 1;
            m(boost::target(e, g), boost::source(e, g)) = 1;
        });

        Eigen::EigenSolver<Eigen::MatrixXd> eigensolver;
        eigensolver.compute(m);
        if (eigensolver.info() != Eigen::Success) return std::make_tuple(0, 0, 0);

        Eigen::VectorXd ev = eigensolver.eigenvalues().real();
        return std::make_tuple(ev.maxCoeff(), ev.minCoeff(), ev.sum());
    }


    static std::tuple<double,double,double> eigen_values_laplacian(const Graph& g) {
        int n = boost::num_vertices(g);
        if (n <= 0) return std::make_tuple(0, 0, 0);

        std::vector<double> deg_list;
        deg_list.reserve(n);
        for_each_v_const(g, [&](Ver v) {
            deg_list.emplace_back((double)boost::out_degree(v, g));
        });

        Eigen::Map<Eigen::VectorXd> my_vect(deg_list.data(), n);
        Eigen::MatrixXd m = Eigen::MatrixXd::Zero(n, n);
        for_each_e_const(g, [&](Edge e){
            m(boost::source(e,g), boost::target(e,g)) = 1;
            m(boost::target(e,g), boost::source(e,g)) = 1;
        });

        m = Eigen::MatrixXd(my_vect.asDiagonal()) - m;
        Eigen::EigenSolver<Eigen::MatrixXd> eigensolver;
        eigensolver.compute(m);
        if (eigensolver.info() != Eigen::Success) return std::make_tuple(0, 0, 0);

        Eigen::VectorXd ev = eigensolver.eigenvalues().real();
        return std::make_tuple(ev.maxCoeff(), ev.minCoeff(), ev.sum());
    }


    static Eigen::MatrixXd adj_mat(const Graph& g) {
        Eigen::MatrixXd m(boost::num_vertices(g),boost::num_vertices(g));
        for_each_e_const(g, [&](Edge e){
            m(boost::source(e,g), boost::target(e,g)) = 1;
            m(boost::target(e,g), boost::source(e,g)) = 1;
        });

        return m;
    }
};

#endif //CGTEA_EIGENRELATEDFUNCTIONS_H
