 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_KENSER_H
#define CGTEA_KENSER_H

#include "GeneratorInterface.h"

class Kenser : public GeneratorInterface {
public:
    explicit Kenser() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        Vector<Edge> ret = new Vector<>();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < (Math.min(n, i + d)); j++) {
                                ret.add((i, j, g), g);
            }
        }
        

        for (int i = 0; i < ret.size(); i++) {
            ret1[i] = ret.get(i);
        }

        

    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        Graph g;
        Vector<Edge> ret = new Vector<>();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < (Math.min(n, i + d)); j++) {
                                ret.add((i, j, g), g);
            }
        }
        

        for (int i = 0; i < ret.size(); i++) {
            ret1[i] = ret.get(i);
        }

        

    }

    string name() const override {
        return "K(n/d)";
    }

    string description() const override {
        return "Generate K(n/d)";
    }
    
    string category() const override {
        return "General Graphs";
    };
    
    string check_parameters() override {
        
    	if( d<0 || n<0)return "Both N & D must be positive!";
    	if(d>0 & n>0 & d>n)return " D must be smaller than N!";
    	else
    		return null;
   
    };
};

#endif

