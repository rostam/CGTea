//
// Created by rostam on 09.10.19.
//

#ifndef CGTEA_BANANA_H
#define CGTEA_BANANA_H

#include "GeneratorInterface.h"

class Banana : public GeneratorInterface {
public:
    explicit Banana() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (unsigned int i = 0; i < n; i++)
            for (unsigned int j = i+1; j < n; j++)
                add_edge(i, j, 1, g);
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 100.0, n);
        int i = 0;
        for_each_v(g, [&](Ver v) {
            boost::put(boost::vertex_distance, g, v, pos[i]);
            i++;
        });
        return g;
    }

    string name() const override {
        return "Banana Graph";
    }

    string description() const override {
        return "Generates a banana graph.";
    }
};


#endif //CGTEA_BANANA_H
