//
// Created by rostami on 28.06.17.
//

#ifndef EXACT_COLORING_GENERATORINTERFACE_H
#define EXACT_COLORING_GENERATORINTERFACE_H

#include "datatypes.h"
#include "PositionGenerators.h"
#include "compute_force_directed.h"
#include "point.h"

class GeneratorInterface {
public:
    virtual Graph generate(unsigned int n, unsigned int k) {};
    virtual Graph generate_with_positions(unsigned int n, unsigned int k,double width, double height) {};
    Graph generate_with_force_directed(unsigned int n, unsigned int k, double width, double height) {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = compute_force_directed(100,100, width, height, g);
        int i = 0;
        for_each_v(g, [&](Ver v) {
            boost::put(boost::vertex_distance, g, v, pos[i]);
            i++;
        });
        return g;
    }
    virtual string name() {};
    virtual string description() {};
};

#endif //EXACT_COLORING_GENERATORINTERFACE_H
