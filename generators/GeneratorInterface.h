//
// Created by rostami on 28.06.17.
//

#ifndef EXACT_COLORING_GENERATORINTERFACE_H
#define EXACT_COLORING_GENERATORINTERFACE_H

#include "../datatypes.h"
#include "PositionGenerators.h"
#include "compute_force_directed.h"
#include "point.h"

class GeneratorInterface {
public:
    virtual Graph generate(unsigned int n, unsigned int k) { return Graph();};
    virtual Graph generate_with_positions(unsigned int n, unsigned int k,double width, double height) {return Graph();};
    Graph generate_with_force_directed(unsigned int n, unsigned int k, double width, double height) {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = compute_force_directed(50,50, width, height, g);
        int i = 0;
        for_each_v(g, [&](Ver v) {
            boost::put(boost::vertex_distance, g, v, pos[i]);
            i++;
        });
        return g;
    }
    virtual string name() {return "Generator Interface";};
    virtual string description() {return "Generator Interface";};
};

#endif //EXACT_COLORING_GENERATORINTERFACE_H
