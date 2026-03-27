// Created by rostami on 10.06.20.
#ifndef CGTEA_KMN_H
#define CGTEA_KMN_H
#include "GeneratorInterface.h"

// Complete bipartite graph K_{n,k}
// Part A: vertices 0..n-1   Part B: vertices n..n+k-1
class Kmn : public GeneratorInterface {
public:
    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (unsigned int i = 0; i < n; i++)
            for (unsigned int j = 0; j < k; j++)
                add_edge(i, n + j, g);
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        double dx1 = (n > 0) ? width / (n + 1) : width;
        double dx2 = (k > 0) ? width / (k + 1) : width;
        for (unsigned int i = 0; i < n; i++)
            boost::put(boost::vertex_distance, g, i,     cgtea_geometry::Point(dx1 * (i + 1), height / 3));
        for (unsigned int j = 0; j < k; j++)
            boost::put(boost::vertex_distance, g, n + j, cgtea_geometry::Point(dx2 * (j + 1), 2 * height / 3));
        return g;
    }

    string name()        const override { return "Complete Bipartite K(n,k)"; }
    string description() const override { return "Complete bipartite graph K_{n,k}"; }
    bool hasSecondParam()         const override { return true; }
    string paramNName()           const override { return "n (first part)"; }
    string paramKName()           const override { return "k (second part)"; }
    unsigned int defaultN()       const override { return 3; }
    unsigned int defaultK()       const override { return 4; }
};
#endif
