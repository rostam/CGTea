 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_KMN_H
#define CGTEA_KMN_H

#include "GeneratorInterface.h"

class Kmn : public GeneratorInterface {
public:
    explicit Kmn() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                 add_edge(i, n + j, g);
            }
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        return g;
    }

    string name() const override {
        return "Km,n";
    }

    string description() const override {
        return "Generate Km,n";
    }
    
    string category() const override {
        return "Multipartite Graphs";
    };
    
    string check_parameters() override {
        
    	if ( n<0 || m<0)return " Values of both M & N must be positive!";
    	else return "";
    };
};

#endif

