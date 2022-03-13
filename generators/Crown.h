 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_CROWN_H
#define CGTEA_CROWN_H

#include "GeneratorInterface.h"

class Crown : public GeneratorInterface {
public:
    explicit Crown() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (int i = 0; i < n; i++) {
            add_edge(i, n + i, 1, g);
//            add_edge(n + i, 2 * n, 1, g);
            add_edge(n + i, n + ((i + 1) % n), 1, g);
        }
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos1 = position_generators::circle(width, height, 100.0, n);
        std::vector<cgtea_geometry::Point> pos2 = position_generators::circle(width, height, 150.0, n);
        pos1.insert(pos1.end(),std::make_move_iterator(pos2.begin()),std::make_move_iterator(pos2.end()));
        for_each_v(g, [&](Ver v) { boost::put(boost::vertex_distance, g, v, pos1[v]); });
        return g;
    }

    string name() const override {
        return "Crown Graph";
    }

    string description() const override {
        return "Generate Crown Graph";
    }
    
    string category() const override {
        return "Web Class Graphs";
    };
    
    string check_parameters() override {
       return "";
    }
};

#endif

