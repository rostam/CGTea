/**
 * Created by rostami on 28.06.17.
 */
#ifndef EXACT_COLORING_CYCLE_H
#define EXACT_COLORING_CYCLE_H

#include "GeneratorInterface.h"
#include "boost/graph/fruchterman_reingold.hpp"
#include "boost/graph/random_layout.hpp"
#include "boost/graph/topology.hpp"

class Cycle : public GeneratorInterface {
public:
    Cycle(int n) : GeneratorInterface(n) {};

    Graph generate() {
        Graph g;
        for (int i = 0; i < n; i++)
            add_edge(i, ((i + 1) % n), g);
        return g;
    }

    Graph generate_with_positions() {
        Graph g = generate();
        std::vector<std::pair<double, double>> pos = position_generators::circle(200, 500, 500, n);
        int i = 0;
        for_each_v(g, [&](Ver v) {
            boost::put(boost::vertex_distance, g, v, pos[i]);
            i++;
        });
        return g;
    }

    Graph generate_with_force_directed() {
        Graph g = generate();
        compute_force_directed(500, 500);
    }
};

#endif
