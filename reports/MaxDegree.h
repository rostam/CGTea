//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_MAXDEGREE_H
#define CGTEA_MAXDEGREE_H

#include "ReportInterface.h"

class MaxDegree : public ReportInterface{
public:
    string report(const Graph& g) override {
        int max_degree = 0;
        for_each_v_const(g, [&](Ver v){
           int deg = boost::out_degree(v, g);
           if(deg > max_degree) max_degree = deg;
        });
        return std::to_string(max_degree);
    };
    string name() override {
        return "Maximum degree";
    };
    string description() override {
        return "Maximum degree";
    };
};

#endif //CGTEA_MAXDEGREE_H
