// Created by rostam on 10.10.19.
#ifndef CGTEA_NUMOFQUADRANGLE_H
#define CGTEA_NUMOFQUADRANGLE_H
#include "ReportInterface.h"

// Number of 4-cycles (C4) using common-neighbor counting:
// C4 = (1/2) * sum_{i<j} C(common_neighbors(i,j), 2)
class NumberOfQuadrangles : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        long long count = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                int common = 0;
                for (int k = 0; k < n; k++)
                    if (k != i && k != j
                        && boost::edge(i, k, g).second
                        && boost::edge(j, k, g).second)
                        common++;
                count += (long long)common * (common - 1) / 2;
            }
        return std::to_string(count / 2);
    }
    string name()        const override { return "Number of 4-Cycles"; }
    string description() const override { return "Number of cycles of length 4"; }
    string type()        const override { return "int"; }
    string category()    const override { return "General"; }
};
#endif
