/**
 * Created by rostami on 28.06.17.
 */
#ifndef EXACT_COLORING_CYCLE_H
#define EXACT_COLORING_CYCLE_H

#include "GeneratorInterface.h"
#include "boost/graph/fruchterman_reingold.hpp"
#include "boost/graph/random_layout.hpp"
#include "boost/graph/topology.hpp"
#include "compute_force_directed.h"
#include "point.h"

class Cycle : public GeneratorInterface {
public:
    explicit Cycle() : GeneratorInterface() {};

    Graph generate(unsigned int num_of_vertices, unsigned int k) override {
        Graph g;
        for (unsigned int i = 0; i < num_of_vertices; i++)
            add_edge(i, ((i + 1) % num_of_vertices), g);
        return g;
    }

    Graph generate_with_positions(unsigned int num_of_vertices, unsigned int k, double width, double height) override {
        Graph g = generate(num_of_vertices, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 100.0, num_of_vertices);
        int i = 0;
        for_each_v(g, [&](Ver v) {
            boost::put(boost::vertex_distance, g, v, pos[i]);
            i++;
        });
        return g;
    }

    Graph generate_with_force_directed(unsigned int num_of_vertices, unsigned int k, double width, double height) override {
        Graph g = generate(num_of_vertices, k);
        std::vector<cgtea_geometry::Point> pos = compute_force_directed(100,100, width, height, g);
        int i = 0;
        for_each_v(g, [&](Ver v) {
            boost::put(boost::vertex_distance, g, v, pos[i]);
            i++;
        });
        return g;
    }

    string name() override {
        return "Cycle";
    }

    string description() override {
        return "Generates a cycle graph.";
    }
};


#endif
