 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_KMNO_H
#define CGTEA_KMNO_H

#include "GeneratorInterface.h"

class Kmno : public GeneratorInterface {
public:
    explicit Kmno() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
		
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n + o; j++)
				 add_edge(i, m + j, g);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < o; j++)
				 add_edge(m + i, m + n + j, g);

		return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        return g;
    }

    string name() const override {
        return "Km,n,o";
    }

    string description() const override {
        return "Generate Km,n,o";
    }
    
    string category() const override {
        return "Multipartite Graphs";
    };
    
    string check_parameters() override {
        return "";
    }
};

#endif

