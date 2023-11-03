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
        Eigen::MatrixXd m(n, n);
        for_each_e_const(g, [&](Edge e) {
            m(boost::source(e, g), boost::target(e, g)) = 1;
            m(boost::target(e, g), boost::source(e, g)) = 1;
        });
        if (m.rows() <= 0 || m.cols() <= 0) return std::make_tuple(0, 0, 0);

        Eigen::EigenSolver<Eigen::MatrixXd> eigensolver;
        eigensolver.compute(m);
        Eigen::VectorXd eigen_values = eigensolver.eigenvalues().real();
        Eigen::MatrixXd eigen_vectors = eigensolver.eigenvectors().real();
        double max_eigen = eigensolver.eigenvalues().real().maxCoeff();
        double min_eigen = eigensolver.eigenvalues().real().minCoeff();
        double sum_eigen = eigensolver.eigenvalues().real().sum();
        return std::make_tuple(max_eigen, min_eigen, sum_eigen);
    }


    static std::tuple<double,double,double> eigen_values_laplacian(const Graph& g) {
        int n = boost::num_vertices(g);
        std::vector<double> deg_list;
        for_each_v_const(g, [&](Ver v) {
            deg_list.emplace_back((double)boost::out_degree(v, g));
        });

        double* ptr = &deg_list[0];
        Eigen::Map<Eigen::VectorXd> my_vect(ptr, 4);
        Eigen::MatrixXd m(n,n);
        for_each_e_const(g, [&](Edge e){
            m(boost::source(e,g), boost::target(e,g)) = 1;
            m(boost::target(e,g), boost::source(e,g)) = 1;
        });

        Eigen::MatrixXd D = my_vect.asDiagonal();
        m = D - m;
        Eigen::EigenSolver<Eigen::MatrixXd> eigensolver;
        eigensolver.compute(m);
        Eigen::VectorXd eigen_values = eigensolver.eigenvalues().real();
        Eigen::MatrixXd eigen_vectors = eigensolver.eigenvectors().real();

        double max_eigen = eigensolver.eigenvalues().real().maxCoeff();
        double min_eigen = eigensolver.eigenvalues().real().minCoeff();
        double sum_eigen = eigensolver.eigenvalues().real().sum();
        return std::make_tuple(max_eigen,min_eigen,sum_eigen);
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
