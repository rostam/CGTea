//
// Created by rostami on 28.06.17.
//

#ifndef EXACT_COLORING_GENERATORINTERFACE_H
#define EXACT_COLORING_GENERATORINTERFACE_H

#include "../datatypes.h"
#include "PositionGenerators.h"
#include "compute_force_directed.h"

class GeneratorInterface {
public:
    GeneratorInterface(unsigned int num_of_vertices) : n(num_of_vertices) {}

    GeneratorInterface(unsigned int num_of_vertices, unsigned int kk) : n(num_of_vertices), k(kk) {}

    virtual Graph generate() = 0;
    virtual Graph generate_with_positions() = 0;
    virtual Graph generate_with_force_directed() = 0;

protected:
    unsigned int n, k;
};


#endif //EXACT_COLORING_GENERATORINTERFACE_H
