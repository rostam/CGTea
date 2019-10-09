/**
 * Created by rostami on 28.06.17.
 */
#ifndef EXACT_COLORING_COMPLETE_H
#define EXACT_COLORING_COMPLETE_H

#include "GeneratorInterface.h"
#include "boost/graph/fruchterman_reingold.hpp"
#include "boost/graph/random_layout.hpp"
#include "boost/graph/topology.hpp"
#include "compute_force_directed.h"
#include "point.h"

class Complete : public GeneratorInterface {
public:
    explicit Complete(unsigned int n) : GeneratorInterface(n) {};

    Graph generate() override {
        Graph g;
        for (unsigned int i = 0; i < n; i++)
            for (unsigned int j = i+1; j < n; j++)
            add_edge(i, j, g);
        return g;
    }

    Graph generate_with_positions(double width, double height) override {
        Graph g = generate();
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 100.0, n);
        int i = 0;
        for_each_v(g, [&](Ver v) {
            boost::put(boost::vertex_distance, g, v, pos[i]);
            i++;
        });
        return g;
    }

    Graph generate_with_force_directed(double width, double height) override {
        Graph g = generate();
        compute_force_directed(0,0, width, height, g);
    }
};

#endif
