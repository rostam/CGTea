 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_RANDOMTREE_H
#define CGTEA_RANDOMTREE_H

#include "GeneratorInterface.h"

class RandomTree : public GeneratorInterface {
public:
    explicit RandomTree() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        int[][] ver = new int[2][n]; //o->deg 1->height
        ver[1][0] = 0;
//the new one
        for (int i = 0; i < n - 1; i++) {
            int ran = (int) (Math.random() * (i + 1));
            while (!(ver[0][ran] < d && ver[1][ran] < h)) {
                ran = (ran + 1) % (i + 1);
            }
             add_edge(i + 1, ran, g);
            ver[0][i + 1]++;
            ver[0][ran]++;
            ver[1][i + 1] = ver[1][ran] + 1;
        }
        

    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        Graph g;
        
        int[][] ver = new int[2][n]; //o->deg 1->height

        ver[1][0] = 0;
//the new one
        for (int i = 0; i < n - 1; i++) {
            int ran = (int) (Math.random() * (i + 1));
            while (!(ver[0][ran] < d && ver[1][ran] < h)) {
                ran = (ran + 1) % (i + 1);
            }
             add_edge(i + 1, ran, g);
            ver[0][i + 1]++;
            ver[0][ran]++;
            ver[1][i + 1] = ver[1][ran] + 1;
        }
        

    }

    string name() const override {
        return "Random Tree";
    }

    string description() const override {
        return "Generates a random tree";
    }
    
    string category() const override {
        return "Trees";
    };
    
    string check_parameters() override {
        if ( n<0 || h<0|| d<0)return "Values must be positive!";
    	if (n > Math.pow(d, h) - 1) return "N is to small!";
        else return null;
    };
};

#endif

