// Created by rostami on 10.06.20.
#ifndef CGTEA_TADPOLE_H
#define CGTEA_TADPOLE_H
#include "GeneratorInterface.h"

// Tadpole T(n,k): cycle C_n with path P_k attached at vertex 0
class Tadpole : public GeneratorInterface {
public:
    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        if (n == 0) return g;
        for (unsigned int i = 0; i < n; i++)
            add_edge(i, (i + 1) % n, g);
        if (k > 0) {
            add_edge(0, n, g);
            for (unsigned int i = 1; i < k; i++)
                add_edge(n + i - 1, n + i, g);
        }
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        return generate_with_force_directed(n, k, width, height);
    }

    string name()        const override { return "Tadpole Graph"; }
    string description() const override { return "Cycle C_n with path P_k attached"; }
    bool hasSecondParam()         const override { return true; }
    string paramNName()           const override { return "n (cycle size)"; }
    string paramKName()           const override { return "k (tail length)"; }
    unsigned int defaultN()       const override { return 6; }
    unsigned int defaultK()       const override { return 3; }
};
#endif
