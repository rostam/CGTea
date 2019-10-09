//
// Created by rostami on 28.06.17.
//

#ifndef EXACT_COLORING_GENERATORINTERFACE_H
#define EXACT_COLORING_GENERATORINTERFACE_H

#include "datatypes.h"
#include "PositionGenerators.h"
#include "compute_force_directed.h"

class GeneratorInterface {
public:
    virtual Graph generate(unsigned int n, unsigned int k) = 0;
    virtual Graph generate_with_positions(unsigned int n, unsigned int k,double width, double height) = 0;
    virtual Graph generate_with_force_directed(unsigned int n, unsigned int k,double width, double height) = 0;
    virtual string name() = 0;
    virtual string description() = 0;
};

#endif //EXACT_COLORING_GENERATORINTERFACE_H
