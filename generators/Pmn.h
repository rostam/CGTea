// Created by rostami on 10.06.20.
#ifndef CGTEA_PMN_H
#define CGTEA_PMN_H
#include "GeneratorInterface.h"

// Grid graph P_n x P_k  (n rows, k columns)
class Pmn : public GeneratorInterface {
public:
    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (unsigned int i = 0; i < n; i++)
            for (unsigned int j = 0; j < k; j++) {
                if (j + 1 < k) add_edge(i * k + j, i * k + j + 1, g);
                if (i + 1 < n) add_edge(i * k + j, (i + 1) * k + j, g);
            }
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        double dx = (k > 1) ? width  / (k + 1) : width  / 2;
        double dy = (n > 1) ? height / (n + 1) : height / 2;
        for (unsigned int i = 0; i < n; i++)
            for (unsigned int j = 0; j < k; j++)
                boost::put(boost::vertex_distance, g, i * k + j,
                           cgtea_geometry::Point(dx * (j + 1), dy * (i + 1)));
        return g;
    }

    string name()        const override { return "Grid Graph P(n)*P(k)"; }
    string description() const override { return "n x k grid graph"; }
    bool hasSecondParam()         const override { return true; }
    string paramNName()           const override { return "n (rows)"; }
    string paramKName()           const override { return "k (columns)"; }
    unsigned int defaultN()       const override { return 4; }
    unsigned int defaultK()       const override { return 5; }
};
#endif
