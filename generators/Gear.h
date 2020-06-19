 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_GEAR_H
#define CGTEA_GEAR_H

#include "GeneratorInterface.h"

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
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
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
        //!!! check it!!!
        if (n < 4)return "n must be higher than 4 !!!";
        else
            return null;
    };
};

#endif

