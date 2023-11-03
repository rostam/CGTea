 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_PATH_H
#define CGTEA_PATH_H

#include "GeneratorInterface.h"

class Path : public GeneratorInterface {
public:
    explicit Path() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        
        for (int i = 0; i < n - 1; i++) {
             add_edge(i, i + 1, 1, g);
        }

        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        for_each_v(g, [&](Ver v) { boost::put(boost::vertex_distance, g, v, pos[v]); });
        return g;
    }

    string name() const override {
        return "Path";
    }

    string description() const override {
        return "Generates a path with n vertices";
    }
    
    string category() const override {
        return "Trees";
    };
    
    string check_parameters() override {
    	return "";
    };
};

#endif

