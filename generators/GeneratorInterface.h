//
// Created by rostami on 28.06.17.
//

#ifndef EXACT_COLORING_GENERATORINTERFACE_H
#define EXACT_COLORING_GENERATORINTERFACE_H

#include "../datatypes.h"
#include "PositionGenerators.h"

class GeneratorInterface {
public:
    GeneratorInterface(unsigned int num_of_vertices) : n(num_of_vertices) {}

    GeneratorInterface(unsigned int num_of_vertices, unsigned int kk) : n(num_of_vertices), k(kk) {}

    virtual Graph generate(bool fill_positions = false) = 0;

protected:
    unsigned int n, k;
};


#endif //EXACT_COLORING_GENERATORINTERFACE_H
