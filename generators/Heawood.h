//
// Created by rostam on 03.07.20.
//

#ifndef CGTEA_HEAWOOD_H
#define CGTEA_HEAWOOD_H


#include "GeneratorInterface.h"

/**
 * @brief Headwood Graph
 * 
 * - Reference: https://mathworld.wolfram.com/HeawoodGraph.html
 * 
 */
class Heawood : public GeneratorInterface {
public:
    explicit Heawood() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (int i = 0; i <= 13; i++) boost::add_edge(i, (i + 1)%14 , 1, g);
        for (int i = 0; i < 14; i += 2) boost::add_edge(i, (i + 5)%14 , 1, g);
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, 14);
        for_each_v(g, [&](Ver v) {boost::put(boost::vertex_distance, g, v, pos[v]);});
        return g;
    }

    string name() const override {
        return "Heawood Graph";
    }

    string description() const override {
        return "Heawood Graph";
    }

    string category() const override {
        return "General";
    };

    string check_parameters() override {
        return "";
    };
};


#endif //CGTEA_HEAWOOD_H
