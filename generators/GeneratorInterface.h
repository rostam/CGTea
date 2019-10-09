//
// Created by rostami on 28.06.17.
//

#ifndef EXACT_COLORING_GENERATORINTERFACE_H
#define EXACT_COLORING_GENERATORINTERFACE_H

#include "datatypes.h"
#include "PositionGenerators.h"
#include "compute_force_directed.h"
#include <typeindex>
#include <unordered_map>

typedef std::unordered_map<std::type_index, std::string> typemap;

class GeneratorInterface {
public:
    explicit GeneratorInterface(unsigned int num_of_vertices) : n(num_of_vertices), k(0) {}

    GeneratorInterface(unsigned int num_of_vertices, unsigned int kk) : n(num_of_vertices), k(kk) {}

    virtual Graph generate() = 0;
    virtual Graph generate_with_positions(double width, double height) = 0;
    virtual Graph generate_with_force_directed(double width, double height) = 0;

    static vector<string> all_generator_names;
    static typemap & registry() { static typemap impl; return impl; }
protected:
    unsigned int n, k{};
};

template <typename T> struct Registrar
{
    Registrar(std::string const & s) { GeneratorInterface::typemap()[typeid(T)] = s; }
};

#endif //EXACT_COLORING_GENERATORINTERFACE_H
