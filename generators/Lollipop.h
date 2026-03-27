// Created by rostam on 27.03.26.
#ifndef CGTEA_LOLLIPOP_H
#define CGTEA_LOLLIPOP_H
#include "GeneratorInterface.h"

// Lollipop graph L(n,k): complete graph K_n with path P_k attached at vertex 0
class Lollipop : public GeneratorInterface {
public:
    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        // K_n
        for (unsigned int i = 0; i < n; i++)
            for (unsigned int j = i + 1; j < n; j++)
                add_edge(i, j, g);
        // P_k attached at vertex 0
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

    string name()        const override { return "Lollipop Graph"; }
    string description() const override { return "K_n with path P_k attached"; }
    bool hasSecondParam()         const override { return true; }
    string paramNName()           const override { return "n (clique size)"; }
    string paramKName()           const override { return "k (tail length)"; }
    unsigned int defaultN()       const override { return 5; }
    unsigned int defaultK()       const override { return 4; }
};
#endif
