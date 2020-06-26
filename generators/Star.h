//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_STAR_H
#define CGTEA_STAR_H

#include "GeneratorInterface.h"


class Star : public GeneratorInterface {
public:
    explicit Star() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (unsigned int i = 1; i < n; i++) {
            add_edge(0, i, g);
        };
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 150.0, n - 1);
        pos.insert(pos.begin(), cgtea_geometry::Point(width, height));
        for_each_v(g, [&](Ver v) { boost::put(boost::vertex_distance, g, v, pos[v]); });
        return g;
    }

    string name() const override {
        return "Star";
    }

    string description() const override {
        return "Generates a star graph.";
    }
};


#endif //CGTEA_STAR_H
