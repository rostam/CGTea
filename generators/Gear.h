 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_GEAR_H
#define CGTEA_GEAR_H

#include "GeneratorInterface.h"
/**
 * @brief Gear Graph
 * 
 * - Reference: https://mathworld.wolfram.com/GearGraph.html
 * - The gear graph, also sometimes known as a bipartite wheel graph (Brandstädt et al. 1987), 
 *   is a wheel graph with a graph vertex added between each pair of adjacent graph vertices of the outer cycle.
 * 
 */
class Gear : public GeneratorInterface {
public:
    explicit Gear() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (int i = 1; i <= 2 * n - 1; i++) {
            add_edge(i, i + 1, g);
        }

        add_edge(2 * n, 1, g);

        for (int i = 1; i <= 2 * n; i = i + 2) {
            add_edge(0, i, g);
        }

        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos1;
        pos1.push_back(cgtea_geometry::Point(width, height));
        std::vector<cgtea_geometry::Point> pos2 = position_generators::circle(width, height, 200.0, 2*n);
        pos1.insert(std::end(pos1), std::begin(pos2), std::end(pos2));
        for_each_v(g, [&](Ver v) {boost::put(boost::vertex_distance, g, v, pos1[v]);});
        return g;
    }

    string name() const override {
        return "Gear Graph";
    }

    string description() const override {
        return "Gear Graph";
    }

    string category() const override {
        return "Web Class Graphs";
    };

    string check_parameters() override {
        // //!!! check it!!!
        // if (n < 4)return "n must be higher than 4 !!!";
        // else
        //     return null;
        return "";
    };
};

#endif

