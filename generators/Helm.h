 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_HELM_H
#define CGTEA_HELM_H

#include "GeneratorInterface.h"

class Helm : public GeneratorInterface {
public:
    explicit Helm() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;

        if (!closed) result = new Edge[3 * n];
        else result = new Edge[3 * n + n];

        for (int i = 0; i < n; i++) {
            add_edge(i, n + i, g);

            add_edge(n + i, 2 * n, g);

            add_edge(n + i, n + ((i + 1, g) % n, g), g);

            if (closed) {
                add_edge(i, ((i + 1, g) % n, g), g);
            }
        }
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        return g;
    }

    string name() const override {
        return "Helm Graph";
    }

    string description() const override {
        return "Generate Helm Graph";
    }

    string category() const override {
        return "Web Class Graphs";
    };

    string check_parameters() override {

        if (n < 3) return "n must be higher than 2!";
        else
            return null;

    };
};

#endif

