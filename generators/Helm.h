// Created by rostami on 10.06.20.
#ifndef CGTEA_HELM_H
#define CGTEA_HELM_H
#include "GeneratorInterface.h"

// Helm H_n: wheel W_n with a pendant vertex attached to each outer vertex.
// Vertices: 0 = hub, 1..n = cycle, n+1..2n = pendants
class Helm : public GeneratorInterface {
public:
    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        if (n < 3) n = 3;
        for (unsigned int i = 1; i <= n; i++) {
            add_edge(0, i, g);               // hub to cycle vertex
            add_edge(i, i % n + 1, g);       // cycle edge (wraps: n -> 1)
            add_edge(i, n + i, g);            // pendant edge
        }
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        if (n < 3) n = 3;
        Graph g = generate(n, k);
        // hub at center
        boost::put(boost::vertex_distance, g, 0, cgtea_geometry::Point(width, height));
        // cycle vertices on inner circle
        auto inner = position_generators::circle(width, height, 120.0, n);
        for (unsigned int i = 0; i < n; i++)
            boost::put(boost::vertex_distance, g, i + 1, inner[i]);
        // pendants on outer circle
        auto outer = position_generators::circle(width, height, 200.0, n);
        for (unsigned int i = 0; i < n; i++)
            boost::put(boost::vertex_distance, g, n + i + 1, outer[i]);
        return g;
    }

    string name()        const override { return "Helm Graph"; }
    string description() const override { return "Wheel with pendant vertices"; }
    string paramNName()  const override { return "n (spokes)"; }
    unsigned int defaultN() const override { return 6; }
};
#endif
