//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_MAXEIGENVALUE_H
#define CGTEA_MAXEIGENVALUE_H

#include "ReportInterface.h"

class MaxEigenValue : public ReportInterface{
public:
    string report(const Graph& g) override {
        std::tuple<double,double,double> t = eigen_values(g);
        return std::to_string(std::get<0>(t));
    };
    string name() override {
        return "Maximum eigen value";
    };
    string description() override {
        return "Maximum eigen value";
    };

    static std::tuple<double,double,double> eigen_values(const Graph& g) {
        int n = boost::num_vertices(g);
        Eigen::MatrixXd m (n, n);
        for_each_e_const(g, [&](Edge e){
            m(boost::source(e,g), boost::target(e,g)) = 1;
            m(boost::target(e,g), boost::source(e,g)) = 1;
        });
        if(m.rows()<=0 || m.cols()<=0)  return std::make_tuple(0,0,0);

        Eigen::EigenSolver<Eigen::MatrixXd> eigensolver;
        eigensolver.compute(m);
        Eigen::VectorXd eigen_values = eigensolver.eigenvalues().real();
        Eigen::MatrixXd eigen_vectors = eigensolver.eigenvectors().real();
        double max_eigen = eigensolver.eigenvalues().real().maxCoeff();
        double min_eigen = eigensolver.eigenvalues().real().minCoeff();
        double sum_eigen = eigensolver.eigenvalues().real().sum();
        return std::make_tuple(max_eigen,min_eigen,sum_eigen);
    }
};

#endif //CGTEA_MAXEIGENVALUE_H
