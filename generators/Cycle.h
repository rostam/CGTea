/**
 * Created by rostami on 28.06.17.
 */
#ifndef EXACT_COLORING_CYCLE_H
#define EXACT_COLORING_CYCLE_H

#include "GeneratorInterface.h"

class Cycle : public GeneratorInterface {
public:
    explicit Cycle() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (unsigned int i = 0; i < n; i++)
            add_edge(i, ((i + 1) % n), 1, g);
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        for_each_v(g, [&](Ver v) {boost::put(boost::vertex_distance, g, v, pos[v]);});
        return g;
    }

    string name() const override {
        return "Cycle";
    }

    string description() const override {
        return "Generates a cycle graph.";
    }

    string category() const override {
        return "General";
    }
};


#endif
