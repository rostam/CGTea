 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFTRIANGLES_H
#define CGTEA_NUMOFTRIANGLES_H

#include "ReportInterface.h"

class NumberOfTriangles : public ReportInterface {
public:
    string report(const Graph& g) override {
        int cc = 0;
        for_each_v_const(g, [&](Ver i) {
            for_each_neighbor_const(i, g, [&](Ver j) {
                for_each_neighbor_const(j, g, [&](Ver k) {
                    if (i!=k && edge(k, i, g).second) {
                        cc++;
                    }
                });
            });
        });
        return std::to_string(cc / 6);
    };
    string name() const override {
        return "Number Of Triangles";
    };
    string description() const override {
        return "Number Of Triangles";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_NUMOFTRIANGLES_H
