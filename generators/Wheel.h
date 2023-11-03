 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_WHEEL_H
#define CGTEA_WHEEL_H

#include "GeneratorInterface.h"

class Wheel : public GeneratorInterface {
public:
    explicit Wheel() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (int i = 1; i < n - 1; i++) {
            add_edge(i, i + 1, g);
        }
        add_edge(n - 1, 1, g);
        for (int i = 1; i < n; i++) {
            add_edge(0, i, g);
        }
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 150.0, n - 1);
        pos.insert(pos.begin(), cgtea_geometry::Point(width, height));
        for_each_v(g, [&](Ver v) { boost::put(boost::vertex_distance, g, v, pos[v]); });
        return g;
    }

    string name() const override {
        return "Wheel Graph";
    }

    string description() const override {
        return "Wheel Graph";
    }
    
    string category() const override {
        return "Web Class Graphs";
    };
    
    string check_parameters() override {
        return "";
    };
};

#endif

