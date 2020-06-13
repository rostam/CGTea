//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_MINDEGREE_H
#define CGTEA_MINDEGREE_H

#include "ReportInterface.h"

class MinDegree : public ReportInterface{
public:
    string report(const Graph& g) override {
        int min_degree = boost::num_vertices(g) + 1;
        for_each_v_const(g, [&](Ver v){
           int deg = boost::out_degree(v, g);
           if(deg < min_degree) min_degree = deg;
        });
        return std::to_string(min_degree);
    };
    string name() const override {
        return "Minimum degree";
    };
    string description() const override {
        return "Minimum degree";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_MAXDEGREE_H
