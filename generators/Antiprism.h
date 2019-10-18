//
// Created by rostam on 09.10.19.
//

#ifndef CGTEA_ANTIPRISM_H
#define CGTEA_ANTIPRISM_H

#include "GeneratorInterface.h"

class Antiprism : public GeneratorInterface {

public:
    explicit Antiprism() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        //generating edges
        for (unsigned int i = 0; i < n; i++) {
           add_edge(i, (i + 1) % n, g);
           if ((i + n + 1) == 2 * n) add_edge(i + n, n,g);
           else add_edge(i + n, i + n + 1,g);
           add_edge(i, (i+n), g);
           add_edge((i + 1) % n, i+n,g);
        }
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos1 = position_generators::circle(width, height, 100.0, n);
        std::vector<cgtea_geometry::Point> pos2 = position_generators::circle(width, height, 200.0, n);
        pos1.insert(pos1.end(), pos2.begin(), pos2.end());
        int i = 0;
        for_each_v(g, [&](Ver v) {
            boost::put(boost::vertex_distance, g, v, pos1[i]);
            i++;
        });
        return g;
    }

    string name() override {
        return "Antiprism Graphs";
    }

    string description() override {
        return "Generates an antiprism graph.";
    }
};

#endif //CGTEA_ANTIPRISM_H
